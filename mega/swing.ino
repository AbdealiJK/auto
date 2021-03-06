void swing_init() {
  PC.println(F("SWING init"));
  
  PC.println(F("next : both home"));
  QUIT_OR_CONTINUE;
  go_home(BOTH, SWING_PWM);

  PC.println(F("next : both move home with delay"));
  QUIT_OR_CONTINUE;
  long int start_time = millis();
  while (run(BOTH, MID, SWING_PWM)) { // >>>>>>>>>>>>>>>>. NOTICE : had to put 0.8 as motors are not responding same. or maybe MD ?
    if ( millis() - start_time > SWING_TIME ) {
      run(BOTH, STOP, 0);
      break;
    }
  }  
  PC.println(F("SWING init done"));
}
void swing_geton() {
  PC.println(F("SWING get on"));
  
  PC.println(F("next : clamp both ... waiting on comm trip"));
  update(COMM_TRIP);
  while ( comm_trip ) {
    update(COMM_TRIP);
  }
  piston(RIGHT, CLOSE);
  piston(LEFT, CLOSE);
  pp(MID, EXTEND);

  PC.println(F("SWING got on"));
}
void swing() {
  PC.println(F("SWING task"));
  pp(MID, EXTEND);
  PC.println(F("SWING task done"));
}
void swing_getoff() {
  PC.println(F("SWING get off"));
  
  PC.println(F("next : waiting for trip for a long time to arm it"));
  update(COMM_TRIP);
  long int start_time = millis();
  while (1) {
    if (comm_trip && millis() - start_time > 2000) {
      break;
    }
    if ( ! comm_trip ) {
      start_time = millis();
    }
    update(COMM_TRIP);
  }

  PC.println(F("next : unclamp both ... waiting on comm trip"));
  update(COMM_IR);
  while ( ! comm_ir ) {
    update(COMM_IR);
  }
  piston(RIGHT, OPEN);
  piston(LEFT, OPEN);
  pp(MID, SHRINK);
  PC.println(F("SWING got off"));
}

