void ladder() {
  /*
   Problems :
  */
  PC.println(">>>>>>>>>> Starting LADDER");

  long start_time;

  // First rung -- left : go to 2nd rung
/*
  QUIT_OR_CONTINUE;
  PC.println("Moving right clamp to extreme");
  NEXT.print(NEXT_CLAMP);
  NEXT.print('v');
  NEXT.print(-200);

*/
  // Repetitive rungs -- left : clamp, go left till fixedclamp_trip, come back sli, open clamp, go right till middle trip
  int n = 4; // 4rpo
  while (n--) {

    PC.println("Closing piston");
    piston(CLOSE); // clamp
    PC.println("Piston closed");

    QUIT_OR_CONTINUE;

    start_time = millis();
    PC.println("Going towards home");
    while ( run ( HOME, 255) ) { // Bot goes up till fixedclamp_trip
      if ( q_stop() ) break;
      update_fixedclamp_trip();
      if (n == 0 && start_time != -1 && millis() - start_time > 400) { // % calib
        PC.println("Activating tail piston through slave");
        NEXT.write('r');
        NEXT.write('p');
        NEXT.write('c');
        start_time = -1;
        //        listen();
      }
      if ( fixedclamp_trip ) {
        PC.println("Fixed clamp was pressed !");
        run ( STOP, 255 );
        break;
      }
    }
    start_time = -1;
    while ( run ( HOME, 255 ) ) { // Bot goes up till fixedclamp_trip
      update_fixedclamp_trip();
      if ( q_stop() ) break;
      if ( !fixedclamp_trip ) {
        PC.println("Fixed clamp was removed !");
        run ( STOP, 255 );
        break;
      }
    }
    PC.println("Stopped ... but not done");

    QUIT_OR_CONTINUE;

    PC.print("Going up so that fixed clamp opens up fully ....");
    start_time = millis();
    while ( run ( HOME, 255 ) ) { // Bot goes up till fixedclamp_trip
      if ( q_stop() ) break;
      if ( millis() - start_time > 300 ) { // % calib
        run(STOP, 255);
        PC.print(" time delay done ");
        break;
      }
    }
    PC.println("Stopped");

    QUIT_OR_CONTINUE;

    PC.print("Moving middle for a small time ");
    start_time = millis();
    while ( run ( MID, 255 ) ) { // Bot goes down a little
      if ( q_stop() ) break;
      if ( millis() - start_time > 200 ) { // % calib 
        run(STOP, 255);
        PC.print(" time delay done ");
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
    while ( run( MID, 255) ) { // go up till middle_trip
      if ( q_stop() ) break;
    }
    PC.println("Something tripped");
    QUIT_OR_CONTINUE;
  }

  // Last rung

  PC.println("Closing piston");
  piston(CLOSE); // clamp open
  PC.println("Piston closed");
  QUIT_OR_CONTINUE;

  PC.println("Going towards home");
  start_time = millis();
  while ( run ( HOME, 200 ) ) { // Bot goes up till home trips
    if ( q_stop() ) break;
    if (start_time != -1 && millis() - start_time > 500) { // % calib
      PC.println("Opening tail piston through slave");
      NEXT.write('r');
      NEXT.write('p');
      NEXT.write('o');
      start_time = -1;
    }
   }
  PC.println("Stopped");
  QUIT_OR_CONTINUE;

  PC.println("Opening piston");
  piston(OPEN); // clamp open
  PC.println("Piston openend");
  QUIT_OR_CONTINUE;

  PC.print("Moving middle for a small time ");
  start_time = millis();
  while ( run ( MID, 255 ) ) { // Bot goes down a little
    if ( q_stop() ) break;
    if ( millis() - start_time > 800 ) { // % calib
      run(STOP, 255);
      PC.print(" time delay done ");
      break;
    }
  }
  PC.println("Moved for sometime");
  QUIT_OR_CONTINUE;

  PC.println("Closing piston");
  piston(CLOSE); // clamp close
  PC.println("Piston closed");
  QUIT_OR_CONTINUE;
  // Flag
  PC.println("Ladder Done!!!");

}

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

void seesaw() {
  PC.println(">>>>>>>>>> See saw START");

  // Move till AVS
  int vel = 100;
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

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

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

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

void polewalk() {
 /*     move both motors towards the left
         clamp right motor
         move right motor towards right for some time T1 
         clamp left motor
         unclamp right motor
         move right motor to left for some time T2
         move left motor to right till it trips
    */
    
    // move both motors towards left
     
    // move master
    /*
    PC.print(MY_CLAMP);
    PC.print("-motor moving to home trip switch ... ");
    go_home(200);
      
    // move slave
   
    NEXT.print(NEXT_CLAMP);
    NEXT.print('v');
    NEXT.print(200);
    listen();
    
    
    //clamp right motor
   
    NEXT.print(NEXT_CLAMP);
    NEXT.print('p');
    NEXT.print('c');
    listen();
    // move right motor towards right till left motor detects disc. move for some more time T1 and stop
    update_avs();
   
    NEXT.print(NEXT_CLAMP);
    NEXT.print('v');
    NEXT.print(-200);
    update_avs();
    while ( avs_value < 3400 ) { // set threshold @ to be calibrated
      update_avs();
      PC.print("AVS value : ");
      PC.println(avs_value);
      }
    PC.println("avs saw something ... but moving for some more time");      
    delay(100);// move for some time after AVS is detected. @ T1 to be calibrated
    NEXT.print('q'); // stop motor
    PC.print("Right motor Stopped");
    QUIT_OR_CONTINUE;
    
    // Clamp using left motor
     piston(CLOSE);
     PC.print("Left motor clamped");
     delay(500);
    // Unclamp right motor
   
     NEXT.print(NEXT_CLAMP);
     NEXT.print('p');
     NEXT.print('o');
     listen();
     PC.print("Right motor unclamped");     
    //move right clamp towards left for some time T2 and stop 
    QUIT_OR_CONTINUE;    
   
    NEXT.print(NEXT_CLAMP);
    NEXT.print('v');
    NEXT.print(200);    
    listen();
    delay(1000); // @ T2 to be calibrated
    NEXT.print('q');
    //move left clamp towards right till middle tripswitch trips
     while ( run( MID, 200) )  {
        if ( q_stop() ) break;
      }
   PC.println("Polewalk completed .... ");      
*/}
