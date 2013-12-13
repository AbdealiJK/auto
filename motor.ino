// ------------------------------------------------
motor::motor(int p1,int p2, int p, int pot) {
  /* 
   Sets the pins 
   Initiates dummy values
   Starts PID class
   */
  pin1 = p1;
  pin2 = p2;
  pwm_pin = p;
  pot_pin = pot;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pwm_pin, OUTPUT);
  pinMode(pot_pin, INPUT);

  trip_left = -1;
  trip_right = -1;
  lim = 5;
  Kp = 0.01;
  Ki = Kd = 0;  

  motor_pid.init(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
  motor_pid.SetMode(AUTOMATIC);
  motor_pid.SetTunings(Kp, Ki, Kd);
  motor_pid.SetOutputLimits(-lim, lim);
}

// ------------------------------------------------
void motor::reset() {
  /* 
   Resets initial position.
   */

  calc_pos();
  calc_vel();
  init_pos = cur_pos;
#ifdef DEBUG
  Serial.print("\t Motor initialized @ ");
  Serial.println(init_pos);
#endif
}

// ------------------------------------------------
int motor::run(int dir, int pwm) {
  /*
    Runs the motor. Gives 1
   Checks if trips tripped. If tripped, gives 0
   */

  if ( trip_left != -1 && digitalRead(trip_left) == HIGH ) {
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    analogWrite(pwm_pin, 255);
    return 0;
  } 
  if ( trip_right != -1 && digitalRead(trip_right) == HIGH ) {
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    analogWrite(pwm_pin, 255);
    return 0;
  }

  digitalWrite(pin1, dir / 2);
  digitalWrite(pin2, dir % 2);
  analogWrite(pwm_pin, pwm);
  return 1;
}

// ------------------------------------------------
void motor::calc_pos() {  
  /*
    Sets cur_pos and cur_turns
   */
  for( int i = 0; i < SAMPLE_ANALOG; i++) {
    cur_turns += analogRead(pot_pin);
  }
  cur_turns /= SAMPLE_ANALOG;

  cur_pos = cur_turns * K_FACTOR;
  cur_pos -= init_pos;  

}

// ------------------------------------------------
void motor::calc_vel() {  
  /*
    Sets velocities
   */
  vel_turns = (cur_turns - prev_turns) / (micros()-time_prev);
  vel = (cur_pos - prev_pos) / (micros()-time_prev);
  time_prev = micros();
  prev_pos = cur_pos;
  prev_turns = cur_turns;
} 

// ------------------------------------------------
void motor::set_trips(int l, int r) {
  /*
    Sets the trip switches
   */
  trip_left = l;
  trip_right = r;
}

// ------------------------------------------------
void motor::set_params(double Kp , double Ki, double Kd , int lim) {  
  /*
    Sets pid params
   */
  motor_pid.SetTunings(Kp, Ki, Kd);
  motor_pid.SetOutputLimits(-lim, lim);
}

// ------------------------------------------------
int motor::goto_pos(float req_pos) {  
  /*
    Goes to the position defined. returns 0 while moving
   If tripped, return -1
   If reached, return 1
   */
  calc_pos();
  calc_vel();
  Input = cur_pos;

  target_pos = req_pos;

  Setpoint = req_pos;
  motor_pid.Compute();

#ifdef DEBUG
  Serial.print("\t Input ");
  Serial.print(Input);
  Serial.print("\t Setpoint ");
  Serial.print(Setpoint);
  Serial.print("\t Output ");
  Serial.print(Output);
#endif

  if (Output > 0) {
    if( run(1, Output) == 0 )
      return -1; 
  } 
  else if (Output < 0) {
    if( run(2, -Output) == 0 )
      return -1; 
  } 
  else {
    return 1;
  }
  return 0;
}

// ------------------------------------------
int motor::goto_pos() {  
  return goto_pos(target_pos);
}

