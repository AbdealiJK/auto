
void seesaw_init() {
  PC.println(F("SEESAW init"));

  PC.println(F("next : both home"));
  QUIT_OR_CONTINUE;
  go_home(BOTH, 255);

  PC.println(F("next : both move mid with delay"));
  QUIT_OR_CONTINUE;
  run(BOTH, MID, 255);
  long int start_time = millis();
  while (l_running != STOP || r_running != STOP ) {
    PC.print(l_running);
    PC.println(r_running);
    if ( q_stop() )   break;
    if ( millis() - start_time > SEESAW_TIME ) {
      run(BOTH, STOP, 0);
      PC.println("time delay over");
      break;
    }
  }
  PC.print(l_running);
  PC.println(r_running);
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

  while ( ! comm_trip ) {
    update(COMM_TRIP);
  }
  piston(RIGHT, OPEN);
  piston(LEFT, OPEN);
  PC.println(F(">>>>>>>>>> Seesaw fully done"));
}

