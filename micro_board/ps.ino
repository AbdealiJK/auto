void ladder() {
  /*
   Problems :
  */
  PC.println(">>>>>>>>>> Starting LADDER");

  long start_time;

  // First rung
  /*
    QUIT_OR_CONTINUE;
    PC.println("Moving right clamp to extreme");
    NEXT.print(NEXT_CLAMP);
    NEXT.print('v');
    NEXT.print(-200);
  */

  // Repetitive rungs
  int n = 4;
  while (n--) {

    PC.println("Closing piston");
    QUIT_OR_CONTINUE;
    piston(CLOSE); // clamp
    PC.println("Piston closed");

    PC.println("Going towards home ... waiting for fixed clamp to go above last rung");
    QUIT_OR_CONTINUE;
    update_fixedclamp_trip();
    if ( ! fixedclamp_trip ) { // as initially, the clamp is below the rung
      while ( run ( HOME, 255) ) { // Bot goes up till fixedclamp_trip
        if ( q_stop() ) break;
        update_fixedclamp_trip();
        if ( fixedclamp_trip ) {
          PC.println("Fixed clamp was pressed !");
          run ( STOP, 255 );
          break;
        }
      }
    }
    while ( run ( HOME, 255) ) { // Bot goes up till fixedclamp_trip
      if ( q_stop() ) break;
      update_fixedclamp_trip();
      if ( !fixedclamp_trip ) {
        PC.println("Fixed clamp was un-pressed !");
        run ( STOP, 255 );
        break;
      }
    }
    PC.println("Going towards home ... trying to find fixedclamp");
    QUIT_OR_CONTINUE;
    while ( run ( HOME, 255) ) { // Bot goes up till fixedclamp_trip
      if ( q_stop() ) break;
      update_fixedclamp_trip();
      if ( fixedclamp_trip ) {  // @@@@ bot wont trip since tail piston opens
        PC.println("Fixed clamp was pressed !");
        run ( STOP, 255 );
        break;
      }
    }
    PC.println("Stopped ... but not done");

    if ( n == 0 ) {
      // come down sli so that tail will hit the rung    PC.print("Moving middle for a small time ");
      QUIT_OR_CONTINUE;
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
      // open tail piston
      PC.println("Activating tail piston through slave");
      QUIT_OR_CONTINUE;
      NEXT.write('r');
      NEXT.write('p');
      NEXT.write('c');
    }

    PC.print("Moving middle for a small time ");
    QUIT_OR_CONTINUE;
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

    PC.println("Opening piston");
    QUIT_OR_CONTINUE;
    piston(OPEN); // clamp open
    PC.println("Piston openend");
  
    if ( n == 0 ) {
      QUIT_OR_CONTINUE;
      // close tail piston
      PC.println("DEactivating tail piston through slave");
      QUIT_OR_CONTINUE;
      NEXT.write('r');
      NEXT.write('p');
      NEXT.write('o');
    }
 
    PC.println("Goinig up !");
    QUIT_OR_CONTINUE;
    while ( run( MID, 255) ) { // go up till middle_trip
      if ( q_stop() ) break;
    }
    PC.println("Something tripped");
  }



  // Last rung

  PC.println("Closing piston");
  QUIT_OR_CONTINUE;
  piston(CLOSE); // clamp open
  PC.println("Piston closed");
  // something is cuppinghere
  PC.println("Going towards home");
  QUIT_OR_CONTINUE;
  start_time = millis();
  while ( run ( HOME, 200 ) ) { // Bot goes up till home trips
    if ( q_stop() ) break;
    if (start_time != -1 && millis() - start_time > 500) { // % calib
      start_time = -1;
    }
  }
  PC.println("Stopped");

  PC.println("Opening tail piston through slave");
  QUIT_OR_CONTINUE;
  NEXT.write('r');
  NEXT.write('p');
  NEXT.write('o');

  PC.println("Opening piston");
  QUIT_OR_CONTINUE;
  piston(OPEN); // clamp open
  PC.println("Piston openend");

  PC.print("Moving middle for a small time ");
  QUIT_OR_CONTINUE;
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
  QUIT_OR_CONTINUE;
  piston(CLOSE); // clamp close
  PC.println("Piston closed");

  // Flag
  PC.println("Ladder Done!!!");

}

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

void seesaw() {
  PC.println(">>>>>>>>>> Seesaw START");
  PC.println(">>>>>>>>>> Seesaw fully done");
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

  PC.print("............. Pole Walk satrt ");
  // move both motors to middle

  // clamp right piston

  // move left to extreme, move right to extreme

  // clamp left

  // move right to middle and left to middle

  PC.println("Polewalk completed .... ");

}
