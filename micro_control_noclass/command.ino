void master_ui() {

  char c = PC.read();

  // RESET THE BOT' POSITION
  if ( c == 'r' ) {
    while (!PC.available());
    char c2 = PC.read();
    if ( c2 == MY_CLAMP ) {
      // MYCLAMP CODE
      PC.print("MY CLAMP motor moving to home trip switch ... ");
      go_home();
      PC.println("DONE");
      pos = 0;
      PC.println("MY CLAMP motor pos set back to 0 ");

    }
    else if (c2 == NEXT_CLAMP) {
      // NEXT CODE
      NEXT.print('r');
      NEXT.print(NEXT_CLAMP);
      listen();
    }
  }
  //-------------------------------------------------------------------------------
  // SET MODE
  if ( c == 's' ) {
    while (!PC.available());
    char c2 = PC.read();
    if ( c2 == MY_CLAMP ) {
      //MYCLAMP CODE
      pos = 0;
      PC.println("MY CLAMP motor pos set at 0 ");
    }
    else if (c2 == NEXT_CLAMP) {
      //NEXT CODE
      NEXT.print('s');
      NEXT.print(NEXT_CLAMP);
      listen();
      PC.print("NEXT motor pos set at 0 ");
    }
  }
  //---------------------------------------------------------------------------------
  // PRINT STUFF
  if ( c == 'w' ) {
    while (!PC.available());
    char c2 = PC.read();
    if ( c2 == MY_CLAMP ) {
      PC.print("MY CLAMP Motor ");
      PC.print("\t Position = ");
      PC.println(pos);
    }
    else if ( c2 == NEXT_CLAMP ) {
      NEXT.print('w');
      NEXT.print(NEXT_CLAMP);
      listen();
    }
  }
  //---------------------------------------------------------------------------------
  // PWM MODE
  else if ( c == 'v' ) {
    while (!PC.available());
    char c2 = PC.read();
    if ( c2 == MY_CLAMP ) {
      // MYCLAMP CODE
      int vel = PC.parseInt();
      PC.print("MY CLAMP motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      while ( run( ( vel < 0 ) ? LEFT : RIGHT, abs(vel)) ) {
        if ( PC.available() && PC.read() == 'q' ) {
          run(STOP, 255);
          break;
        }
      }
      PC.println("DONE");
    }
    else if ( c2 == NEXT_CLAMP ) {
      // NEXT CODE
      NEXT.print('v');
      NEXT.print(NEXT_CLAMP);
      int vel = PC.parseInt();
      NEXT.print(vel);
      listen();
    }
  }
  //----------------------------------------------------------------------
  // POSITION MODE
  else if ( c == 'm' ) {
    while (!PC.available());
    char c2 = PC.read();
    if ( c2 == MY_CLAMP ) {
      int pos = PC.parseInt();
      PC.println("Left motor moving ... pos = ");
      PC.print(pos);
      PC.print(" -> ");
      while ( goto_pos(pos) == 0 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          run(STOP, 255);
          break;
        }
      }
      PC.println(pos);
    }
    else if ( c2 == NEXT_CLAMP ) {
      NEXT.print('m');
      NEXT.print('r');
      float pos = PC.parseFloat();
      NEXT.print(pos);
      listen();
    }
  }

  // ACTUATIONS
  if ( c == 'p' ) {
    while (!PC.available());
    char c2 = PC.read();
    if ( c2 == MY_CLAMP ) {
      // MYCLAMP CODE 
      while (!PC.available());
      char c3 = PC.read();
      if ( c3 == 'c' ) {
        PC.println("Closing piston LEFT ");
        piston(CLOSE);
      }
      else {
        PC.println("Opening piston LEFT ");
        piston(OPEN);
      }
    }
    else if ( c2 == NEXT_CLAMP ) {
      // NEXT CODE
      while (!PC.available());
      char c3 = PC.read();
      if ( c3 == 'c' ) {
        NEXT.print('p');
        NEXT.print(NEXT_CLAMP);
        NEXT.print('c');
        listen();
      }
      else {
        NEXT.print('p');
        NEXT.print(NEXT_CLAMP);
        NEXT.print('o');
        listen();
      }
    }
    else if ( c2 == 'x' ) {
      while (!PC.available());
      char c3 = PC.read();
      if ( c3 == 'c' ) {
        // MYCLAMP CODE
        PC.println("Closing piston BOTH ");
        piston(CLOSE);
        // NEXT CODE
        NEXT.print('p');
        NEXT.print(NEXT_CLAMP);
        NEXT.print('c');
        listen();
      }
      else {
        // MYCLAMP CODE        
        PC.println("Opening piston BOTH ");
        piston(OPEN);
        // NEXT CODE
        NEXT.print('p');
        NEXT.print(NEXT_CLAMP);
        NEXT.print('o');
        listen();
      }
    }
  }
  //----------------------------------------------------------------------------
  // DECLARE EMERGENCY STOP
  else if ( c == 'q' ) {
    // MYCLAMP CODE
    PC.println("Both motors STOPPED !");
    run(STOP, 255);
    // NEXT CODE
    NEXT.print('q');
    listen();
  }

  // DECLARE EMERGECNY STOP AND OPEN PISTONS
  else if ( c == 'z' ) {
    // MYCLAMP CODE
    PC.println("Both motors STOPPED !");
    run(STOP, 255);
    piston(OPEN);
    // NEXT CODE    
    NEXT.print('z');
    listen();
  }

  while (PC.available());
  PC.read();
}


