void master_ui() {

  char c = PC.read();

  // RESET THE BOT
  if ( c == 'r' ) {
    while (!PC.available());
    char c2 = PC.read();
    if ( c2 == MY_CLAMP ) {
      // MYCLAMP CODE
      PC.print("MY CLAMP motor moving to home trip switch ... ");
      go_home();
      PC.println("DONE");
      reset();
      PC.println("MY CLAMP motor pos set back to 0 ");

    }
    else if (c2 == NEXT_CLAMP) {
      // NEXT CODE
      query('r');
      query(NEXT_CLAMP);
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
      reset();
      PC.println("MY CLAMP motor pos set at 0 ");
    }
    else if (c2 == NEXT_CLAMP) {
      //NEXT CODE
      query('s');
      query(NEXT_CLAMP);
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
      query('w');
      query(NEXT_CLAMP);
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
      query('v');
      query(NEXT_CLAMP);
      int vel = PC.parseInt();
      query(vel);
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
          stop();
          break;
        }
      }
      PC.println(pos);
    }
    else if ( c2 == NEXT_CLAMP ) {
      query('m');
      query('r');
      float pos = PC.parseFloat();
      query(pos);
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
        query('p');
        query(NEXT_CLAMP);
        query('c');
        listen();
      }
      else {
        query('p');
        query(NEXT_CLAMP);
        query('o');
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
        query('p');
        query(NEXT_CLAMP);
        query('c');
        listen();
      }
      else {
        // MYCLAMP CODE        
        PC.println("Opening piston BOTH ");
        piston(OPEN);
        // NEXT CODE
        query('p');
        query(NEXT_CLAMP);
        query('o');
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
    query('q');
    listen();
  }

  // DECLARE EMERGECNY STOP AND OPEN PISTONS
  else if ( c == 'z' ) {
    // MYCLAMP CODE
    PC.println("Both motors STOPPED !");
    run(STOP, 255);
    piston(OPEN);
    // NEXT CODE    
    query('z');
    listen();
  }

  while (PC.available());
  PC.read();
}








void simple_ui() {
  char c = PC.read();

  // RESET THE BOT
  if ( c == 'a' ) {
    if ( MY_CLAMP == 'l' ) {
      PC.print("Left motor moving to left trip switch ... ");
      while ( run(LEFT, 50) == 1 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          run(STOP, 255);
          break;
        }
      }
      PC.println("DONE");
      reset();
      PC.println("Left motor pos set back to 0 ;");
    }
    else {
    }
  }
  else if ( c == '\'' ) {
    if ( MY_CLAMP == 'r' ) {
      PC.print("Right motor moving to left trip switch ... ");
      while ( run(RIGHT, 50) == 1 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          run(STOP, 255);
          break;
        }
      }
      PC.println("DONE");
      reset();
      PC.println("Right motor pos set back to 0 ;");
    }
    else {
    }
  }

  // PRINT STUFF
  else if ( c == '4' || c == '5' || c == '6' || c == '7' ) {
    PC.print("Motor LEFT ");
    PC.print("\t Position = ");
    PC.println(pos);

  }

  // PWM MODE
  else if ( c == 's' ) {
    if ( MY_CLAMP == 'l' ) {
      int vel = PC.parseInt();
      PC.print("Left motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      while ( run( ( vel < 0 ) ? LEFT : RIGHT, abs(vel)) ) {
        if ( PC.available() && PC.read() == 'q' ) {
          run(STOP, 255);
          break;
        }
      }
      PC.println("DONE");
    } else {
      int vel = PC.parseInt();
    }
  } else if ( c == ';' ) {
    while (!PC.available());
    if ( MY_CLAMP == 'r' ) {
      int vel = PC.parseInt();
      PC.print("Right motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      while ( run( ( vel < 0 ) ? LEFT : RIGHT, abs(vel)) ) {
        if ( PC.available() && PC.peek() == 'q' ) {
          while (PC.available()) PC.println(PC.read());
          run(STOP, 255);
          break;
        }
      }
      PC.println("DONE");
    } else {
      int vel = PC.parseInt();
    }
  }

  // POSITION MODE
  else if ( c == 'x' ) {
    if ( MY_CLAMP == 'l' ) {
      while ( ! PC.available() );
      int pos = PC.parseInt();
      PC.println("Left motor moving ... pos = ");
      PC.print(pos);
      PC.print(" -> ");
      while ( goto_pos(pos) == 0 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          stop();
          break;
        }
      }
      PC.println(pos);
    }
    else {
    }
  } else if ( c == '.' ) {
    if ( MY_CLAMP == 'r' ) {
      while ( ! PC.available() );
      int pos = PC.parseInt();
      PC.println("Right motor moving ... pos = ");
      PC.print(pos);
      PC.print(" -> ");
      while ( goto_pos(pos) == 0 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          stop();
          break;
        }
      }
      PC.println(pos);
    }
    else {
    }
  }

  // ACTUATIONS
  else if ( c == 'w' ) {
    if ( MY_CLAMP == 'l' ) {
      PC.println("Closing piston left ");
      piston(CLOSE);
    } else {
    }
  } else if ( c == '2' ) {
    if ( MY_CLAMP == 'l' ) {
      PC.println("Opening piston left ");
      piston(OPEN);
    } else {
    }
  } else if ( c == 'p' ) {
    if ( MY_CLAMP == 'r' ) {
      PC.println("Closing piston right ");
      piston(CLOSE);
    } else {
    }
  } else if ( c == '0' ) {
    if ( MY_CLAMP == 'r' ) {
      PC.println("Opening piston right ");
      piston(OPEN);
    } else {
    }
  }

  // STOPS !
  else if ( c == ' ' ) {
    PC.println("Both motors STOPPED !");
    run(STOP, 255);
  }


  while ( PC.available() )
    PC.read();
}

