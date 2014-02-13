void polewalk_init() {
  PC.println(F("POLEWALK init"));
  update(COMM_TRIP);  
  if( ! comm_ir)
  {
    PC.println(F("next : both home"));
    QUIT_OR_CONTINUE;
    go_home( BOTH, 255 );
  
    PC.println(F("next : both mid"));
    QUIT_OR_CONTINUE;
    go_mid(BOTH, 255);
  }
  else{
    PC.println(F("Left already at middle. moving right to middle"));
    QUIT_OR_CONTINUE;
    go_mid(RIGHT, 255);
  }
  
  PC.println(F("both stopped"));
  run(BOTH, STOP, 0);
  
  PC.println(F("both pp"));
  if( MIRROR ) {
    pp(RIGHT,EXTEND);
    pp(LEFT,SHRINK);
  }
  else {
    pp(LEFT,EXTEND);
    pp(RIGHT,SHRINK);
  }
  PC.println(F("POLEWALK init done"));
}

void polewalk_geton() {
  PC.println(F("POLEWALK geton"));

  // Clamp
  PC.println(F("next : both clamp ... waiting on comm trip"));
  update(COMM_TRIP);
  while ( comm_trip ) {
    update(COMM_TRIP);
  }
  PC.println(F("somebody threw me"));
  piston(LEFT,CLOSE);
  piston(RIGHT,CLOSE);
  
  delay(255);
  pp(LEFT,SHRINK);
  pp(RIGHT,SHRINK);
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
  go_home(BOTH, 255);

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
  go_mid(BOTH, 255); // moves both to home, then moves left to mid and then right
  piston(RIGHT, CLOSE);
  pp(RIGHT, EXTEND);
  pp(LEFT, SHRINK);

  PC.println(F("POLEWALK task done"));

}

void polewalk_getoff() {
  PC.println(F("POLEWALK getoff"));
  piston(LEFT, CLOSE);
  piston(RIGHT, CLOSE);
  PC.println(F("next : unclamp ... waiting on comm ir"));
  update(COMM_IR);
  while ( ! comm_ir ) {
    update(COMM_IR);
  }
  PC.println(F("fingers detected"));
  delay(1000);
  piston(LEFT, OPEN);
  piston(RIGHT, OPEN);
  delay(250);
  pp(LEFT, SHRINK);
  pp(RIGHT, SHRINK);
  
  PC.println(F("POLEWALK gotoff"));
}

