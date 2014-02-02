void ui() {

  if ( ! PC.available() )
    return;

  char c = PC.peek();
  Serial.print("GOt :");
  Serial.println(c);
  if ( c == 'l' ) {
    // >>>>>>>>>>>>>> CODE FOR MY CLAMP !!!!!!!!!!!!!!!!!
    PC.read();
    while (!PC.available());
    char c2 = PC.read();
    if ( c2 == 'w' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> WATCH
      // Display initial values :

      update_home_trip();
      update_middle_trip();
      update_fixedclamp_trip();
      update_ir_trip();
      PC.print(">>>>>>>>>> data for master : ");
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
      int vel = pc_get_int();
      PC.print("master-motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
        if ( q_stop() ) break;
      }
      PC.println("DONE");
      PC.print(PC_END);
    }
    else if ( c2 == 'f' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>> MOTION with fixed clamp also
      int vel = pc_get_int();
      PC.print("master-motor moving (with fixed clamp) at pwm = ");
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
      int vel = pc_get_int();
      PC.print("master-motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
        if ( q_stop() ) break;
        update_ir_trip();
        if ( ir_trip ) {
          run ( STOP, 255 );
          PC.print("IR reached.... ");
          PC.println("master-clamp Now in middle position");
          break;
        }
      }
      PC.println("DONE");
      PC.print(PC_END);
    }
    else if ( c2 == 'p' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PISTON
      while (!PC.available());
      if ( PC.read() == 'c' ) {
        PC.print("Closing piston master");
        piston(CLOSE);
      } else {
        PC.print("Opening piston master");
        piston(OPEN);
      }
      PC.print(PC_END);
    }
    else if ( c2 == 'c' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> VELOCITY
      while (!PC.available());
      if ( PC.read() == 'c' ) {
        PC.print("Waiting for the comm to occur");
        while ( !comm_ir_trip ) {
          update_comm_ir_trip();
        }
        delay(1000);
        PC.print("Closing piston master");
        piston(CLOSE);
      } else {
        PC.print("Waiting for the comm to occur");
        while ( !comm_ir_trip ) {
          update_comm_ir_trip();
        }
        delay(1000);
        PC.print("Opening piston master");
        piston(OPEN);
      }
      PC.print(PC_END);
    }

  }
  else if ( c == NEXT_CLAMP ) {
    // >>>>>>>>>>>>>>>>>>>>> MAKE THE OTHER GUY DO IT !!!!!!!!!!!!!!!!!
    delay(2);
    if (!(NEXT))
      Serial.println("Other clamp not present :P ");
    else {
      Serial.println("Sending it to the other clamp");
      while (PC.available())
        NEXT.write(PC.read());
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

