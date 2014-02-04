void ladder() {
  PC.println(">>>>>>>>>> Starting LADDER");

  long start_time;

  /*
    QUIT_OR_CONTINUE;
    PC.println("Setup initial position");
    NEXT.print(MOVE);
    NEXT.print(-255);
  */

  int n = 4;
  while (n--) {

    PC.println("Need to close piston");
    QUIT_OR_CONTINUE;
    piston(CLOSE);
    PC.println("Piston closed");

    PC.println("Need to go towards home till just above last rung (i.e. fixed clamp should become untripped)");
    QUIT_OR_CONTINUE;
    update_trip(FIXEDCLAMP_TRIP);
    if ( ! fixedclamp_trip ) {
      PC.println("Initially, fixed clamp was found to be not tripped ... But it should have been tripped ! (as it should be at the ~prev rung) ... so, maybe it went down too much ... going up till we can find the last rung.");
      while ( run ( HOME, 255) ) {
        if ( q_stop() ) break;
        update_trip(FIXEDCLAMP_TRIP);
        if ( fixedclamp_trip ) {
          PC.println("Fixed clamp was pressed !");
          run ( STOP, 255 );
          break;
        }
      }
    }
    while ( run ( HOME, 255) ) {
      if ( q_stop() ) break;
      update_trip(FIXEDCLAMP_TRIP);
      if ( !fixedclamp_trip ) {
        PC.println("Fixed clamp was un-pressed !");
        run ( STOP, 255 );
        break;
      }
    }
    PC.println("Need to go towards home till the rung is reached");
    QUIT_OR_CONTINUE;
    while ( run ( HOME, 255) ) {
      if ( q_stop() ) break;
      update_trip(FIXEDCLAMP_TRIP);
      if ( fixedclamp_trip ) {
        PC.println("Fixed clamp was pressed !");
        run ( STOP, 255 );
        break;
      }
    }

    if ( n == 0 ) {
      PC.println("For the last rung, need to come down a little so tail gets support");
      QUIT_OR_CONTINUE;
      start_time = millis();
      while ( run ( MID, 255 ) ) { // Bot goes down a little
        if ( q_stop() ) break;
        if ( millis() - start_time > 200 ) { // % calib
          run(STOP, 255);
          PC.println("Time delay done ");
          break;
        }
      }

      PC.println("Need to activate the tail");
      QUIT_OR_CONTINUE;
      SLAVE.print(CLOSE);
    }

    PC.println("Need to make bot come down a bit so that fixed clamp doesnt get damaged ");
    QUIT_OR_CONTINUE;
    start_time = millis();
    while ( run ( MID, 255 ) ) { // Bot goes down a little
      if ( q_stop() ) break;
      if ( millis() - start_time > 200 ) { // % calib
        run(STOP, 255);
        PC.println("Time delay done ");
        break;
      }
    }

    PC.println("Need to unclamp the ladder");
    QUIT_OR_CONTINUE;
    piston(OPEN); // clamp open
    PC.println("Unclamped the left clamp");

    if ( n == 0 ) {
      PC.println("Need to deactivate tail piston through slave");
      QUIT_OR_CONTINUE;
      SLAVE.write(OPEN);
    }

    PC.println("Need to make the left clamp touch right clamp");
    QUIT_OR_CONTINUE;
    while ( run( MID, 255) ) { // go up till middle_trip
      if ( q_stop() ) break;
    }
  }

  // Last rung
  PC.println("Need to clamp the last rung");
  QUIT_OR_CONTINUE;
  piston(CLOSE);

  PC.println("Need to open tail to push the bot onto the platform and move up simultaneously.");
  QUIT_OR_CONTINUE;
  start_time = millis();
  while ( run ( HOME, 200 ) ) { // Bot goes up till home trips
    if ( q_stop() ) break;
    update_trip(FIXEDCLAMP_TRIP);
    if ( fixedclamp_trip ) {
      PC.println("Fixed clamp was pressed !");
      run ( STOP, 255 );
      break;
    }
  }
  PC.println("Need to make bot come down a bit so tail will hit ");
  QUIT_OR_CONTINUE;
  start_time = millis();
  while ( run ( MID, 255 ) ) { // Bot goes down a little
    if ( q_stop() ) break;
    if ( millis() - start_time > 200 ) { // % calib
      PC.println("Time delay done ");
      run(STOP, 255);
      PC.println("Activating tail piston through slave");
      SLAVE.write(CLOSE);
      break;
    }
  }

  PC.println("Go more up and close tail ");
  QUIT_OR_CONTINUE;
  start_time = millis();
  int close_tail_flag = 0;
  while ( run ( HOME, 255 ) ) { // Bot goes down a little
    if ( q_stop() ) break;
    if ( close_tail_flag == 0 && millis() - start_time > 300 ) { // % calib
      PC.println("Time delay done ");
      PC.println("Switching off tail piston through slave");
      SLAVE.write(OPEN);
      close_tail_flag = 1;
    }
  }


  PC.println("Need to open the left piston now");
  QUIT_OR_CONTINUE;
  piston(OPEN);

  PC.println("Push the left clamp towards center to finish ladder ");
  QUIT_OR_CONTINUE;
  start_time = millis();
  while ( run ( MID, 255 ) ) { // Bot goes down a little
    if ( q_stop() ) break;
    if ( millis() - start_time > 1200 ) { // % calib
      run(STOP, 255);
      PC.println("Time delay done ");
      break;
    }
  }

  PC.println("Close left clamp to push the bot up");
  QUIT_OR_CONTINUE;
  piston(CLOSE);

  // Flag
  PC.println("Awww ... no flag.");

  PC.println("Ladder Done!!!");

}

