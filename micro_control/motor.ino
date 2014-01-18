// ------------------------------------------------
motor::motor(int p1, int p2, int p, int aut, int pist, int tl, int tr) {
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
void motor::reset() {
  /*
   Resets initial position.
   */
  pos = 0;

  //#ifdef DEBUG
  //  PC.println("\t Motor position reset to 0");
  //#endif
}

// ------------------------------------------------
int motor::run(int dir, int pwm) {
  /*
    Runs the motor. Gives 1
   Checks if trips tripped. If tripped, gives 0
   */
  calc_pos();
  update_trip();
  PC.print("\t Trip pin : ");
  PC.println(trip_right);
  PC.print("\t Trip right value : ");
  PC.println(digitalRead(trip_right));
  delay(100);
  if ( get_trip( HOME_TRIP, dir)) {
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    analogWrite(pwm_pin, 255);
    //#ifdef DEBUG
    PC.println("\t Trip switch HOME pressed for some motor ! ");
    //#endif
    return 0;
  }

  if (get_trip( CENTRE_TRIP, dir)) {
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    analogWrite(pwm_pin, 255);
    //#ifdef DEBUG
    PC.println("\t Trip switch CENTRE pressed for some motor ! ");
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
int motor::stop() {
  return run(STOP, 255);
}

// ------------------------------------------------
void motor::calc_pos() {
  /*
    Sets cur_pos and cur_turns
   */
  float temp = 0;
  for ( int i = 0; i < SAMPLE_LENGTH; i++) {
    temp += digitalRead(autonic_pin);
  }
  //  temp /= SAMPLE_ANALOG;
  if ( temp > SAMPLE_LENGTH / 2 )
    pos ++;

  //#ifdef DEBUG
  //   PC.print("Current position ");
  //   PC.print(cur_pos);
  //   PC.print(" Current turns ");
  //   PC.print(cur_turns);
  //#endif
}

// ------------------------------------------------
void motor::piston(int v) {
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
    if ( run(RIGHT, Output) == 0 )
      return -1;
  }
  else if (Output < 0) {
    if ( run(LEFT, -Output) == 0 )
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

void motor::go_home()
{
  if (MY_CLAMP == 'l')
  {
    while ( m.run(LEFT, HOME_SPEED) == 1 ) {
      if ( PC.available() && PC.read() == 'q' ) {
        m.run(STOP, 255);
        break;
      }
    }
  }
  else
  {
    while ( m.run(RIGHT, HOME_SPEED) == 1 ) {
      if ( PC.available() && PC.read() == 'q' ) {
        m.run(STOP, 255);
        break;
      }
    }
  }
}
void get_trip( int trip, int dir)
{
  char clamp = MY_CLAMP;
  if (clamp == 'r')
  {
    if (trip == HOME_TRIP)
    {
      return (trip_right != -1 && digitalRead(trip_right) == HIGH && dir == RIGHT);
    }
    else if (trip == CENTRE_TRIP)
    {
      if (HAS_CENTRE)
      {
        if (trip_left != -1 && digitalRead(trip_left) == HIGH && dir == LEFT)
        {
          update_trip();
          return (1);
        }
        else
        {
          return (0);
        }
      }
      else
      {

        if (trip_flag == TRIPPED)
        {
          return (1);
        }
        else
        {
          return (0);
        }
      }
    }
  }
  else if (clamp == 'l')
  {
    if (trip == HOME_TRIP)
    {
      return (trip_left != -1 && digitalRead(trip_left) == HIGH && dir == LEFT);
    }
    else if (trip == CENTRE_TRIP)
    {
      if (HAS_CENTRE)
      {
        if ( trip_right != -1 && digitalRead(trip_right) == HIGH && dir == RIGHT )
        {
          update_trip();
          return (1);
        }
        else
        {
          return (0);
        }
      }
      else
      {

        if (trip_flag == TRIPPED)
        {
          return (0);
        }
        else
        {
          return (1);
        }
      }
    }
  }
}
void update_trip()
{
  if (HAS_CENTRE)
  {
    if (MY_CLAMP == 'l')
    {
      if (trip_right != -1 && digitalRead(trip_right) == HIGH && !trip_flag)
      {
        query(TRIP_CHAR);
        query(1);
        trip_flag = 1;
      }
      else if (trip_flag) //performs only if previous value of trip flag is different
      {
        query(TRIP_CHAR);
        query(0);
        trip_flag = 0;
      }
    }
    else
    {
      if (trip_left != -1 && digitalRead(trip_left) == HIGH && !trip_flag)
      {
        query(TRIP_CHAR);
        query(1);
        trip_flag = 1;
      }
      else if (trip_flag)
      {
        query(TRIP_CHAR);
        query(0);
        trip_flag = 0;
      }
    }
  }
  else
  {
    if (Serial.peek() == TRIP_CHAR)
    {
      Serial.read();// to bypass TRIP_CHAR
      trip_flag = Serial.parseInt();
    }
  }
}
