// ------------------------------------------------
void motor_init(int p1,int p2, int p, int aut, int pist, int tl, int tr) {
  /*  // pin1, pin2, pwm, autonic, trip_left, trip_right
   Sets the pins 
   Initiates dummy values
   Starts PID class
   */
  pin1 = p1;
  pin2 = p2;
  pwm_pin = p;
  autonic_pin = aut;
  piston_pin = pist;
  trip_left = tl;
  trip_right = tr;
  
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pwm_pin, OUTPUT);
  pinMode(autonic_pin, INPUT);
  pinMode(piston_pin, OUTPUT);
  pinMode(trip_left, INPUT);
  pinMode(trip_right, INPUT);
  run(STOP, 255);
  if ( autonic_pin == 7 )
    setInterrupt(RISING_I);// function is ISR(INT6_vect) interrupt for INT.6 which isnt available in attachInterrupt. 
  pwm_lim = 5;
  Kp = 0.01;
  Ki = Kd = 0;  

  motor_pid.init(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
  motor_pid.SetMode(AUTOMATIC);
  motor_pid.SetTunings(Kp, Ki, Kd);
  motor_pid.SetOutputLimits(-pwm_lim, pwm_lim);

//#ifdef DEBUG
//  PC.println("\t Motor class initiated ");
//#endif
}          

// ------------------------------------------------
void reset() {
  /* 
   Resets initial position.
   */
  pos = 0;

//#ifdef DEBUG
//  PC.println("\t Motor position reset to 0");
//#endif
}

// ------------------------------------------------
int run(int dir, int pwm) {
  /*
    Runs the motor. Gives 1
   Checks if trips tripped. If tripped, gives 0
   */
  //  calc_pos();

    PC.print("\t Trip pin : ");
    PC.println(trip_right);
    PC.print("\t Trip right value : ");
    PC.println(digitalRead(trip_right));
    delay(100);
  if ( trip_left != -1 && digitalRead(trip_left) == TRIPPED && dir==LEFT) {
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    analogWrite(pwm_pin, 255);
//#ifdef DEBUG
    PC.println("\t Trip switch LEFT pressed for some motor ! ");
//#endif
    return 0;
  } 
  if ( trip_right != -1 && digitalRead(trip_right) == TRIPPED && dir==RIGHT ) {
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    analogWrite(pwm_pin, 255);
//#ifdef DEBUG
    PC.println("\t Trip switch RIGHT pressed for some motor ! ");
    PC.print("\t Trip pin : ");
    PC.println(trip_right);
    PC.print("\t Trip right value : ");
    PC.println(digitalRead(trip_right));
//#endif
    return 0;
  }
//#ifdef DEBUG
//  PC.print("\t Running motor at pwm = ");
//  PC.println(pwm);
//  PC.print("\t Current position ");
//  PC.println(pos);
//#endif

  digitalWrite(pin1, dir / 2);
  digitalWrite(pin2, dir % 2);
  analogWrite(pwm_pin, pwm);
  return 1;

}

// ------------------------------------------------
int stop() {
  return run(STOP, 255);
}

// ------------------------------------------------
void calc_pos() {  
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

//#ifdef DEBUG
//   PC.print("Current position ");
//   PC.print(cur_pos);
//   PC.print(" Current turns ");
//   PC.print(cur_turns);
//#endif
}

// ------------------------------------------------
void piston(int v) {  
  /*
    Actuates the piston depending on the value given
   */
  digitalWrite(piston_pin, v == CLOSE);
    
  
//#ifdef DEBUG
//  if ( v == OPEN )
//    PC.print("Piston opened ");
//  else if ( v == CLOSE )
//    PC.print("Piston closed ");
//  else
//    PC.print("Unknown input, Piston closed ");
//#endif
}

// ------------------------------------------------
void set_params(double Kp, double Ki, double Kd) {  
  /*
    Sets pid params
   */
  motor_pid.SetTunings(Kp, Ki, Kd);
}

// ------------------------------------------------
void set_params(double Kp, double Ki, double Kd, int lim) {  
  /*
    Sets pid params
   */
  motor_pid.SetTunings(Kp, Ki, Kd);
  motor_pid.SetOutputLimits(-lim, lim);
}

// ------------------------------------------------
int goto_pos() {
  /*
    Goes to the position defined. returns 0 while moving
   If tripped, return -1
   If reached, return 1
   */
   
  Input = pos;

  motor_pid.Compute();
  
//#ifdef DEBUG
//  PC.print("\t Input ");
//  PC.print(Input);
//  PC.print("\t Setpoint ");
//  PC.print(Setpoint);
//  PC.print("\t Output ");
//  PC.println(Output);
//#endif

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
int goto_pos(int req_pos) {  
  Setpoint = req_pos;
  return goto_pos();
}
