void ladder() {
  PC.println(">>>>>>>>>> Starting LADDER");
  
  
  long start_time;

  // First rung -- left : go to 2nd rung
  QUIT_OR_CONTINUE;
  PS.println("Moving right clamp to extreme");
  NEXT.print(NEXT_CLAMP);
  NEXT.print('v');
  NEXT.print(-200);


  // Repetitive rungs -- left : clamp, go left till fixedclamp_trip, come back sli, open clamp, go right till middle trip
  int n = 4;
  while (n--) {

    PC.println("Closing piston");
    piston(CLOSE); // clamp
    PC.println("Piston closed");

    if ( n == 1 ) {
      PC.println("Activating tail piston through slave");
      NEXT.write('r');
      NEXT.write('p');
      NEXT.write('c');
      listen();
    }

    QUIT_OR_CONTINUE;

    PC.println("Going towards home");
    while ( run ( HOME, 200 ) ) { // Bot goes up till fixedclamp_trip
      if ( q_stop() ) break;
      if ( fixedclamp_trip ) {
        PC.println("Fixed clamp was pressed !");
        run ( STOP, 255 );
        break;
      }
    }
    while ( run ( HOME, 200 ) ) { // Bot goes up till fixedclamp_trip
      if ( q_stop() ) break;
      if ( !fixedclamp_trip ) {
        PC.println("Fixed clamp was removed !");
        run ( STOP, 255 );
        break;
      }
    }
    PC.println("Stopped ... but not done");

    QUIT_OR_CONTINUE;

    start_time = millis();
    while ( run ( HOME, 200 ) ) { // Bot goes up till fixedclamp_trip
      if ( q_stop() ) break;
      if ( millis() - start_time > 100 ) {
        run(STOP, 255);
        break;
      }
    }
    PC.println("Stopped");

    QUIT_OR_CONTINUE;

    PC.println("Moving middle for a while");
    start_time = millis();
    while ( run ( MID, 200 ) ) { // Bot goes down a little
      if ( q_stop() ) break;
      if ( millis() - start_time > 150 ) {
        run(STOP, 255);
        break;
      }
    }
    PC.println("Moved for soemtime");

    QUIT_OR_CONTINUE;

    PC.println("Opening piston");
    piston(OPEN); // clamp open
    PC.println("Piston openend");

    QUIT_OR_CONTINUE;

    PC.println("Goinig up !");
    while ( run( MID, 200) ) { // go up till middle_trip
      if ( q_stop() ) break;
    }
    PC.println("Something tripped");

    QUIT_OR_CONTINUE;
  }





  // Last rung
  /*  PC.println("Going towards home");
    while( run ( HOME, 200 ) ) { // Bot goes up till fixedclamp_trip
      if ( q_stop() ) break;
      if ( fixedclamp_trip ) {
        PC.println("Fixed clamp was pressed !");
        run ( STOP, 255 );
        break;
      }
    }
    PC.println("Stopped");

    PC.println("Waiting for 'c' ... ");
    while( !PC.available() || ( PC.available() && PC.read() != 'c' ) );
  */
  // Flag
}


void seesaw() {
  PC.println(">>>>>>>>>> See saw START");
  
  // Move till AVS
  int val = 100;
  QUIT_OR_CONTINUE;
  PC.print("Telling slave to move to avs ... ");
  NEXT.print(NEXT_CLAMP);
  NEXT.print('a');
  NEXT.print(vel);
  listen();
  PC.println("DONE");

  QUIT_OR_CONTINUE;
  PC.print("Moving to avs myself ... ");
  update_avs();
  while ( run( MID, vel) ) {
    if ( q_stop() ) break;
    update_avs();
    if ( avs_value > 3400 ) {
      run ( STOP, 255 );
      PC.print("avs saw something ... ");
      break;
    }
  }
  PC.println("DONE");

  QUIT_OR_CONTINUE;
  PC.print("Clamping both ! ... ");
  NEXT.print("rpc");
  piston(CLOSE);
  listen();
  
  QUIT_OR_CONTINUE;
  PC.print("Leaving both ! ... ");
  NEXT.print("rpo");
  piston(OPEN);
  listen();
  
  PC.println(">>>>>>>>>> See saw fully done");
}
void swing() {
  PC.println(">>>>>>>>>> Swing starting !!");
  // Move to correct positions
  // ?
  
  // Clamp now !
  QUIT_OR_CONTINUE;
  PC.print("Clamping both ! ... ");
  NEXT.print("rpc");
  piston(CLOSE);
  listen();
  
  // Leave the swing now
  QUIT_OR_CONTINUE;
  PC.print("Leaving both ! ... ");
  NEXT.print("rpo");
  piston(OPEN);
  listen();
  
  PC.println(">>>>>>>>>> Swing fully done");
}

void polewalk() {
  
}
