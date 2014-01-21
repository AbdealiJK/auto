void ui() {

  if ( ! PC.available() )
    return;  
    
  char c = PC.peek();

  if ( c == MY_CLAMP ) {
    // >>>>>>>>>>>>>> CODE FOR MY CLAMP !!!!!!!!!!!!!!!!!
    PC.read();
    while (!PC.available());
    char c2 = PC.read();
    if ( c2 == 'r' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> RESET
      PC.print(MY_CLAMP);
      PC.print("-motor moving to home trip switch ... ");
      go_home();
      PC.println("DONE");
      PC.print(PC_END);
    }
    else if ( c2 == 'w' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> WATCH
      // Display initial values :
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
      PC.print("AVS Value : \t");
      PC.println(avs_value);
      PC.println(" >> begun");
      PC.print(PC_END);

      PC.print(PC_END);
    }
    else if ( c2 == 'v' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> VELOCITY
      int vel = pc_get_int();
      PC.print("-motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
        if ( PC.available() && PC.read() == 'q' ) {
          run(STOP, 255);
          PC.print(" manual broken - ");
          break;
        }
      }
      PC.println("DONE");
      PC.print(PC_END);
    }
    else if ( c2 == 'p' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PISTON
      while (!PC.available());
      if ( PC.read() == 'c' ) {
        PC.print("Closing piston  ");
        PC.println(MY_CLAMP);
        piston(CLOSE);
      }
      else {
        PC.print("Opening piston ");
        PC.println(MY_CLAMP);
        piston(OPEN);
      }
      PC.print(PC_END);
    }
  }
  else if ( c == NEXT_CLAMP && SLAVE == 0 ) {
    // >>>>>>>>>>>>>>>>>>>>> MAKE THE OTHER GUY DO IT !!!!!!!!!!!!!!!!!
    delay(2);
    while (PC.available())
      NEXT.write(PC.read());
    listen();
  }
  else if ( c == 'q' ) {
    // >>>>>>>>>>>>>>>>>>>>> STOP MOVING !!!!!!!!!!!!!!!!!
    run(STOP, 255);
    PC.print(MY_CLAMP);
    PC.println("-motor STOPPED !~");
    NEXT.print(c);
    listen();
  }
  else if ( c == 'z' ) {
    // >>>>>>>>>>>>>>>>>>>>> STOP IT ALL !!!!!!!!!!!!!!!!!
    run(STOP, 255);
    piston(OPEN);
    PC.print(MY_CLAMP);
    PC.println("-everything STOPPED !~");
    NEXT.print(c);
    listen();
  }

}

