// ------------------------------------------------
motor::motor(int p1,int p2, int p, int aut, int tl, int tr) {
  /*  // pin1, pin2, pwm, autonic, trip_left, trip_right
   Sets the pins 
   Initiates dummy values
   Starts PID class
   */
  pin1 = p1;
  pin2 = p2;
  pwm_pin = p;
  autonic_pin = aut;
  trip_left = tl;
  trip_right = tr;
  
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pwm_pin, OUTPUT);
  pinMode(autonic_pin, INPUT);
  pinMode(trip_left, INPUT);
  pinMode(trip_right, INPUT);
  run(STOP, 255);

  trip_left = -1;
  trip_right = -1;
  pwm_lim = 5;
  Kp = 0.01;
  Ki = Kd = 0;  

  motor_pid.init(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
  motor_pid.SetMode(AUTOMATIC);
  motor_pid.SetTunings(Kp, Ki, Kd);
  motor_pid.SetOutputLimits(-pwm_lim, pwm_lim);

#ifdef DEBUG
  Serial.println("\t Motor class initiated ");
#endif
}          

// ------------------------------------------------
void motor::reset() {
  /* 
   Resets initial position.
   */
  pos = 0;

#ifdef DEBUG
  Serial.println("\t Motor position reset to 0");
#endif
}

// ------------------------------------------------
int motor::run(int dir, int pwm) {
  /*
    Runs the motor. Gives 1
   Checks if trips tripped. If tripped, gives 0
   */
  //  calc_pos();

  if ( trip_left != -1 && digitalRead(trip_left) == HIGH && dir==LEFT) {
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    analogWrite(pwm_pin, 255);
#ifdef DEBUG
    Serial.println("\t Trip switch LEFT pressed for some motor ! ");
#endif
    return 0;
  } 
  if ( trip_right != -1 && digitalRead(trip_right) == HIGH && dir==RIGHT ) {
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    analogWrite(pwm_pin, 255);
#ifdef DEBUG
    Serial.println("\t Trip switch RIGHT pressed for some motor ! ");
#endif
    return 0;
  }
#ifdef DEBUG
  Serial.print("\t Running motor at pwm = ");
  Serial.print(pwm);
  Serial.print("\t Current position ");
  Serial.println(cur_pos);
#endif

  digitalWrite(pin1, dir / 2);
  digitalWrite(pin2, dir % 2);
  analogWrite(pwm_pin, pwm);
  return 1;

}

// ------------------------------------------------
int motor::stop() {
  return run(STOP, 255);
}

// ------------------------------------------------
void motor::calc_pos() {  
  /*
    Sets cur_pos and cur_turns
   */
  float temp = 0;
  for( int i = 0; i < SAMPLE_LENGTH; i++) {
    temp += digitalRead(autonic_pin);
  }
//  temp /= SAMPLE_ANALOG;
  if ( temp > SAMPLE_LENGTH/2 )
    pos ++;

#ifdef DEBUG
  /*Serial.print("Current position ");
   Serial.print(cur_pos);
   Serial.print(" Current turns ");
   Serial.print(cur_turns);*/
#endif
}

// ------------------------------------------------
void motor::set_params(double Kp, double Ki, double Kd) {  
  /*
    Sets pid params
   */
  motor_pid.SetTunings(Kp, Ki, Kd);
}

// ------------------------------------------------
void motor::set_params(double Kp, double Ki, double Kd, int lim) {  
  /*
    Sets pid params
   */
  motor_pid.SetTunings(Kp, Ki, Kd);
  motor_pid.SetOutputLimits(-lim, lim);
}

// ------------------------------------------------
int motor::goto_pos() {
  /*
    Goes to the position defined. returns 0 while moving
   If tripped, return -1
   If reached, return 1
   */
   
  Input = pos;
/*
  if( abs( req_pos - cur_pos ) < 0.2) {
    run(STOP, 255);
    return 1;
  }
*/
  motor_pid.Compute();
  
#ifdef DEBUG
  Serial.print("\t Input ");
  Serial.print(Input);
  Serial.print("\t Setpoint ");
  Serial.print(Setpoint);
  Serial.print("\t Output ");
  Serial.println(Output);
#endif

  if (Output > 0) {
    if( run(RIGHT, Output) == 0 )
      return -1; 
  }
  else if (Output < 0) {
    if( run(LEFT, -Output) == 0 )
      return -1; 
  }
  else {
    run(STOP, 255);
    return 1;
  }
  return 0;
}

// ------------------------------------------
int motor::goto_pos(int req_pos) {  
  Setpoint = req_pos;
  return goto_pos();
}
