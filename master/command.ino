void ui() {

  if ( ! PC.available() )
    return;

  char c = PC.peek();
  Serial.print(F("GOt :"));
  Serial.println(c);
  if ( c == 'l' ) {
    // >>>>>>>>>>>>>> CODE FOR MY CLAMP !!!!!!!!!!!!!!!!!
    PC.read();
    while (!PC.available());
    char c2 = PC.read();
    if ( c2 == 'w' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> WATCH
      // Display initial values :
      
      update_trip(HOME_TRIP);
      update_trip(MIDDLE_TRIP);
      update_trip(FIXEDCLAMP_TRIP);
      update_trip(IR_TRIP);
      PC.print(F(">>>>>>>>>> data for master : "));
      PC.print(F("Trips - home : \t"));
      PC.println(home_trip);
      PC.print(F("Trips - mid : \t"));
      PC.println(middle_trip);
      PC.print(F("Trips - fixedclamp : \t"));
      PC.println(fixedclamp_trip);
      PC.print(F("Trips - comm : \t"));
      PC.println(comm_trip);
      PC.print(F("Trips - ir : \t"));
      PC.println(ir_trip);
      PC.println(F(" >> begun"));
      PC.print(COMM_END);
    }
    else if ( c2 == 'v' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> VELOCITY
      int vel = pc_get_int();
      PC.print(F("master-motor moving at pwm = "));
      PC.print(vel);
      PC.print(F(" ... "));
      while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
        if ( q_stop() ) break;
      }
      PC.println(F("DONE"));
      PC.print(COMM_END);
    }
    else if ( c2 == 'f' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>> MOTION with fixed clamp also
      int vel = pc_get_int();
      PC.print(F("master-motor moving (with fixed clamp) at pwm = "));
      PC.print(vel);
      PC.print(F(" ... "));
      while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
        if ( q_stop() ) break;
        update_trip(FIXEDCLAMP_TRIP);
        if ( fixedclamp_trip ) {
          run ( STOP, 255 );
          PC.println(F("fixed clamp pressed ... "));
          break;
        }
      }
      PC.println(F("DONE"));
      PC.print(COMM_END);
    }
    else if ( c2 == 'i'  ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>. IR ( only for SLAVE )
      int vel = pc_get_int();
      PC.print(F("master-motor moving at pwm = "));
      PC.print(vel);
      PC.print(F(" ... "));
      while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
        if ( q_stop() ) break;
        update_trip(IR_TRIP);
        if ( ir_trip ) {
          run ( STOP, 255 );
          PC.print(F("IR reached.... "));
          PC.println(F("master-clamp Now in middle position"));
          break;
        }
      }
      PC.println(F("DONE"));
      PC.print(COMM_END);
    }
    else if ( c2 == 'p' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PISTON
      while (!PC.available());
      if ( PC.read() == 'c' ) {
        PC.print(F("Closing piston master"));
        piston(CLOSE);
      } else {
        PC.print(F("Opening piston master"));
        piston(OPEN);
      }
      PC.print(COMM_END);
    }
    else if ( c2 == 'c' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> VELOCITY
      while (!PC.available());
      if ( PC.read() == 'c' ) {
        PC.print(F("Waiting for the comm to occur"));
        while ( !comm_ir_trip ) {
          update_trip(COMM_IR_TRIP);
        }
        delay(1000);
        PC.print(F("Closing piston master"));
        piston(CLOSE);
      } else {
        PC.print(F("Waiting for the comm to occur"));
        while ( !comm_ir_trip ) {
          update_trip(COMM_IR_TRIP);
        }
        delay(1000);
        PC.print(F("Opening piston master"));
        piston(OPEN);
      }
      PC.print(COMM_END);
    }

  }
  else if ( c == 'r' ) {
    // >>>>>>>>>>>>>>>>>>>>> MAKE THE OTHER GUY DO IT !!!!!!!!!!!!!!!!!
    delay(2);
    if ( ! SLAVE )
      PC.println(F("Oops, SLAVE not found :(((("));
    else {
      Serial.println(F("Sending it to the other clamp"));
      while (PC.available())
        SLAVE.write(PC.read());
      listen();
    }
  }

  if ( c == '4' ) {
    PC.read();
    ladder () ;
  }
  else if ( c == '3' ) {
    PC.read();
    polewalk() ;
  }
  q_stop();
}










