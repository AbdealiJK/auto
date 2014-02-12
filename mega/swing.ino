#define SW_H_VEL 255
#define SW_VEL 255
void swing_init()
{

  PC.println(F(">>>>>>>>>> Setting up Swing"));
  // move left motor to extreme
  PC.println(F("Need to move both clamps to the extreme."));
  QUIT_OR_CONTINUE;
  go_home();

  PC.println(F("Both clamps go to mid."));
  QUIT_OR_CONTINUE;
  go_mid();


}
void swing_geton()
{
  PC.println(F(">>>>>>>>>> Getting on to Swing"));
  // Clamp
  PC.println(F("Need to clamp both on swing... "));
  update(COMM_TRIP);
  while ( comm_trip ) {
    update(COMM_TRIP);
  }
  piston(RIGHT, CLOSE);
  piston(LEFT, CLOSE);
  
  // !!!!!!!!!!!!!!!!!!!!! code for middle PP to be written !!!!!!!!!!!!!

}
void swing_getoff()
{
  PC.println(F("FINISH SWING ... Need to UNclamp both on swing."));
  update(COMM_TRIP);

  while ( 1 ) {
    if (! comm_trip)
      break;
    update(COMM_TRIP);
  }
  piston(RIGHT, OPEN);
  piston(LEFT, OPEN);
  PC.println(F(">>>>>>>>>> Swing fully done"));
}
void swing()
{
  swing_init();
  swing_geton();
  swing_getoff();
}

