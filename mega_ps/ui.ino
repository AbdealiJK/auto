void ui() {

  char c = PC.read();

  // RESET MODE
  if ( c == 'r' ) {
    while(!PC.available());
    char c2 = PC.read();
    if ( c2 == 'l' ) {
      PC.print("Left motor moving to left trip switch ... ");
      while( ml.run(LEFT, 50) == 1 ){
        if ( PC.available() && PC.read() == 'q' ) {
          ml.run(STOP, 255);
          break;
        }
      }
      PC.println("DONE");
      ml.reset();
      PC.println("Left motor pos set back to 0 ");
    } 
    else if ( c2 == 'r' ) {
      PC.print("Right motor moving to right trip switch ... ");
      while( mr.run(RIGHT, 190) == 1 ){
        if ( PC.available() && PC.read() == 'q' ) {
          mr.run(STOP, 255);
          break;
        }
      }
      PC.println("DONE");
      mr.reset();
      PC.println("Right motor pos set at 0 ");
    }
  }

  // SET MODE
  if ( c == 's' ) { 
    while(!PC.available());
    char c2 = PC.read();
    if ( c2 == 'l' ) {
      ml.reset();
      PC.println("Left motor pos set at 0 ");
    } 
    else if ( c2 == 'r' ) {
      mr.reset();
      PC.print("Right motor pos set at 0 ");
    }
  }

  // PRINT STUFF  
  if ( c == 'w' ) { 
    while(!PC.available());
    char c2 = PC.read();
    if ( c2 == 'l' ) {
      PC.print("Motor LEFT ");
      PC.print("\t Position = ");
      PC.println(ml.pos);
    } 
    else if ( c2 == 'r' ) {
      PC.print("Motor RIGHT ");
      PC.print("\t Position = ");
      PC.println(mr.pos);
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
      while( ml.run( ( vel < 0 ) ? LEFT : RIGHT, abs(vel)) ) {
        if ( PC.available() && PC.read() == 'q' ) {
          ml.run(STOP, 255);
          break;
        }
      }
      PC.println("DONE");
    }  
    else if ( c2 == 'r' ) {
      int vel = PC.parseInt();
      PC.print("Right motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");

      while( mr.run( ( vel < 0 ) ? LEFT : RIGHT, abs(vel)) ) {
        if ( PC.available() && PC.read() == 'q' ) {
          mr.run(STOP, 255);
          break;
        }
      }
      PC.println("DONE");
    }
  }

  // POSITION MODE
  else if ( c == 'm' ) {
    while(!PC.available());
    char c2 = PC.read();
    if ( c2 == 'l' ) {
      int pos = PC.parseInt();
      PC.println("Left motor moving ... pos = ");
      PC.print(ml.pos);
      PC.print(" -> ");
      while ( ml.goto_pos(pos) == 0 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          ml.stop();
          break;
        }
      }
      PC.println(ml.pos);
    } 
    else if ( c2 == 'r' ) {
      float pos = PC.parseFloat();
      PC.println("Right motor moving to pos = ");
      PC.print(mr.pos);
      PC.print(" -> ");
      while ( mr.goto_pos(pos) == 0 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          mr.run(STOP, 255);
          break;
        }
      };
      PC.println(mr.pos);
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
        ml.piston(CLOSE);
      } 
      else {

PC.println("Opening piston LEFT ");
        ml.piston(OPEN);
      }
    } 
    else if ( c2 == 'r' ) {
      while(!PC.available());
      char c3 = PC.read();
      if ( c3 == 'c' ) {
        PC.println("Closing piston RIGHT ");
        mr.piston(CLOSE);
      } 
      else {
        PC.println("Opening piston RIGHT ");
        mr.piston(OPEN);
      }
    }   
    else if ( c2 == 'x' ) {
      while(!PC.available());
      char c3 = PC.read();
      if ( c3 == 'c' ) {
        PC.println("Closing piston BOTH ");
        mr.piston(CLOSE);
        ml.piston(CLOSE);
      } 
      else {
        PC.println("Opening piston BOTH ");
        mr.piston(OPEN);
        ml.piston(OPEN);
      }
    }   
  }

  // POSITION MODE
  else if ( c == 'q' ) { 
    PC.println("Both motors STOPPED !");
    ml.run(STOP, 255);
    mr.run(STOP, 255);
  } 
  
  // POSITION MODesaw();

  else if ( c == 'z' ) { 
    PC.println("Both motors STOPPED !");
    ml.run(STOP, 255);
    mr.run(STOP, 255);
    ml.piston(OPEN);
    mr.piston(OPEN);
  } 
else if(c=='1')
{
  seesaw();
}

else if(c=='2')
{
  swing();
}

else if(c=='3')
{
  polewalk();
}

else if(c=='4')
{
  ladder();
}

  while(PC.available());
  PC.read();
}


