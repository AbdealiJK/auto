void ui() {

  char c = PC.read();

  // RESET MODE
  if ( c == 'r' ) { 
    a = 0;
    check = 1;

    while(!PC.available());
    char c2 = PC.read();
    if ( c2 == 'l' ) {
      PC.print("Left motor moving to left trip switch ... ");
      while( ml.run(LEFT, 70) == 1 ) {
      }
      PC.println("DONE");
      ml.reset();
      PC.print("Left motor init set at ... ");
      PC.print(ml.init_pos);
      PC.print("cm = ");
      PC.print(ml.init_turns);
      PC.println("turns");
    } 
    else if ( c2 == 'r' ) {
      PC.print("Right motor moving to rightn trip switch ... ");
      while( mr.run(RIGHT, 70) == 1 ) {
        if ( check == 0 ) {
          check = 1;
          Serial.print(a);
          Serial.print(" -- ");
          Serial.print(m);
          Serial.print(" -- p ");
          Serial.print(t);
          Serial.print(" -- tlin ");
          Serial.println(t - lt);
          lt = t;
        }

      }
      PC.println("DONE");
      mr.reset();
      PC.print("Right motor init set at ... ");
      PC.print(ml.init_pos);
      PC.print("cm = ");
      PC.print(ml.init_turns);
      PC.println("turns");
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

  // PRINT STUFF  
  if ( c == 'w' ) { 
    while(!PC.available());
    char c2 = PC.read();
    if ( c2 == 'l' ) {
      ml.calc_pos();
      PC.println("Motor LEFT ");
      PC.print("Position : current=");
      PC.print(ml.cur_pos);
      PC.print("\t init=");
      PC.println(ml.init_pos);
    } 
    else if ( c2 == 'r' ) {
      mr.calc_pos();
      PC.println("Motor RIGHT ");
      PC.print("Position : current=");
      PC.print(mr.cur_pos);
      PC.print("\t init=");
      PC.println(mr.init_pos);
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
      if ( vel > 0 ) {
        while( ml.run(RIGHT, vel) ) {
          //PC.println(analogRead(ml.pot_pin));
          if ( PC.available() && PC.read() == 'q' ) {
            ml.run(STOP, 255);
            break;
          }
        }
      }
      else if ( vel < 0 ) {
        while( ml.run(LEFT, vel) ) {
          //PC.println(analogRead(ml.pot_pin));
          if ( PC.available() && PC.read() == 'q' ) {
            ml.run(STOP, 255);
            break;
          }
        }
      }
      PC.println("DONE");
    }  
    else if ( c2 == 'r' ) {
      a= 0;
      check = 1;
      int vel = PC.parseInt();
      PC.print("Right motor moving at pwm = ");
      PC.print(vel);
      PC.print(" ... ");
      if ( vel > 0 ) {
        while( mr.run(RIGHT, vel) ) {
          //PC.println(analogRead(mr.pot_pin));
          if ( PC.available() && PC.read() == 'q' ) {
            mr.run(STOP, 255);
            break;
          }
        }
      }
      else if ( vel < 0 ) {
        while( mr.run(LEFT, vel) ) {
          //PC.println(analogRead(mr.pot_pin));
          if ( check == 0 ) {
            check = 1;
            Serial.print(a);
            Serial.print(" -- ");
            Serial.print(m);
            Serial.print(" -- p ");
            Serial.print(t);
            Serial.print(" -- tlin ");
            Serial.println(t- lt);
            lt = t;
          }
          if ( PC.available() && PC.read() == 'q' ) {
            mr.run(STOP, 255);
            break;
          }
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
      float pos = PC.parseFloat();
      PC.println("Left motor moving to postion = ");
      PC.print(pos);
      PC.print(" ... ");
      while ( ml.goto_pos(pos) == 0 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          ml.run(STOP, 255);
          break;
        }
      };
      //      PC.println("DONE");
    } 
    else if ( c2 == 'r' ) {
      float pos = PC.parseFloat();
      PC.println("Right motor moving to postion = ");
      PC.print(pos);
      PC.print(" ... ");
      while ( mr.goto_pos(pos) == 0 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          mr.run(STOP, 255);
          break;
        }
      };
      //      PC.println("DONE");
    }
  } 

  // POSITION MODE
  else if ( c == 'q' ) { 
    PC.println("Both motors STOPPED !");
    ml.run(STOP, 255);
    mr.run(STOP, 255);
  } 
  while(Serial.available());
  Serial.read();
}







