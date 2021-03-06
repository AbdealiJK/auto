// ------------------------------------------------
int run(int dir, int pwm) {
  update_home_trip();
  update_middle_trip();

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
    PC.println("\t Trip switch MIDDLE pressed for some motor ! ~");
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

void update_middle_trip() {
  if ( ! SLAVE && MIDDLE_TRIP != -1 ) {
    middle_trip = digitalRead(MIDDLE_TRIP) == MIDDLE_TRIPPED;
  }

}
void update_comm_trip() {
  if ( ! SLAVE && COMM_TRIP != -1 ) {
    comm_trip = digitalRead(COMM_TRIP) == COMM_TRIPPED;
  }

}

void update_comm_ir_trip() {
  if ( ! SLAVE && COMM_IR_TRIP != -1 ) {
    long int temp = 0, lim = 0;
    for ( lim = 0; lim < 10000; lim++ ) {
      temp += digitalRead(COMM_IR_TRIP);
    }

    if ( temp > 0.7 * lim ) {
      if ( COMM_IR_TRIPPED == 1 ) {
        comm_ir_trip = 1;
      } else {
        comm_ir_trip = 0;
      }
    } else {
      if ( COMM_IR_TRIPPED == 1 ) {
        comm_ir_trip = 0;
      } else {
        comm_ir_trip = 1;
      }
    }
  }
}

void update_home_trip() {
  if (HOME_TRIP != -1 ) {
    home_trip = ( digitalRead(HOME_TRIP) == HOME_TRIPPED);
  }

}

void update_fixedclamp_trip() {
  //  long int ti = millis();
  if ( !SLAVE && FIXEDCLAMP_TRIP != -1 ) { // Flicker correction for fixed clamp.
    long int temp = 0, lim = 0;
    for ( lim = 0; lim < 1000; lim++ ) {
      temp += digitalRead(FIXEDCLAMP_TRIP) == FIXEDCLAMP_TRIPPED;
    }
    //      Serial.println(temp);
    if ( temp > 0.7 * lim )
      fixedclamp_trip = 1;
    else
      fixedclamp_trip = 0;
  }
}
void update_ir_trip() {
  //  long int ti = millis();
  if ( IR_TRIP != -1 ) { // Flicker correction for IR.
    long int temp = 0, lim = 0;
    for ( lim = 0; lim < 1000; lim++ ) {
      temp += digitalRead(IR_TRIP) == IR_TRIPPED;
    }
    //      Serial.println(temp);
    if ( temp > 0.7 * lim )
      ir_trip = 1;
    else
      ir_trip = 0;
  }
}


int pc_get_int() {
  int temp = 0, next_val, neg = 1;
  char temp_c;

  while (!PC.available());
  delay(2);
  next_val = PC.peek();
  if ( next_val == '-' ) {
    neg = -1;
    PC.read();
    next_val = PC.peek();
  }
  while ( PC.available() && next_val <= '9' && next_val >= '0' ) {
    PC.read();
    temp *= 10;
    temp += next_val - '0';
    next_val = PC.peek();
  }
  return temp * neg;
}

void listen() {
  char temp = !PC_END;
  Serial.print("Waiting for next");
  while (temp != PC_END)
  {
    if (NEXT.available()) {
      temp  = NEXT.read();
      PC.print( temp );
    }
    if ( PC.available() && PC.peek() == 'q' ) {
      PC.read();
      NEXT.print('q'); // charachter to be sent to slave for emergency stop
    }
  }
  Serial.print("DONENEEE");
}

int q_stop () {
  if ( PC.available() && PC.peek() == 'q' ) {
    if ( SLAVE ) Serial.print("Got Q");
    NEXT.print('q');
    run(STOP, 255);
    PC.print(MY_CLAMP);
    PC.println("-motor ...manual stop... ");
    Serial.println("STOPPED");
    PC.print(PC_END);
    listen();
    return 1;
  } else if ( PC.available() && PC.peek() == 'z' ) {
    if ( SLAVE ) Serial.print("Got Z");
    NEXT.print('z');
    run(STOP, 255);
    piston(OPEN);
    PC.print(MY_CLAMP);
    PC.println("-motor ...manual complete halt... ");
    PC.print(PC_END);
    listen();
    return 1;
  }
  return 0;
}

void proceed_comm() { 
  update_comm_trip();
  Serial.println("- waiting for comm trip ..... ");

  while ( !comm_trip ) {
    update_comm_trip();
//    Serial.print(MY_CLAMP);
//   Serial.println(  digitalRead(COMM_TRIP) );
    //  Serial.println("- waiting for comm trip ..... ");
    delay(10);
  }
}

/*

PINS on the Board
Motors :     4, 5
Motor pwm :  6
Actuation :
  Towards l298 - A5
  Away from l29813 --------------- 13 doesnt work for some reason
Trips :
  Trip1 - 11 (mid),
  Trip2 - 10 (home),
  Trip3 - a3
  Trip4 - a4
Autonic :    7
Hall : A0 - towards the 2 pins for power ( outer side of board)
       D8
Soft Serial :
  SCK  - outer side
  MISO -

L298 Pin config: (from left)
1 - current sense A
2 - out 1
3 - out 2
4 - 12V
5 - in1
6 - enable A
7 - in2
8 - gnd
9 - 5V
10 - in3
11 - enable B
12 - in4
13 - out3
14 - out4
15 - current sense B

*/
