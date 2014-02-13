#define SEESAW_TIME     1500
void seesaw_init() {
  PC.println(F("SEESAW init"));
  
  PC.println(F("next : both home"));
  QUIT_OR_CONTINUE;
  go_home(BOTH, 200);

  PC.println(F("next : both move home with delay"));
  QUIT_OR_CONTINUE;
  long int start_time = millis();
  run(BOTH, MID, 200);
  while (l_running || r_running ) {
  if ( q_stop() )   break;
    if ( millis() - start_time > SEESAW_TIME ) {
      run(BOTH, STOP, 0);
      break;
    }
  }
  PC.println(F("SEESAW init done"));
}
void seesaw_geton() {
  PC.println(F("SEESAW get on"));
  // Clamp
  PC.println(F("Need to clamp both on seesaw... "));
  update(COMM_TRIP);
  while ( comm_trip ) {
    update(COMM_TRIP);
  }
  piston(RIGHT, CLOSE);
  piston(LEFT, CLOSE);

}
void seesaw() {
}
void seesaw_getoff() {
  PC.println(F("FINISH SEESAW ... Need to UNclamp both on seesaw."));
  update(COMM_TRIP);

  while ( 1 ) {
    if (! comm_trip)
      break;
    update(COMM_TRIP);
  }
  piston(RIGHT, OPEN);
  piston(LEFT, OPEN);
  PC.println(F(">>>>>>>>>> Seesaw fully done"));
}

