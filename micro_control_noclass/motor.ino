
// ------------------------------------------------
int run(int dir, int pwm) {
  /*
    Runs the motor. Gives 1
   Checks if trips tripped. If tripped, gives 0
   */
  calc_pos();
  update_trip();

  if ( home_trip && dir == HOME ) {
    digitalWrite(MOTOR_1, 0);
    digitalWrite(MOTOR_2, 0);
    analogWrite(MOTOR_PWM, 255);
    //#ifdef DEBUG
    PC.println("\t Trip switch HOME pressed for some motor ! ");
    //#endif
    return 0;
  }

  if ( middle_trip  && dir == MID ) {
    digitalWrite(MOTOR_1, 0);
    digitalWrite(MOTOR_2, 0);
    analogWrite(MOTOR_PWM, 255);
    //#ifdef DEBUG
    PC.println("\t Trip switch CENTRE pressed for some motor ! ");
    //#endif
    return 0;
  }
  //#ifdef DEBUG
  //  PC.print("\t Running motor at pwm = ");
  //  PC.println(pwm);
  //  PC.print("\t Current position ");
  //  PC.println(pos);
  //#endif

  digitalWrite(MOTOR_1, dir / 2);
  //Serial.print("m1 : ");
  //Serial.println(dir/2);
  digitalWrite(MOTOR_2, dir % 2);
  //Serial.print("m2 : ");
  //Serial.println(dir%2);
  analogWrite(MOTOR_PWM, pwm);
  return 1;

}


// ------------------------------------------------
void calc_pos() {
  /*
    Sets cur_pos and cur_turns
   */
  float temp = 0;
  for ( int i = 0; i < SAMPLE_LENGTH; i++) {
    temp += digitalRead(AUTONIC_PIN);
  }
  //  temp /= SAMPLE_ANALOG;
  if ( temp > SAMPLE_LENGTH * 0.7)
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
  digitalWrite(PISTON_PIN, v == CLOSE);


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
int goto_pos() {
  /*
    Goes to the position defined. returns 0 while moving
   If tripped, return -1
   If reached, return 1
   */

  int output_pwm = (target_pos - pos) * acc_pwm;

  //#ifdef DEBUG
  //  PC.print("\t Input ");
  //  PC.print(Input);
  //  PC.print("\t Setpoint ");
  //  PC.print(Setpoint);
  //  PC.print("\t Output ");
  //  PC.println(Output);
  //#endif

  if (output_pwm > 0) {
    if ( run(MID, output_pwm) == 0 )
      return -1;
  }
  else if (output_pwm < 0) {
    if ( run(HOME, -output_pwm) == 0 )
      return -1;
  }
  else {
    run(STOP, 255);
    return 1;
  }
  return 0;
}

// ------------------------------------------
int goto_pos(int target) {
  target_pos = target;
  return goto_pos();
}

void go_home()
{
  while ( run(HOME, HOME_SPEED) == 1 ) {
    if ( PC.available() && PC.read() == 'q' ) {
      run(STOP, 255);
      break;
    }
  }

}
void update_trip() {
  if (MIDDLE_TRIP != 0)  { // I have middle_trip
    //    int temp_mid_trip = digitalRead(MIDDLE_TRIP) == MIDDLE_TRIPPED;
    //    Serial.println(temp_mid_trip);

    if (MIDDLE_TRIP != -1 ) { //&& temp_mid_trip != middle_trip) {
      middle_trip = digitalRead(MIDDLE_TRIP) == MIDDLE_TRIPPED;
      Serial1.print(TRIP_CHAR);
      Serial1.print(middle_trip);

      Serial.print("middle_trips sent : ");
      Serial.print(TRIP_CHAR);
      Serial.print(" ... ");
      Serial.println(middle_trip);
    }
  }
  else { // I need to get middle_trip data from others
    if (Serial1.available() && Serial1.peek() == TRIP_CHAR) {
      Serial1.read(); // to bypass TRIP_CHAR
      int start_time = millis();
      while (!Serial1.available()) {
        if ( millis() - start_time > 5 ) {
          start_time = -1;
        }
      }
      if ( start_time != -1 ) {
        char trip = Serial1.read();
        if ( trip == '0' || trip == '1' ) { // remove garbage data
          middle_trip = trip - '0';
        }
      }
    }
  }
  if (RUNG_TRIP != 0 && rflag == 1)  { // check if I have rung_trip and check if rung trip must be checked
    if (RUNG_TRIP != -1 && digitalRead(RUNG_TRIP) == rung_trip) {
      rung_trip = digitalRead(RUNG_TRIP) == TRIPPED;
      Serial1.print(TRIP_CHAR_RUNG);
      Serial1.print(rung_trip);
    }
  }
  home_trip = ( digitalRead(HOME_TRIP) == HOME_TRIPPED);
}



