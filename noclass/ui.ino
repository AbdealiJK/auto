
void simple_ui() {
  char c = PC.read();

  // RESET THE BOT
  if ( c == '`' ) {
    if ( MY_CLAMP == 'l' ) {
      PC.print("Left motor moving to left trip switch ... ");
      while( run(LEFT, 50) == 1 ){
        if ( PC.available() && PC.read() == ' ' ) {
          run(STOP, 255);
          break;
        }
      }
      PC.println("DONE");
      reset();
      PC.println("Left motor pos set back to 0 ~");
    } 
    else {
      //Code to trasmit to other clamp
    }
  }
  else if ( c == '=' || c == '1' ) {
    if ( MY_CLAMP == 'r' ) {
      PC.print("Right motor moving to right trip switch ... ");
      while( run(RIGHT, 50) == 1 ){
        if ( PC.available() && PC.read() == ' ' ) {
          run(STOP, 255);
          break;
        }
      }
      PC.println("DONE");
      reset();
      PC.println("Right motor pos set back to 0 ;");
    } 
    else {
      //Code to trasmit to other clamp
    }
  } 

  // PRINT STUFF  
  else if ( c == '4' || c == '5' || c == '6' || c == '7' || c == '8' ) { 
    PC.print("Motor LEFT ");
    PC.print("\t Position = ");
    PC.println(pos);

//Code to trasmit to other clamp and rceive dat from other clamp


  }

  // PWM MODE
  else if ( c == 'd' || c == 'a' ) { 
    if ( MY_CLAMP == 'l' ) {
      int vel = PC.parseInt();
      if ( c == 'd' )
        vel = -abs(vel);
      else
        vel = abs(vel);
      PC.print("Left motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      while( run( ( vel < 0 ) ? LEFT : RIGHT, abs(vel)) ) {
        if ( PC.available() && PC.read() == ' ' ) {
          run(STOP, 255);
          break;
        }
      }
      PC.println("DONE");
    } 
    else {
      //Code to trasmit to other clamp
      int vel = PC.parseInt();
    }
  } 
  else if ( c == 'j' || c == 'l') {
    while(!PC.available());
    if ( MY_CLAMP == 'r' ) {
      int vel = PC.parseInt();
      if ( c == 'j'  )
        vel = -abs(vel);
      else
        vel = abs(vel);
      PC.print("Right motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      while( run( ( vel < 0 ) ? LEFT : RIGHT, abs(vel)) ) {
        if ( PC.available() && PC.peek() == ' ' ) {
          while(PC.available()) PC.println(PC.read());
          run(STOP, 255);
          break;
        }
      }
      PC.println("DONE"); 
    } 
    else {
      int vel = PC.parseInt();
      //Code to trasmit to other clamp
    }
  }

  // POSITION MODE
  else if ( c == 'q' || c == 'e' ) {
    if ( MY_CLAMP == 'l' ) {
      while ( ! PC.available() );
      int pos_t = PC.parseInt();
      if ( c == 'q'  )
        pos_t = -abs(pos_t);
      else
        pos_t = abs(pos_t);
      PC.println("Left motor moving ... pos = ");
      PC.print(pos);
      PC.print(" -> ");
      while ( goto_pos(pos_t) == 0 ) {
        if ( PC.available() && PC.read() == ' ' ) {
          stop();
          break;
        }
      }
      PC.println(pos);
    } 
    else {
      //Code to trasmit to other clamp
    }
  } 
  else if ( c == 'u' || c == 'o' ) {
    if ( MY_CLAMP == 'r' ) {
      while ( ! PC.available() );
      int pos_t = PC.parseInt();
      if ( c == 'u'  )
        pos_t = -abs(pos_t);
      else
        pos_t = abs(pos_t);
      PC.println("Right motor moving ... pos = ");
      PC.print(pos);
      PC.print(" -> ");
      while ( goto_pos(pos_t) == 0 ) {
        if ( PC.available() && PC.read() == ' ' ) {
          stop();
          break;
        }
      }
      PC.println(pos);
    } 
    else {
      //Code to trasmit to other clamp
    }
  }

  // ACTUATIONS
  else if ( c == 's' ) {
    if ( MY_CLAMP == 'l' ) {
      PC.println("Closing piston left ");
      piston(CLOSE);
    } 
    else {
      //Code to trasmit to other clamp
    }
  } 
  else if ( c == 'w' ) {
    if ( MY_CLAMP == 'l' ) {
      PC.println("Opening piston left ");
      piston(OPEN);
    } 
    else {
      //Code to trasmit to other clamp
    }
  } 
  else if ( c == 'k' ) {
    if ( MY_CLAMP == 'r' ) {
      PC.println("Closing piston right ");
      piston(CLOSE);
    } 
    else {
      //Code to trasmit to other clamp
    }
  } 
  else if ( c == 'i' ) {
    if ( MY_CLAMP == 'r' ) {
      PC.println("Opening piston right ");
      piston(OPEN);
    } 
    else {
      //Code to trasmit to other clamp
    }
  }

  // STOPS !
  else if ( c == ' ' ) { 
    PC.println("Both motors STOPPED !");
    run(STOP, 255);
    //Code to trasmit to other clamp
  }
  else if (c == 'b')
  {
    PC.println("Both motors STOPPED and clamps OPENED !");    
    run(STOP,255);
    piston(OPEN);
        //Code to trasmit to other clamp    
  }  
  


  while( PC.available() )
    PC.read();
}

