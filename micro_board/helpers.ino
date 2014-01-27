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

void listen()
{
  char temp = !PC_END;
  Serial.print("Waiting for next");
  while (NEXT && temp != PC_END)
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



void test () {
  // Display initial values :
  while ( !Serial );
  Serial.println("5sec delay");
  Serial.println("This is the test mode. If you wish to go to normal mode, uncomment 'test()' in setup");
  delay(5000);
  while (1) {
    update_middle_trip();
    update_home_trip();
    update_fixedclamp_trip();
    //    update_avs();
    Serial.print("My clamp : \t");
    Serial.println(MY_CLAMP);
    Serial.print("Next clamp : \t");
    Serial.println(NEXT_CLAMP);
    Serial.print("Trips - home : \t");
    Serial.println(digitalRead(HOME_TRIP));
    Serial.print("Trips - mid : \t");
    if ( MIDDLE_TRIP )   Serial.println(digitalRead(MIDDLE_TRIP));
    else                 Serial.println("Middle trip is not with me");
    Serial.print("Trips - fixedclamp : \t");
    if ( FIXEDCLAMP_TRIP )    Serial.println(digitalRead(FIXEDCLAMP_TRIP));
    else                      Serial.println("Fixedclamp is not with me");
    Serial.print("Trips - comm : \t");
    if ( COMM_TRIP )          Serial.println(digitalRead(COMM_TRIP));
    else                      Serial.println("Communication trip is not with me");
    Serial.print("AVS Value : \t");
    Serial.println(avs_value);
    Serial.println(" TESTS done");
    while (!Serial.available() ) {
      Serial.println("byebye");
      delay(1000);
    }
    while (Serial.available())
      Serial.read();

  }
}




/*
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



Sensors :
CLAMP L
1. Home trip switch
2. Middle trip switch
3. AVS
CLAMP R
1. Home trip switch
2. Ladder trip switch
3. AVS
GEN
1. Comm trip switch


Actuations :
CLAMP L
1. Piston
2. Motor
3.
CLAMP R
1. Piston
2. Motor
3. Servo
GEN
1. Peepee


UI :
CLAMP L
1. Autonic
2. 1 trip
3. HALL x2
4. Servo
CLAMP R
1. Autonic
2. 1 trip
3. HALL x2



(7)
*/

