// ------------------------------------------------
int run(int dir, int pwm) {
  update_trips();

  if ( home_trip && dir == HOME ) {
    digitalWrite(MOTOR_1, 0);
    digitalWrite(MOTOR_2, 0);
    analogWrite(MOTOR_PWM, 255);
    PC.println("\t Trip switch HOME pressed for some motor ! ");
    return 0;
  }

  if ( middle_trip  && dir == MID ) {
    digitalWrite(MOTOR_1, 0);
    digitalWrite(MOTOR_2, 0);
    analogWrite(MOTOR_PWM, 255);
    PC.println("\t Trip switch CENTRE pressed for some motor ! ~");
    return 0;
  }

  digitalWrite(MOTOR_1, dir / 2);
  digitalWrite(MOTOR_2, dir % 2);
  analogWrite(MOTOR_PWM, pwm);
  return 1;
}

// ------------------------------------------------
void piston(int v) {
  digitalWrite(PISTON_PIN, v == CLOSE);
}

void go_home() {
  while ( run(HOME, HOME_SPEED) == 1 ) {
    if ( PC.available() && PC.read() == 'q' ) {
      run(STOP, 255);
      break;
    }
  }
}
void update_trips() {
  Serial1.print(COMM_CHAR);
  if (MIDDLE_TRIP != 0 && MIDDLE_TRIP != -1 ) { // I have middle_trip
    middle_trip = digitalRead(MIDDLE_TRIP) == MIDDLE_TRIPPED;
    Serial1.print(middle_trip);
  } else {
    Serial1.print('2');
  }
  if (FIXEDCLAMP_TRIP != 0 && FIXEDCLAMP_TRIP != -1 ) { // I have middle_trip
    fixedclamp_trip = digitalRead(FIXEDCLAMP_TRIP) == FIXEDCLAMP_TRIPPED;
    Serial1.print(fixedclamp_trip);
  } else {
    Serial1.print('2');
  }
  if (COMM_TRIP != 0 && COMM_TRIP != -1 ) { // I have middle_trip
    comm_trip = digitalRead(COMM_TRIP) == COMM_TRIPPED;
    Serial1.print(comm_trip);
  } else {
    Serial1.print('2');
  }

  if ( Serial1.available() && Serial1.peek() == COMM_CHAR ) {
    Serial1.read(); // to bypass COMM_CHAR
    int start_time = millis();
    while (Serial1.available() < 4) {
      if ( millis() - start_time > 5 ) {
        start_time = -1;
        break;
      }
    }
    if ( start_time != -1 ) {
      char trip = Serial1.read();
      if ( trip == '0' || trip == '1' ) { // remove garbage data
        middle_trip = trip - '0';
      } else if ( trip == '2' ) {
        middle_trip = !MIDDLE_TRIPPED;
      }
      trip = Serial1.read();
      if ( trip == '0' || trip == '1' ) { // remove garbage data
        fixedclamp_trip = trip - '0';
      } else if ( trip == '2' ) {
        fixedclamp_trip = !FIXEDCLAMP_TRIPPED;
      }
      trip = Serial1.read();
      if ( trip == '0' || trip == '1' ) { // remove garbage data
        comm_trip = trip - '0';
      } else if ( trip == '2' ) {
        comm_trip = !COMM_TRIPPED;
      }
    }
  }
  home_trip = ( digitalRead(HOME_TRIP) == HOME_TRIPPED);
}



