void ui() {

  char c = PC.read();

  // RESET MODE
  if ( c == 'r' ) {
    while(!PC.available());
    char c2 = PC.read();
    if ( c2 == 'l' ) {
      PC.print("Left motor moving to left trip switch ... ");
      while( m.run(LEFT, 50) == 1 ){
        if ( PC.available() && PC.read() == 'q' ) {
          m.run(STOP, 255);
          break;
        }
      }
      PC.println("DONE");
      m.reset();
      PC.println("Left motor pos set back to 0 ");
      
    } 
    else if ( c2 == 'r' ) {
        
  #ifdef SLAVE    
        query("rr");
        listen();
  #endif        
    }
  }

  // SET MODE
  if ( c == 's' ) { 
    while(!PC.available());
    char c2 = PC.read();
    if ( c2 == 'l' ) {
      m.reset();
      PC.println("Left motor pos set at 0 ");
    } 
    else if ( c2 == 'r' ) {
  #ifdef SLAVE          
      query("sr");
      listen();
      PC.print("Right motor pos set at 0 ");
  #endif
    }
  }

  // PRINT STUFF  
  if ( c == 'w' ) { 
    while(!PC.available());
    char c2 = PC.read();
    if ( c2 == 'l' ) {
      PC.print("Motor LEFT ");
      PC.print("\t Position = ");
      PC.println(m.pos);
    } 
    else if ( c2 == 'r' ) {
  #ifdef SLAVE          
      query("wr");
      listen();
  #endif      
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
      while( m.run( ( vel < 0 ) ? LEFT : RIGHT, abs(vel)) ) {
        if ( PC.available() && PC.read() == 'q' ) {
          m.run(STOP, 255);
          break;
        }
      }
      PC.println("DONE");
    }  
    else if ( c2 == 'r' ) {
  #ifdef SLAVE          
         query("vr");
          int vel = PC.parseInt();         
          query(vel);
         listen();
  #endif         
    }
  }

  // POSITION MODE
  else if ( c == 'm' ) {
    while(!PC.available());
    char c2 = PC.read();
    if ( c2 == 'l' ) {
      int pos = PC.parseInt();
      PC.println("Left motor moving ... pos = ");
      PC.print(pos);
      PC.print(" -> ");
      while ( m.goto_pos(pos) == 0 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          m.stop();
          break;
        }
      }
      PC.println(m.pos);
    } 
    else if ( c2 == 'r' ) {
  #ifdef SLAVE          
      query("mr");
      float pos = PC.parseFloat();
      query(pos);
      listen();
  #endif      
    }
  } 

  // ACTUATIONS
  if ( c == 'p' ) { 
    while(!PC.available());
    char c2 = PC.read();
    if ( c2 == 'l' ) {
      while(!PC.available());
      char c3 = PC.read();
      if ( c3 == 'c' ) {
        PC.println("Closing piston LEFT ");
        m.piston(CLOSE);
      } 
      else {
        PC.println("Opening piston LEFT ");
        m.piston(OPEN);
      }
    } 
    else if ( c2 == 'r' ) {
  #ifdef SLAVE          
      while(!PC.available());
      char c3 = PC.read();
      if ( c3 == 'c' ) {
        
        query("prc");
        listen();
      } 
      else {
        
        query("pro");
        listen();
      }
  #endif      
    }   
    else if ( c2 == 'x' ) {
      while(!PC.available());
      char c3 = PC.read();
      if ( c3 == 'c' ) {
        PC.println("Closing piston BOTH ");
        m.piston(CLOSE);
  #ifdef SLAVE                  
        query("pxc");
        listen();
  #endif        
      } 
      else {
        PC.println("Opening piston BOTH ");
        m.piston(OPEN);
  #ifdef SLAVE                  
        query("pxo");
        listen();
  #endif        
      }
    }   
  }

  // POSITION MODE
  else if ( c == 'q' ) { 
    PC.println("Both motors STOPPED !");
    m.run(STOP, 255);
    #ifdef SLAVE
        query("q");
        listen();
    #endif        
  } 
  
  // POSITION MODE
  else if ( c == 'z' ) { 
    PC.println("Both motors STOPPED !");
    m.run(STOP, 255);
    m.piston(OPEN);
  #ifdef SLAVE              
    query("z");
    listen();
  #endif    
  } 
  
  while(PC.available());
  PC.read();
}


