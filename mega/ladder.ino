// initially TSOP may flicker too much, so i guess  it would be better to check for time between flicker initially and do. other than this. everything is fine. also mech wise, last  rung not being clamped. ALso tail piston must remain closed TILL just before the last rung. otherwise last rung wont be clamped. Dont know how to do that.
void ladder_init() {
  PC.println(F("LADDER init"));

  PC.println(F("LADDER init done"));
}
void ladder_geton() {
  PC.println(F("LADDER get on"));

  //  PC.println(F("next : clamp ladder"));
  //  QUIT_OR_CONTINUE;
  //  piston(CLOSE);

  PC.println(F("LADDER got on"));
}
void ladder() {
  PC.println(F("LADDER task"));
  long start_time = 0;

  PC.println(F("next - left away"));
  QUIT_OR_CONTINUE;
  go_away(LEFT, 255);

  int n = 3;
  while (n--) {
    PC.print(n);
    PC.println(" start<<<<<");
    PC.println(F("next : clamp ladder"));
    QUIT_OR_CONTINUE;
    piston(LEFT, CLOSE);

    PC.println(F("next : bot up - left home for ladder rungs"));
    QUIT_OR_CONTINUE;
    update(LADDER_IR);
    if(n)
    {
    if ( ladder_ir )  go_up(255, 2,0); // i guess its only till for the initial thing i tink it must be 2
    else              go_up(255, 3,0);
    }
    if ( n == 0 ) {
    if ( ladder_ir )  go_up(255, 2,1); // i guess its only till for the initial thing i tink it must be 2
    else              go_up(255, 3,1);
   

     
//      piston(RIGHT, CLOSE);
            PC.println(F("next : tail open and going down a little more"));
       QUIT_OR_CONTINUE;
      delay(250);
      start_time = millis();
      while ( run( LEFT, MID, 255 ) ) {
        if ( millis() - start_time > LADDER_TIME ) {
          run(BOTH, STOP, 0);
          PC.println(F(" time delay done "));
          break;
        }
      }
    }

    PC.println(F("next : unclamp rung"));
    QUIT_OR_CONTINUE;
    piston(LEFT, OPEN);

    PC.println(F("next - left away"));
    QUIT_OR_CONTINUE;
    go_away(LEFT, 255);
  }

  // Last rung
  PC.println(F("next : clamp last rung"));
  QUIT_OR_CONTINUE;
  piston(LEFT, CLOSE);

  PC.println(F("next : go up"));
  QUIT_OR_CONTINUE;
 piston(RIGHT, OPEN);  
  go_up(255, 3,1);


  start_time = millis();
  int close_tail_flag = 0;
  while ( run ( LEFT, HOME, 255 ) ) { // Bot goes down a little
    if ( q_stop() ) break;
    if ( close_tail_flag == 0 && millis() - start_time > 800 ) { // % calib
      PC.println(F("Time delay done "));
      PC.println(F("Switching off tail piston through slave"));
      piston(RIGHT, OPEN);
      close_tail_flag = 1;
    }
  }

  PC.println(F("next : leave ladder"));
  QUIT_OR_CONTINUE;


  PC.println(F("next : go onto platform"));
  QUIT_OR_CONTINUE;
  start_time = millis();
  go_mid(LEFT, 255);
  piston(LEFT, CLOSE);

  PC.println(F("LADDER task done"));
}
void ladder_getoff() {
  PC.println(F("LADDER get off"));
  PC.println(F("LADDER got off"));
}
