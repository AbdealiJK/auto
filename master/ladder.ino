void ladder_init() {
  PC.println(F(">>>>>>>>>> Setting up LADDER"));
  QUIT_OR_CONTINUE;
  PC.println(F("Setup initial position"));
  SLAVE.print(MOVE);
  SLAVE.print(-255); 
  
  // What should the left clamp do ?
}
void ladder() {
  PC.println(F(">>>>>>>>>> Starting LADDER"));

  long start_time;

  int n = 4;
  while (n--) {

    PC.println(F("Need to close piston"));
    QUIT_OR_CONTINUE;
    piston(CLOSE);
    PC.println(F("Piston closed"));

    PC.println(F("Need to go towards home till just above last rung (i.e. fixed clamp should become untripped)"));
    QUIT_OR_CONTINUE;
    update(LADDER_IR);
    if ( ! ladder_ir ) {
      PC.println(F("Initially, fixed clamp was not tripped... But it should have been tripped ! (as it was at the ~prev rung)... so, maybe it went down too much ... going up till the last rung."));
      while ( run ( HOME, 255) ) {
        if ( q_stop() ) break;
        update(LADDER_IR);
        if ( ladder_ir ) {
          PC.println(F("Fixed clamp was pressed !"));
          run ( STOP, 0 );
          break;
        }
      }
    }
    while ( run ( HOME, 255) ) {
      if ( q_stop() ) break;
      update(LADDER_IR);
      if ( !ladder_ir ) {
        PC.println(F("Fixed clamp un-pressed !"));
        run ( STOP, 0 );
        break;
      }
    }
    PC.println(F("Need to go towards home till the rung is reached"));
    QUIT_OR_CONTINUE;
    while ( run ( HOME, 255) ) {
      if ( q_stop() ) break;
      update(LADDER_IR);
      if ( ladder_ir ) {
        PC.println(F("Fixed clamp pressed !"));
        run ( STOP, 0 );
        break;
      }
    }

    if ( n == 0 ) {
      PC.println(F("For the last rung, need to come down a little so tail gets support"));
      QUIT_OR_CONTINUE;
      start_time = millis();
      while ( run ( MID, 255 ) ) {
        if ( q_stop() ) break;
        if ( millis() - start_time > 200 ) { // DELAY alert
          run(STOP, 0);
          PC.println(F("Time delay done "));
          break;
        }
      }

      PC.println(F("Need to activate the tail"));
      QUIT_OR_CONTINUE;
      SLAVE.print(CLOSE);
    }

    PC.println(F("Need to make bot come down a bit so that fixed clamp doesnt get damaged "));
    QUIT_OR_CONTINUE;
    start_time = millis();
    while ( run ( MID, 255 ) ) {
      if ( q_stop() ) break;
      if ( millis() - start_time > 200 ) { // DELAY alert
        run(STOP, 0);
        PC.println(F("Time delay done "));
        break;
      }
    }

    PC.println(F("Need to unclamp the ladder"));
    QUIT_OR_CONTINUE;
    piston(OPEN); // clamp open
    PC.println(F("Unclamped the left clamp"));

    if ( n == 0 ) {
      PC.println(F("Need to deactivate tail piston through slave"));
      QUIT_OR_CONTINUE;
      SLAVE.write(OPEN);
    }

    PC.println(F("Need to make the left clamp touch right clamp"));
    QUIT_OR_CONTINUE;
    while ( run( MID, 255) ) { // go up till middle_trip
      if ( q_stop() ) break;
    }
  }

  // Last rung
  PC.println(F("Need to clamp the last rung"));
  QUIT_OR_CONTINUE;
  piston(CLOSE);

  PC.println(F("Need to open tail to push the bot onto the platform and move up simultaneously."));
  QUIT_OR_CONTINUE;
  start_time = millis();
  while ( run ( HOME, 200 ) ) { // Bot goes up till home trips
    if ( q_stop() ) break;
    update(LADDER_IR);
    if ( ladder_ir ) {
      PC.println(F("Fixed clamp was pressed !"));
      run ( STOP, 0 );
      break;
    }
  }
  PC.println(F("Need to make bot come down a bit so tail will hit "));
  QUIT_OR_CONTINUE;
  start_time = millis();
  while ( run ( MID, 255 ) ) { // Bot goes down a little
    if ( q_stop() ) break;
    if ( millis() - start_time > 200 ) { // DELAY alert
      run(STOP, 0);
      PC.println(F("Time delay done "));
      PC.println(F("Activating tail piston through slave"));
      SLAVE.write(CLOSE);
      break;
    }
  }

  PC.println(F("Go more up and close tail "));
  QUIT_OR_CONTINUE;
  start_time = millis();
  int close_tail_flag = 0;
  while ( run ( HOME, 255 ) ) { // Bot goes down a little
    if ( q_stop() ) break;
    if ( close_tail_flag == 0 && millis() - start_time > 300 ) { // % calib
      PC.println(F("Time delay done "));
      PC.println(F("Switching off tail piston through slave"));
      SLAVE.write(OPEN);
      close_tail_flag = 1;
    }
  }


  PC.println(F("Need to open the left piston now"));
  QUIT_OR_CONTINUE;
  piston(OPEN);

  PC.println(F("Push the left clamp towards center to finish ladder "));
  QUIT_OR_CONTINUE;
  start_time = millis();
  while ( run ( MID, 255 ) ) { // Bot goes down a little
    if ( q_stop() ) break;
    if ( millis() - start_time > 1200 ) { // DELAY alert
      run(STOP, 0);
      PC.println(F("Time delay done "));
      break;
    }
  }

  PC.println(F("Close left clamp to push the bot up"));
  QUIT_OR_CONTINUE;
  piston(CLOSE);

  // Flag
  PC.println(F("Awww ... no flag."));

  PC.println(F("Ladder Done!!!"));

}

