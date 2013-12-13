void ui() {
  char c = Serial.read();
  
  // RESET MODE
  if ( c == 'r' ) { 
    while(!Serial.available());
    char c2 = Serial.read();
    if ( c2 == 'l' ) {
      while( ml.run(LEFT, 10) );
    } 
    else if ( c2 == 'r' ) {
      while( mr.run(LEFT, 10) );
    }
  }
  
  // SET MODE
  if ( c == 's' ) { 
    while(!Serial.available());
    char c2 = Serial.read();
    if ( c2 == 'l' ) {
      ml.reset();
    } 
    else if ( c2 == 'r' ) {
      mr.reset();
    }
  }

  // PWM MODE
  else if ( c == 'v' ) { 
    while(!Serial.available());
    char c2 = Serial.read();
    if ( c2 == 'l' ) {
      int vel = Serial.parseInt();
      if ( vel > 0 )
        while( ml.run(RIGHT, vel) );
      else if ( vel < 0 )
        while( ml.run(LEFT, vel) );
    } 
    else if ( c2 == 'r' ) {
      int vel = Serial.parseInt();
      if ( vel > 0 )
        while( mr.run(RIGHT, vel) );
      else if ( vel < 0 )
        while( mr.run(LEFT, vel) );
    }      
  }
  
  // POSITION MODE
  else if ( c == 'm' ) { 
    while(!Serial.available());
    char c2 = Serial.read();
    if ( c2 == 'l' ) {
      float pos = Serial.parseFloat();
      while( ml.goto_pos(pos) );
    } 
    else if ( c2 == 'r' ) {
      float pos = Serial.parseFloat();
      while( mr.goto_pos(pos) );
    }
  } 

  // POSITION MODE
  else if ( c == 's' ) { 
    while(!Serial.available());
    char c2 = Serial.read();
    if ( c2 == 'l' ) {
      ml.run(STOP, 255);
    } 
    else if ( c2 == 'r' ) {
      mr.run(STOP, 255);
    }
  } 

  // POSITION MODE
  else if ( c == 'q' ) { 
    ml.run(STOP, 255);
    mr.run(STOP, 255);
  } 

}

