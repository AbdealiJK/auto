// ------------------------------------------------
motor::motor(int p1, int p2, int p, int aut, int pist, int tl, int tr, int at) {
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
  atime = at;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pwm_pin, OUTPUT);
  pinMode(autonic_pin, INPUT);
  pinMode(piston_pin, OUTPUT);
  pinMode(trip_left, INPUT);
  pinMode(trip_right, INPUT);
  run(STOP, 255);
  /* DO NOT USE
    if ( autonic_pin == 3 )
      attachInterrupt(1, posr, RISING);
    else if ( autonic_pin == 2 )
      attachInterrupt(0, posl, RISING);
     else if ( autonic_pin == 18 )
     attachInterrupt(1, calc_pos);
     else if ( autonic_pin == 19 )
     attachInterrupt(1, calc_pos);
     else if ( autonic_pin == 20 )
     attachInterrupt(1, calc_pos);
     else if ( autonic_pin == 21 )
     attachInterrupt(1, calc_pos);
     */
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
  last_pos_time = millis();
  //#ifdef DEBUG
  //  PC.println("\t Motor position reset to 0");
  //#endif
}

// ------------------------------------------------
int motor::run(int dir, int pwm) {
  heartbeat();
  /*
    Runs the motor. Gives 1
   Checks if trips tripped. If tripped, gives 0
   */
  //calc_pos(); //check
  //  current_dir = dir;

  if ( trip_left != -1 && digitalRead(trip_left) == TRIPPED && dir == LEFT) {
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    analogWrite(pwm_pin, 255);
    //#ifdef DEBUG
    PC.println("\t Trip switch LEFT pressed for some motor ! ");
    //#endif
    return 0;
  }
  if ( trip_right != -1 && digitalRead(trip_right) == TRIPPED && dir == RIGHT ) {
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    analogWrite(pwm_pin, 255);
    //#ifdef DEBUG
    PC.println("\t Trip switch RIGHT pressed for some motor ! ");
    //#endif


    return 0;
  }
  //#ifdef DEBUG
  //  PC.print("\t Running motor at pwm = ");
  //  PC.println(pwm);
  //  PC.print("\t Current position ");
  //  PC.println(pos);
  //#endif

  current_dir = dir;

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

  if ( millis() < last_pos_time + atime )
    return;
  float temp = 0;
  for ( int i = 0; i < SAMPLE_LENGTH; i++) {
    temp += digitalRead(autonic_pin);
  }

  //  temp /= SAMPLE_ANALOG;
  if ( temp > SAMPLE_LENGTH / 2 )
  {
    //     Serial.println("HIGH");
    if (current_dir == LEFT)
    {
      pos--;
    }
    else
    {
      pos++;
    }
    Serial.print(" pos: ");
    Serial.println(pos);
    last_pos_time = millis();
  }//#ifdef DEBUG
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
  /*
  if( abs( req_pos - cur_pos ) < 0.2) {
   run(STOP, 255);
   return 1;
   }
   */
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
  //  Serial.println(Kp);
  return 0;
  
}

// ------------------------------------------
int motor::goto_pos(int req_pos) {
  Setpoint = req_pos;
  return goto_pos();
}

//------------------------------------------------------------

int motor::move_right(int req_speed, int req_pos)
{
  motor_pid.SetOutputLimits(-req_speed, req_speed);
  while ( goto_pos(req_pos) == 0 ) {
    if ( PC.available() && PC.read() == 'q' ) {
      stop();
      return 1;
    }
  }
  return 0;

}
int motor::move_right(int req_speed)
{
  while ( run(RIGHT, req_speed) == 1 ) {
    if ( PC.available() && PC.read() == 'q' ) {
      run(STOP, 255);
      break;
      return 1;
    }
  }

  return 0;
}
int motor::move_left(int req_speed, int req_pos)
{
  motor_pid.SetOutputLimits(-req_speed, req_speed);
  while ( goto_pos(-req_pos) == 0 ) {
    if ( PC.available() && PC.read() == 'q' ) {
      stop();
      return 1;
    }
  }
  return 0;
}
int motor::move_left(int req_speed)
{
  while ( run(LEFT, req_speed) == 1 ) {
    if ( PC.available() && PC.read() == 'q' ) {
      run(STOP, 255);
      break;
      return 1;
    }

  }

  return 0;
}


int move_together(int pos1, int pos2, int speed1, int speed2)
{
  ml.motor_pid.SetOutputLimits(-speed1, speed1);
  mr.motor_pid.SetOutputLimits(-speed2, speed2);
  while ( (ml.goto_pos(pos1) == 0) && (mr.goto_pos(pos2) == 0) ) {
    if ( PC.available() && PC.read() == 'q' ) {
      ml.stop();
      mr.stop();
      PC.println("Both motors STOPPED !");
      break;
      return 1;
    }
  }
  while ( (ml.goto_pos(pos1) == 0)  ) {
    if ( PC.available() && PC.read() == 'q' ) {
      ml.stop();

      PC.println("Both motors STOPPED !");
      break;
      return 1;
    }
  }
  while ( (mr.goto_pos(pos2) == 0) ) {
    if ( PC.available() && PC.read() == 'q' ) {

      mr.stop();
      PC.println("Both motors STOPPED !");
      break;
      return 1;
    }
  }
  return 0;
}
int go_home()
{

  while ( ml.run(LEFT, RESET_SPEED_LEFT) == 1 && mr.run(RIGHT, RESET_SPEED_RIGHT) == 1 ) {
    if ( PC.available() && PC.read() == 'q' ) {
      ml.run(STOP, 255);
      mr.run(STOP, 255);
      break;
      return 1;
    }
  }
  while ( ml.run(LEFT, RESET_SPEED_LEFT) == 1  ) {
    if ( PC.available() && PC.read() == 'q' ) {
      ml.run(STOP, 255);
      break;
      return 1;
    }
  }
    while ( mr.run(RIGHT, RESET_SPEED_RIGHT) == 1 ) {
      if ( PC.available() && PC.read() == 'q' ) {
        mr.run(STOP, 255);
        break;
        return 1;
      }

    }
    ml.reset();
    mr.reset();
    return 0;
  }

