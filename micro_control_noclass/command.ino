void master_ui() {

  char c = PC.read();

  if ( c == MY_CLAMP ) {
    // >>>>>>>>>>>>>>>>>>>>> CODE FOR MY CLAMP !!!!!!!!!!!!!!!!!
    while (!PC.available());
    char c2 = PC.read();
    if ( c2 == 'r' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> RESET
      PC.print(MY_CLAMP);
      PC.print("-motor moving to home trip switch ... ");
      go_home();
      PC.println("DONE");
      pos = 0;
      PC.print(MY_CLAMP);
      PC.println("-motor pos set back to 0 ");
      PC.print(PC_END);
    } 
    else if ( c2 == 'w' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> WATCH
      PC.print(MY_CLAMP);
      PC.print("-Motor ");
      PC.print("\t Position = ");
      PC.println(pos);
      PC.print(PC_END);      
    } 
    else if ( c2 == 'v' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> VELOCITY
      int vel = pc_get_int();
      PC.print("-motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      while ( run( ( vel < 0 ) ? LEFT : RIGHT, abs(vel)) ) {
        if ( PC.available() && PC.read() == 'q' ) {
          run(STOP, 255);
          PC.print(" manual broken - ");
          break;
        }
      }
      PC.println("DONE");
      PC.print(PC_END);
    } 
    else if(c2 == 'm' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> POSITION
      int pos = PC.parseInt();
      PC.print(MY_CLAMP);
      PC.print(" motor moving ... pos = ");
      PC.print(pos);
      PC.print(" -> ");
      while ( goto_pos(pos) == 0 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          run(STOP, 255);
          PC.print(" manual broken - ");          
          break;
        }
      }
      PC.print(pos);
      PC.println(" ... DONE");
      PC.print(PC_END);
    } 
    else if( c2 == 'p' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PISTON
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
  else if ( c == NEXT_CLAMP ) {
    // >>>>>>>>>>>>>>>>>>>>> MAKE THE OTHER GUY DO IT !!!!!!!!!!!!!!!!!
    NEXT.write(c);
    delay(2);
    while(PC.available())
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

  while (PC.available())
    PC.read();
}



