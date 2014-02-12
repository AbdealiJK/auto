#define SS_VEL 255
#define MID_TIME 500 // both clamps go to mid and go towards home for sli amount of time = MID_TIME
void seesaw_init()
{

  PC.println(F(">>>>>>>>>> Setting up Seesaw"));
  // move left motor to extreme
  PC.println(F("Need to move both clamps to the extreme."));
  QUIT_OR_CONTINUE;
  go_home( BOTH );// moves both motor home simultaenolusly

  PC.println(F("Both clamps go to mid."));
  QUIT_OR_CONTINUE;
  go_mid(255);// moves both to home, then moves left to mid and then right

  PC.println(F("Both clamps go out slightly."));
  QUIT_OR_CONTINUE;
  long int start_time = millis();
  run(RIGHT, HOME, SS_VEL);
  run(RIGHT, HOME, SS_VEL);
  while (l_running || r_running ) {
  if ( q_stop() ) break;
    if ( millis() - start_time > MID_TIME ) {
      run ( LEFT, STOP, 0 );
      run ( RIGHT, STOP, 0 );
      break;
    }
  }
}
void seesaw_geton()
{
  PC.println(F(">>>>>>>>>> Getting on to Seesaw"));
  // Clamp
  PC.println(F("Need to clamp both on seesaw... "));
  update(COMM_TRIP);
  while ( comm_trip ) {
    update(COMM_TRIP);
  }
  piston(RIGHT, CLOSE);
  piston(LEFT, CLOSE);

}
void seesaw_getoff()
{
  PC.println(F("FINISH SEESAW ... Need to UNclamp both on seesaw."));
  update(COMM_IR);

  while ( 1 ) {
    if (! comm_ir)
      break;
    update(COMM_IR);
  }
  piston(RIGHT, OPEN);
  piston(LEFT, OPEN);
  PC.println(F(">>>>>>>>>> Seesaw fully done"));
}
void seesaw()
{
  seesaw_init();
  seesaw_geton();
  seesaw_getoff();
}

