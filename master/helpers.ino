int run(int dir, int pwm) {
  update(HOME_TRIP);
  update(MID_TRIP);

  if ( home_trip && dir == HOME ) {
    digitalWrite(MOTOR_1, 0); digitalWrite(MOTOR_2, 0); analogWrite(MOTOR_PWM, 255);
    return 0;
  }

  if ( mid_trip && dir == MID ) {
    digitalWrite(MOTOR_1, 0); digitalWrite(MOTOR_2, 0); analogWrite(MOTOR_PWM, 255);
    return 0;
  }

  switch ( dir ) {
    case STOP : dir = 0;  break;
    case HOME : dir = 1;  break;
    case MID :  dir = 2;  break;
    default :   dir = -1; break;
  }

  if ( dir != -1 ) {
    digitalWrite(MOTOR_1, dir / 2);
    digitalWrite(MOTOR_2, dir % 2);
    analogWrite(MOTOR_PWM, pwm);
  }
  return 1;
}

void piston(int v) {
  digitalWrite(PISTON_PIN, v == CLOSE);
}

// ------------------------------------------------------------------------------------

void update(int tr) {
  long int temp = 0, lim = 0;
  bool *val;
  int tripped, pin;
  long int loops = -1;

  if ( tr == HOME_TRIP ) {
    val = &home_trip;  pin = HOME_TRIP;   tripped = HOME_TRIPPED;  loops = 1;
  } else if ( tr == MID_TRIP ) {
    val = &mid_trip;  pin = MID_TRIP;   tripped = MID_TRIPPED;     loops = 1;
  } else if ( tr == COMM_TRIP ) {
    val = &comm_trip;  pin = COMM_TRIP;   tripped = COMM_TRIPPED;   loops = 1;
  } else if ( tr == LADDER_IR ) {
    val = &ladder_ir;  pin = LADDER_IR;   tripped = LADDER_IR_FOUND;   loops = 1000;
  } else if ( tr == COMM_IR ) {
    val = &comm_ir;  pin = COMM_IR;   tripped = COMM_IR_FOUND;   loops = 10000;
  } else if ( tr == MID_IR ) {
    val = &mid_ir;  pin = MID_IR;   tripped = MID_IR_FOUND;   loops = 10000;
  }

  if ( loops > 0 && pin >= 0) {
    long int temp;
    for ( long int lim = 0; lim < loops; lim++ ) {
      temp += digitalRead(pin);
    }

    if ( temp > 0.7 * loops ) {
      if ( tripped == 1 ) {
        *val = 1;
      } else {
        *val = 0;
      }
    } else {
      if ( tripped == 1 ) {
        *val = 0;
      } else {
        *val = 1;
      }
    }
  }
}

// ----------------------------------------------------------------------------------------

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
  if ( !SLAVE ) {
    PC.println(F("Oops, SLAVE not found :(((("));
    return;
  }
  char temp = !COMM_END;
  Serial.print(F("Waiting for next"));
  while (temp != COMM_END) {
    if (SLAVE.available()) {
      temp  = SLAVE.read();
      PC.print( temp );
    }
    if ( PC.available() && PC.peek() == STOP ) {
      PC.read();
      Serial.println(F("Master > Stopping Slave "));
      SLAVE.print(STOP); // charachter to be sent to slave for emergency stop
    }
  }
  Serial.print(F("DONE"));
}

int q_stop () {
  if ( PC.available() && PC.peek() == STOP ) {
    SLAVE.print(STOP);
    run(STOP, 255);
    PC.println(F("MASTER > ...manual stop... "));
    Serial.println(F("STOPPED"));
    PC.print(COMM_END);
    listen();
    return 1;
  }
  return 0;
}

bool quit_or_continue() {
  PC.println(F("Press 'c' ... "));
  while ( 1 ) {
    if ( PC.available() && PC.peek() == 'q' ) return 1;
    if ( PC.available() && PC.peek() == 'c' ) {
      PC.read();
      return 0;
    }
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


