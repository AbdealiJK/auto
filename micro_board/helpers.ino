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
  while (!SLAVE && temp != PC_END)
  {
    if (NEXT.available()) {
      temp  = NEXT.read();
/*      if ( temp == COMM_CHAR ) {
        NEXT.read();
        NEXT.read();
        NEXT.read();
      }
*/
      PC.print( temp );
    }
    if ( PC.available() && PC.peek() == 'q' ) {
      PC.read();
      NEXT.print('q'); // charachter to be sent to slave for emergency stop
    }
  }
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
    update_trips();
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
    while(!Serial.available() ) {
      Serial.println("byebye");
      delay(1000);
    }
    while(Serial.available())
        Serial.read();
      
  }
}
