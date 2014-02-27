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
  go_home(RIGHT, LADDER_PWM);
  go_away(LEFT, LADDER_PWM);

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
    if ( ladder_ir )  go_up(LADDER_PWM, 2);
    else              go_up(LADDER_PWM, 3);


    if ( n != 0 ) {
      long start_time = millis();
      while ( run( LEFT, HOME, LADDER_PWM ) ) {
        if ( millis() - start_time > LADDER_TIME(n) ) {
          run(BOTH, STOP, 0);
          PC.println(millis() - start_time );
          PC.println(F(" time delay done "));
          break;
        }
      }
    } if ( n == 0 ) {
      PC.println(F("next : tail open and going down a little more"));
      QUIT_OR_CONTINUE;
      piston(RIGHT, CLOSE);
      delay(1500);
      start_time = millis();
      while ( run( LEFT, MID, 255 ) ) {
        if ( millis() - start_time > LADDER_TIME(n) ) {
          run(BOTH, STOP, 0);
          PC.println(F(" time delay done "));
          break;
        }
      }
    }

    PC.println(F("next : unclamp rung"));
    QUIT_OR_CONTINUE;
    piston(LEFT, OPEN);
    
    if ( n == 0 ) {
      PC.println(F("next : tail open"));
      delay(500); 
      piston(RIGHT, OPEN);
      delay(500); 
    }
    PC.println(F("next - left away"));
    QUIT_OR_CONTINUE;
    go_away(LEFT, 255);
  }

  // Last rung
  PC.println(F("next : clamp last rung"));
  QUIT_OR_CONTINUE;
  piston(LEFT, CLOSE);

  PC.println(F("next : go up, open and close tail to tip off"));
  QUIT_OR_CONTINUE;
  go_up(255, 3);
  piston(RIGHT, CLOSE);
  delay(500);
  
  start_time = millis();
  int close_tail_flag = 0;
  while ( run ( LEFT, HOME, 255 ) ) {
    if ( q_stop() ) break;
    if ( close_tail_flag == 0 && millis() - start_time > 500 ) {
      PC.println(F("Time delay done - Switching off tail piston"));
      piston(RIGHT, OPEN);
      close_tail_flag = 1;
    }
  }

  PC.println(F("next : leave ladder and go to mid"));
  QUIT_OR_CONTINUE;
  piston(LEFT, OPEN);
  go_mid(LEFT, LADDER_PWM);

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
