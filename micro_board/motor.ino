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

void go_home(int sp) {
  while ( run(HOME, sp) == 1 ) {
    if ( PC.available() && PC.read() == 'q' ) {
      run(STOP, 255);
      break;
    }
  }
}
void update_trips() {
  if (MIDDLE_TRIP != 0 && MIDDLE_TRIP != -1 ) { // I have middle_trip
    middle_trip = digitalRead(MIDDLE_TRIP) == MIDDLE_TRIPPED;
  }
  if (FIXEDCLAMP_TRIP != 0 && FIXEDCLAMP_TRIP != -1 ) { // I have middle_trip
    fixedclamp_trip = digitalRead(FIXEDCLAMP_TRIP) == FIXEDCLAMP_TRIPPED;
  }
  if (COMM_TRIP != 0 && COMM_TRIP != -1 ) { // I have middle_trip
    comm_trip = digitalRead(COMM_TRIP) == COMM_TRIPPED;
  }
  if (COMM_TRIP != 0 && COMM_TRIP != -1 ) { // I have a home_trip
    home_trip = ( digitalRead(HOME_TRIP) == HOME_TRIPPED);
  } else {
    home_trip = !HOME_TRIPPED;
  }
  /*
    Serial.print(">>>>>>>>>> data for : ");
    Serial.println(MY_CLAMP);
    Serial.print("Trips - home : \t");
    Serial.println(home_trip);
    Serial.print("Trips - mid : \t");
    Serial.println(middle_trip);
    Serial.print("Trips - fixedclamp : \t");
    Serial.println(fixedclamp_trip);
    Serial.print("Trips - comm : \t");
    Serial.println(comm_trip);
    Serial.println(" >> begun");
    Serial.print(PC_END);
  */
  if ( middle_trip != last_middle_trip || fixedclamp_trip != last_fixedclamp_trip || comm_trip != last_comm_trip ) {
    last_middle_trip = middle_trip;
    last_fixedclamp_trip = fixedclamp_trip;
    last_comm_trip = comm_trip;
    int ack = 0;
    while ( ack != COMM_CHAR + 1 ) {
      Serial.println("GIVING VALUES TO OTHER MOTOR !!!!!!!!");
      Serial1.print(COMM_CHAR);
      if (MIDDLE_TRIP != 0 && MIDDLE_TRIP != -1 ) { // I have middle_trip
        Serial1.print(last_middle_trip);
      } else {
        Serial1.print('2');
      }
      if (FIXEDCLAMP_TRIP != 0 && FIXEDCLAMP_TRIP != -1 ) { // I have middle_trip
        Serial1.print(last_fixedclamp_trip);
      } else {
        Serial1.print('2');
      }
      if (COMM_TRIP != 0 && COMM_TRIP != -1 ) { // I have middle_trip
        Serial1.print(last_comm_trip);
      } else {
        Serial1.print('2');
      }

      long int start_time_ack = millis();
      while (Serial1.available() == 0) {
        if ( millis() - start_time_ack > 7000 ) {
          Serial.print( " timeout " );
          Serial.println((int) (start_time_ack - millis()));
          
          start_time_ack = -1;
          break;
        }
      }
      if ( start_time_ack != -1 ) {
        ack = Serial1.read();
        Serial.print("ACK got : ");
        Serial.println(ack);
      } else {
        ack = COMM_CHAR - 1;
        Serial.println("ACK failed due to tiemout :(");
      }
    }
    Serial.println(ack);
  }




  if ( Serial1.available() && Serial1.peek() == COMM_CHAR ) {
    Serial1.read(); // to bypass COMM_CHAR
    int ack = COMM_CHAR + 1;
    Serial.println("GETTING VALUES FROM OTHER MOTOR !!!!!!!!");
    int start_time_trips = millis();
    while (Serial1.available() < 3) {
      if ( millis() - start_time_trips > 5000 ) {
        start_time_trips = -1;
        Serial.print( " timeout " );
        ack -= 1;
        break;
      }
    }

    if ( start_time_trips != -1 ) {
      Serial.print("Got 4 vals");
      char trip = Serial1.read();
      if ( trip == '0' || trip == '1' ) { // remove garbage data
        middle_trip = trip - '0';
        last_middle_trip = middle_trip;
      } else if ( trip == '2' && MIDDLE_TRIP == -1 ) {
        middle_trip = !MIDDLE_TRIPPED;
        last_middle_trip = middle_trip;
      } else if ( trip != '1' && trip != '2' && trip != '0' ) {
        ack -= 1;
      }
      trip = Serial1.read();
      if ( trip == '0' || trip == '1' ) { // remove garbage data
        fixedclamp_trip = trip - '0';
        last_fixedclamp_trip = fixedclamp_trip;
      } else if ( trip == '2' && FIXEDCLAMP_TRIP == -1 ) {
        fixedclamp_trip = !FIXEDCLAMP_TRIPPED;
        last_fixedclamp_trip = fixedclamp_trip;
      } else if ( trip != '1' && trip != '2' && trip != '0' ) {
        ack -= 1;
      }
      trip = Serial1.read();
      if ( trip == '0' || trip == '1' ) { // remove garbage data
        comm_trip = trip - '0';
        last_comm_trip = comm_trip;
      } else if ( trip == '2' && COMM_TRIP == -1 ) {
        comm_trip = !COMM_TRIPPED;
        last_comm_trip = comm_trip;
      } else if ( trip != '1' && trip != '2' && trip != '0' ) {
        ack -= 1;
      }

    }
    Serial.print("SENT ACK >>>>");
    Serial.print(ack);
    Serial.print(" / ");
    Serial.println(int(COMM_CHAR));
    Serial1.print(char ( ack ));
  }

}



