int run(int dir, int pwm) {
  update_home_trip();

  if ( home_trip && dir == HOME ) {
    digitalWrite(MOTOR_1, 0);
    digitalWrite(MOTOR_2, 0);
    analogWrite(MOTOR_PWM, 255);
    MASTER.println("\t Trip switch HOME pressed for some motor ! ");
    return 0;
  }

  digitalWrite(MOTOR_1, dir / 2);
  digitalWrite(MOTOR_2, dir % 2);
  analogWrite(MOTOR_PWM, pwm);
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

void update_ir_trip() {
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

// ------------------------------------------------
int get_int(HardwareSerial Ser) {
  int temp = 0, next_val, neg = 1;
  char temp_c;

  while (!Ser.available());
  delay(2);
  next_val = Ser.peek();
  if ( next_val == '-' ) {
    neg = -1;
    Ser.read();
    next_val = Ser.peek();
  }
  while ( Ser.available() && next_val <= '9' && next_val >= '0' ) {
    Ser.read();
    temp *= 10;
    temp += next_val - '0';
    next_val = Ser.peek();
  }
  return temp * neg;
}

// ------------------------------------------------
int q_stop () {
  if ( MASTER.available() && MASTER.peek() == STOP ) {
    run(STOP, 255);
    MASTER.println("SLAVE > manual stop ");
    MASTER.print(COMM_END);
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


