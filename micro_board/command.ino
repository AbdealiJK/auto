void ui() {

  if ( ! PC.available() )
    return;

  char c = PC.peek();
  Serial.print("GOt :");
  Serial.println(c);
  if ( c == MY_CLAMP ) {
    // >>>>>>>>>>>>>> CODE FOR MY CLAMP !!!!!!!!!!!!!!!!!
    PC.read();
    while (!PC.available());
    char c2 = PC.read();
    if ( c2 == 'w' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> WATCH
      // Display initial values :
      if ( SLAVE ) Serial.print("Got W");
      update_home_trip();
      update_middle_trip();
      update_fixedclamp_trip();
      update_ir_trip();
      PC.print(">>>>>>>>>> data for : ");
      PC.println(MY_CLAMP);
      PC.print("Trips - home : \t");
      PC.println(home_trip);
      PC.print("Trips - mid : \t");
      PC.println(middle_trip);
      PC.print("Trips - fixedclamp : \t");
      PC.println(fixedclamp_trip);
      PC.print("Trips - comm : \t");
      PC.println(comm_trip);
      PC.print("Trips - ir : \t");
      PC.println(ir_trip);
      PC.println(" >> begun");
      PC.print(PC_END);
    }
    else if ( c2 == 'v' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> VELOCITY
      if ( SLAVE ) PC.print("Got V");
      int vel = pc_get_int();
      PC.print(MY_CLAMP);
      PC.print("-motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
        if ( q_stop() ) break;
      }
      PC.println("DONE");
      PC.print(PC_END);
    }
    else if ( c2 == 'f' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>> MOTION with fixed clamp also
      if ( SLAVE ) Serial.print("Got F");
      int vel = pc_get_int();
      PC.print(MY_CLAMP);
      PC.print("-motor moving (with fixed clamp) at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
        if ( q_stop() ) break;
        update_fixedclamp_trip();
        if ( fixedclamp_trip ) {
          run ( STOP, 255 );
          PC.println("fixed clamp pressed ... ");
          break;
        }
      }
      PC.println("DONE");
      PC.print(PC_END);
    }
    else if ( c2 == 'i'  ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>. IR ( only for SLAVE )
      if ( SLAVE ) PC.print("Got I");
      int vel = pc_get_int();
      PC.print(MY_CLAMP);
      PC.print("-motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
        if ( q_stop() ) break;
        update_ir_trip();
        if ( ir_trip ) {
          run ( STOP, 255 );
          PC.print("IR reached.... ");
          PC.print(MY_CLAMP);
          PC.println("-clamp Now in middle position");
          break;
        }
      }
      PC.println("DONE");
      PC.print(PC_END);
    }
    else if ( c2 == 'p' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PISTON
      while (!PC.available());
      if ( PC.read() == 'c' ) {
        if ( SLAVE ) Serial.print("Got PC");
        PC.print("Closing piston  ");
        PC.println(MY_CLAMP);
        piston(CLOSE);
      } else {
        if ( SLAVE ) Serial.print("Got PO");
        PC.print("Opening piston ");
        PC.println(MY_CLAMP);
        piston(OPEN);
      }
      PC.print(PC_END);
    }
    else if ( c2 == 'c' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> VELOCITY
      while (!PC.available());
      if ( PC.read() == 'c' ) {
        if ( SLAVE ) Serial.print("Got CC");
        PC.print("Waiting for the comm to occur");
        while ( !comm_ir_trip ) {
          update_comm_ir_trip();
        }
        delay(1000);
        PC.print("Closing piston  ");
        PC.println(MY_CLAMP);
        piston(CLOSE);
      } else {
        if ( SLAVE ) Serial.print("Got CO");
        PC.print("Waiting for the comm to occur");
        while ( !comm_ir_trip ) {
          update_comm_ir_trip();
        }
        delay(1000);
        PC.print("Opening piston  ");
        PC.println(MY_CLAMP);
        piston(OPEN);
      }
      PC.print(PC_END);
    }
    else if ( c2 == 's' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> VELOCITY
      while (!PC.available());
      if ( PC.read() == 'c' ) {
        if ( SLAVE ) Serial.print("Got CC");
        PC.print("Waiting for the comm to occur");
        while ( !comm_ir_trip ) {
          update_comm_ir_trip();
        }
        delay(1000);
        PC.print("Closing piston  ");
        PC.println(MY_CLAMP);
        piston(CLOSE);
      } else {
        if ( SLAVE ) Serial.print("Got CO");
        PC.print("Waiting for the comm to occur");
        while ( !comm_ir_trip ) {
          update_comm_ir_trip();
        }
        delay(1000);
        PC.print("Opening piston  ");
        PC.println(MY_CLAMP);
        piston(OPEN);
      }
      PC.print(PC_END);
    }

  }
  else if ( c == NEXT_CLAMP && SLAVE == 0 ) {
    // >>>>>>>>>>>>>>>>>>>>> MAKE THE OTHER GUY DO IT !!!!!!!!!!!!!!!!!
    delay(2);
    
    
      Serial.println("Sending it to the other clamp");
      mySerial.println("Sending it to the other clamp");
      while (PC.available())
        {
          char c=PC.read();
          for(int i=0;i<10;i++)
          {
        mySerial.write(c);
        Serial.write(c);
          }
          delay(2);
      }
      listen();
    
  }

  if ( !SLAVE ) {
    if ( c == '4' ) {
      PC.read();
      ladder();
    }
    else if ( c == '3' ) {
      PC.read();
      polewalk() ;
    }
    else if ( c == '2' ) {
      PC.read();
      swing();
    }
    else if ( c == '1' ) {
      PC.read();
      seesaw();
    }
    else if ( c == '5' ) {
      // move left motor to extreme
      PC.println("Need to move left clamp to the extreme.");
      QUIT_OR_CONTINUE;
      while ( run( HOME, 255 ) ) {
        if ( q_stop() ) break;
      }
      run( MID, 255 );
      delay(100);
      run( STOP, 255 );
      NEXT.print('r');
      NEXT.print('v');
      NEXT.print(-255);
      listen();

      // move right motor to middle
      PC.println("Right clamp needs to go to the middle position.");
      QUIT_OR_CONTINUE;
      NEXT.print('r');
      NEXT.print('i');
      NEXT.print(255);
      listen();

      // make right motor move a small distance
      PC.println("Need to move right clamp slightly more.");
      QUIT_OR_CONTINUE;
      NEXT.print('r');
      NEXT.print('v');
      NEXT.print(200);
      delay(400);
      NEXT.print('q');
    }
  }
  q_stop();
}

