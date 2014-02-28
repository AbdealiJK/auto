
void seesaw_init() {
  PC.println(F("SEESAW init"));

  PC.println(F("next : both home"));
  QUIT_OR_CONTINUE;
  go_home(BOTH, SEESAW_PWM);

  PC.println(F("next : both move mid with delay"));
  QUIT_OR_CONTINUE;
  
/*  long int start_time = millis();
  while ( run(LEFT, MID, SEESAW_PWM * 0.8) && run(RIGHT, MID, SEESAW_PWM) ) { // >>>>>>>>>>>>>>>>. NOTICE : had to put 0.8 as motors are not responding same. or maybe MD ?
    if ( q_stop() )   break;
    if ( millis() - start_time > SEESAW_TIME ) {
      run(BOTH, STOP, 0);
      PC.println("time delay over");
      break;
    }
  }
*/
  while ( run(LEFT, MID, SEESAW_PWM) ) {
    if ( q_stop() )   break;
    update(L_SEESAW_IR);
    if ( ! l_seesaw_ir ) {
      run(LEFT, STOP, 255);
      break;
    }
  }
  PC.println(F("next : right to seesaw position"));
  QUIT_OR_CONTINUE;
  int flag_clamp_seen = 0;
  while ( run(RIGHT, MID, SEESAW_PWM) ) {
    if ( q_stop() )   break;
    update(R_SEESAW_IR);
    if ( r_seesaw_ir ) {
      flag_clamp_seen = 1;
    }
    if ( (! r_seesaw_ir) && flag_clamp_seen ) {
      run(RIGHT, STOP, 255);
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
  delay(10000);
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

