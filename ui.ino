void ui() {
  char c = PC.read();

  // RESET MODE
  if ( c == 'r' ) { 
    while(!PC.available());
    char c2 = PC.read();
    if ( c2 == 'l' ) {
      PC.print("Left motor moving to left trip switch ... ");
      while( ml.run(LEFT, 10) == 1 );
      PC.println("DONE");
    } 
    else if ( c2 == 'r' ) {
      PC.print("Right motor moving to left trip switch ... ");
      while( mr.run(RIGHT, 10) );
      PC.println("DONE");
    }
  }

  // SET MODE
  if ( c == 's' ) { 
    while(!PC.available());
    char c2 = PC.read();
    if ( c2 == 'l' ) {
      ml.reset();
      PC.print("Left motor init set at ... ");
      PC.print(ml.init_pos);
      PC.print("cm = ");
      PC.print(ml.init_turns);
      PC.println("turns");
    } 
    else if ( c2 == 'r' ) {
      mr.reset();
      PC.print("Right motor init set at ... ");
      PC.print(ml.init_pos);
      PC.print("cm = ");
      PC.print(ml.init_turns);
      PC.println("turns");
    }
  }

  // PWM MODE
  else if ( c == 'v' ) { 
    while(!PC.available());
    char c2 = PC.read();
    if ( c2 == 'l' ) {
      int vel = PC.parseInt();
      PC.print("Left motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      if ( vel > 0 )
        while( ml.run(RIGHT, vel) );
      else if ( vel < 0 )
        while( ml.run(LEFT, vel) );
      PC.println("DONE");
    } 
    else if ( c2 == 'r' ) {
      int vel = PC.parseInt();
      PC.print("Right motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      if ( vel > 0 )
        while( mr.run(RIGHT, vel) );
      else if ( vel < 0 )
        while( mr.run(LEFT, vel) );
      PC.println("DONE");
    }      
  }

  // POSITION MODE
  else if ( c == 'm' ) { 
    while(!PC.available());
    char c2 = PC.read();
    if ( c2 == 'l' ) {
      float pos = PC.parseFloat();
      PC.println("Left motor moving to postion = ");
      PC.print(pos);
      PC.print(" ... ");
      ml.goto_pos(pos);
      //      PC.println("DONE");
    } 
    else if ( c2 == 'r' ) {
      float pos = PC.parseFloat();
      PC.println("Right motor moving to postion = ");
      PC.print(pos);
      PC.print(" ... ");
      mr.goto_pos(pos);
      //      PC.println("DONE");
    }
  } 

  // POSITION MODE
  else if ( c == 'q' ) { 
    PC.println("Both motors STOPPED !");
    ml.run(STOP, 255);
    mr.run(STOP, 255);
  } 

}


