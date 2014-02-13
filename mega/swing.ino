#define SWING_TIME     1000
void swing_init() {
  PC.println(F("SWING init"));
  
  PC.println(F("next : both home"));
  QUIT_OR_CONTINUE;
  go_home(BOTH, 200);

  PC.println(F("next : both move home with delay"));
  QUIT_OR_CONTINUE;
  long int start_time = millis();
  run(BOTH, MID, 200);
  while (l_running || r_running ) {
  if ( q_stop() )   break;
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

  PC.println(F("SWING got on"));
}
void swing() {
  PC.println(F("SWING task"));
  //pp(MID, EXTEND);
  PC.println(F("SWING task done"));
}
void swing_getoff() {
  PC.println(F("SWING get off"));
  update(COMM_TRIP);

  PC.println(F("next : unclamp both ... waiting on comm trip"));
  while ( 1 ) {
    if ( comm_trip)
      break;
    update(COMM_TRIP);
  }
  piston(RIGHT, OPEN);
  piston(LEFT, OPEN);
  pp(MID, SHRINK);
  PC.println(F("SWING got off"));
}

