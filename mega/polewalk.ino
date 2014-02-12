#define PW_MIRROR 0
void polewalk_init() {
  
  PC.print(F("............. Setting up Pole Walk "));

  // move left motor to extreme
  PC.println(F("Need to move both clamps to the extreme."));
  QUIT_OR_CONTINUE;
  go_home( BOTH );
  // move both motors to mid
  PC.println(F("Move both clamps to mid"));
  QUIT_OR_CONTINUE;
  go_mid(255);
  PC.println(F("Stopped both motors !"));
  
  if( PW_MIRROR )
  {
    pp(LEFT,EXTEND);
    pp(RIGHT,SHRINK);
  }
  else
  {
    pp(RIGHT,EXTEND);
    pp(LEFT,SHRINK);
  }
}

void polewalk_geton() {

  PC.println(F(">>>>>>>>>> Getting on to Pole Walk"));

  // Clamp
  PC.println(F("Need to clamp both on Pole Walk... "));
  update(COMM_TRIP);
  while ( comm_trip ) {
    update(COMM_TRIP);
  }
  piston(LEFT,CLOSE);
  piston(RIGHT,CLOSE);
  delay(200);
  pp(LEFT,SHRINK);
  pp(RIGHT,SHRINK);
}

void polewalk() {
  PC.print(F("............. Starting Pole Walk "));

  // move left to extreme, move right to extreme
  PC.println(F("Need to unclamp left and move both to the extreme."));
  QUIT_OR_CONTINUE;
  piston(RIGHT, CLOSE);
  piston(LEFT, OPEN);
  go_home(BOTH); // moves both motor home simultaenolusly
  piston(LEFT, CLOSE);
  delay(500);
  piston(RIGHT, OPEN);
  go_mid(255); // moves both to home, then moves left to mid and then right
  piston(RIGHT, CLOSE);
  pp(LEFT, EXTEND);
  PC.println(F("Polewalk completed .... "));

}

void polewalk_getoff() {
  PC.println(F("............. Get off of Pole Walk "));

  // move both motors to middle
  PC.println(F("Need to UNclamp both on pole walk... "));
  update(COMM_IR);
  while ( ! comm_ir ) {
    update(COMM_IR);
  }
  PC.println(F("Fingers detected! Waiting for the manual bot to stabilize"));
  delay(3000);
  pp(LEFT, SHRINK);
  pp(RIGHT, SHRINK);
  piston(LEFT, OPEN);
  piston(RIGHT, OPEN);
  
}
