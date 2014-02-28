void polewalk_init() {
  PC.println(F("POLEWALK init"));
  update(COMM_TRIP);
  PC.println(F("next : both home"));
  QUIT_OR_CONTINUE;
  go_home( BOTH, POLEWALK_PWM );

  PC.println(F("next : both mid"));
  QUIT_OR_CONTINUE;
  go_mid(BOTH, POLEWALK_PWM);

  PC.println(F("both pp"));
  pp(SIDES, EXTEND);
  pp(MID, SHRINK);
  PC.println(F("POLEWALK init done"));
}

void polewalk_geton() {
  PC.println(F("POLEWALK geton"));

  PC.println(F("both pp"));
  pp(SIDES, EXTEND);
  pp(MID, SHRINK);

  // Clamp
  PC.println(F("next : both clamp ... waiting on comm trip"));
  update(COMM_TRIP);
  while ( comm_trip ) {
    update(COMM_TRIP);
  }
  piston(BOTH, CLOSE);
  PC.println(F("somebody threw me"));

  delay(255);
  pp(SIDES, SHRINK);
  PC.println(F("POLEWALK goton"));
}

void polewalk() {
  PC.println(F("POLEWALK task"));

  PC.println(F("next : both home"));
  QUIT_OR_CONTINUE;
  if ( MIRROR ) {
    piston(RIGHT, CLOSE);
    delay(500);
    piston(LEFT, OPEN);
  } else {
    piston(LEFT, CLOSE);
    delay(500);
    piston(RIGHT, OPEN);
  }
  go_home(BOTH, POLEWALK_PWM);

  PC.println(F("next : clamp / unclamp"));
  QUIT_OR_CONTINUE;
  if ( MIRROR ) {
    piston(LEFT, CLOSE);
    delay(500);
    piston(RIGHT, OPEN);
    delay(500);
  } else {
    piston(RIGHT, CLOSE);
    delay(500);
    piston(LEFT, OPEN);
    delay(500);
  }
  PC.println(F("next : both mid"));
  QUIT_OR_CONTINUE;
  go_mid(BOTH, POLEWALK_PWM); // moves both to home, then moves left to mid and then right
  piston(RIGHT, CLOSE);
  piston(LEFT, CLOSE);

  pp(SIDES, EXTEND);
  
  PC.println(F("POLEWALK task done"));
}

void polewalk_getoff() {
  PC.println(F("POLEWALK getoff"));

  PC.println(F("next : unclamp ... waiting on comm ir"));
  update(COMM_IR);
  while ( ! comm_ir ) {
    update(COMM_IR);
  }
  PC.println(F("fingers detected"));
  // delay(1000);
  piston(BOTH, OPEN);
  delay(250);
  pp(SIDES, SHRINK);

  PC.println(F("POLEWALK gotoff"));
}

