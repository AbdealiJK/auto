void ui() {

  char c = PC.read();

  // RESET THE BOT
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








void simple_ui() {
  char c = PC.read();

  // RESET THE BOT
  if ( c == 'a' ) {
    if ( MY_CLAMP == 'l' ) {
      PC.print("Left motor moving to left trip switch ... ");
      while( m.run(LEFT, 50) == 1 ){
        if ( PC.available() && PC.read() == 'q' ) {
          m.run(STOP, 255);
          break;
        }
      }
      PC.println("DONE");
      m.reset();
      PC.println("Left motor pos set back to 0 ;");
    } 
    else {
    }
  } 
  else if ( c == '\'' ) {
    if ( MY_CLAMP == 'r' ) {
      PC.print("Right motor moving to left trip switch ... ");
      while( m.run(RIGHT, 50) == 1 ){
        if ( PC.available() && PC.read() == 'q' ) {
          m.run(STOP, 255);
          break;
        }
      }
      PC.println("DONE");
      m.reset();
      PC.println("Right motor pos set back to 0 ;");
    } 
    else {
    }
  } 

  // PRINT STUFF  
  else if ( c == '4' || c == '5' || c == '6' || c == '7' ) { 
      PC.print("Motor LEFT ");
      PC.print("\t Position = ");
      PC.println(m.pos);
      
  }
  
  // PWM MODE
  else if ( c == 's' ) { 
    if ( MY_CLAMP == 'l' ) {
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
    } else {
      int vel = PC.parseInt();
    }
  } else if ( c == ';' ) {
    while(!PC.available());
    if ( MY_CLAMP == 'r' ) {
      int vel = PC.parseInt();
      PC.print("Right motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      while( m.run( ( vel < 0 ) ? LEFT : RIGHT, abs(vel)) ) {
        if ( PC.available() && PC.peek() == 'q' ) {
          while(PC.available()) PC.println(PC.read());
          m.run(STOP, 255);
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
      while ( m.goto_pos(pos) == 0 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          m.stop();
          break;
        }
      }
      PC.println(m.pos);
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
      while ( m.goto_pos(pos) == 0 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          m.stop();
          break;
        }
      }
      PC.println(m.pos);
    } 
    else {
    }
  }
  
  // ACTUATIONS
  else if ( c == 'w' ) {
    if ( MY_CLAMP == 'l' ) {
      PC.println("Closing piston left ");
      m.piston(CLOSE);
    } else {
    }
  } else if ( c == '2' ) {
    if ( MY_CLAMP == 'l' ) {
      PC.println("Opening piston left ");
      m.piston(OPEN);
    } else {
    }
  } else if ( c == 'p' ) {
    if ( MY_CLAMP == 'r' ) {
      PC.println("Closing piston right ");
      m.piston(CLOSE);
    } else {
    }
  } else if ( c == '0' ) {
    if ( MY_CLAMP == 'r' ) {
      PC.println("Opening piston right ");
      m.piston(OPEN);
    } else {
    }
  }
  
  // STOPS !
  else if ( c == ' ' ) { 
    PC.println("Both motors STOPPED !");
    m.run(STOP, 255);
  }


  while( PC.available() )
    PC.read();
}

