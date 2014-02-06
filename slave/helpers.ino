int run(int dir, int pwm) {
  update_home_trip();

  if ( home_trip && dir == HOME ) {
    digitalWrite(MOTOR_1, 0);
    digitalWrite(MOTOR_2, 0);
    analogWrite(MOTOR_PWM, 255);
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

// ------------------------------------------------
void update_home_trip() {
  if (HOME_TRIP != -1 ) {
    home_trip = ( digitalRead(HOME_TRIP) == HOME_TRIPPED);
  }
}

void update_mid_ir() {
  if ( MID_IR != -1 ) { // Flicker correction for IR.
    long int temp = 0, lim = 0;
    for ( lim = 0; lim < 1000; lim++ ) {
      temp += digitalRead(MID_IR) == MID_IR_FOUND;
    }
    //      Serial.println(temp);
    if ( temp > 0.7 * lim )
      mid_ir = 1;
    else
      mid_ir = 0;
  }
}

// ------------------------------------------------
int get_int() {
  int temp = 0, next_val, neg = 1;
  char temp_c;

  while (!MASTER.available());
  delay(2);
  next_val = MASTER.peek();
  if ( next_val == '-' ) {
    neg = -1;
    MASTER.read();
    next_val = MASTER.peek();
  }
  while ( MASTER.available() && next_val <= '9' && next_val >= '0' ) {
    MASTER.read();
    temp *= 10;
    temp += next_val - '0';
    next_val = MASTER.peek();
  }
  return temp * neg;
}

// ------------------------------------------------
int q_stop () {
  if ( MASTER.available() && MASTER.peek() == STOP ) {
    run(STOP, 255);
    MASTER.read();
    MASTER.println(F("SLAVE > ...manual stop... "));
    MASTER.print(COMM_END);
    Serial.println("Slave received 'q'");
    return 1;
  }
  return 0;
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


