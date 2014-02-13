/*# define LADDER_TIME 200
void ladder_init() {
  PC.println(F("LADDER init"));

  PC.println(F("LADDER init done"));
}
void ladder_geton() {
  PC.println(F("LADDER get on"));

  PC.println(F("LADDER got on"));
}
void ladder() {
  PC.println(F("LADDER task"));

  int n = 4;
  while (n--) {
    PC.println(F("next : clamp ladder"));
    QUIT_OR_CONTINUE;
    piston(CLOSE);

    PC.println(F("next : left home"));
    QUIT_OR_CONTINUE;
    int flag = 0;
    run(LEFT, HOME, 200);
    while ( l_running || r_running ) {
      if ( q_stop() ) break;
      update(LADDER_IR);
      if ( flag == 0 && ladder_ir ) {
        flag++;
      } else if ( flag == 1 && ! ladder_ir ) {
        flag++;
      } else if ( flag == 2 && ladder_ir ) {
        run( LEFT, STOP, 0 );
        PC.println(F(" rung detected by IR "));
        break;
      }
    }

    if ( n == 0 ) {
      PC.println(F("next : come done a bit for tail"));
      QUIT_OR_CONTINUE;
      start_time = millis();
      while ( run ( MID, 255 ) ) {
        if ( q_stop() ) break;
        if ( millis() - start_time > LADDER_TIME ) {
          run(BOTH, STOP, 0);
          PC.println(F(" time delay done "));
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

  PC.println(F("LADDER task done"));
}
void ladder_getoff() {
  PC.println(F("LADDER get off"));
  PC.println(F("LADDER got off"));
}*/
