#define PW_MIRROR 0
void polewalk_init() {
  
  PC.print(F("............. Setting up Pole Walk "));

  // move left motor to extreme
  PC.println(F("Need to move both clamps to the extreme."));
  QUIT_OR_CONTINUE;
  go_home(BOTH);
  // move both motors to mid
  PC.println(F("Move both clamps to mid"));
  QUIT_OR_CONTINUE;
  move_mid();
  PC.println("Stopped both motors !");
  
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

  piston(LEFT,CLOSE);
  piston(RIGHT,OPEN);
  
  // move left to extreme, move right to extreme
  PC.println(F("Need to move left clamp to the extreme."));
  QUIT_OR_CONTINUE;

  piston(OPEN);
  while ( run( HOME, 255 ) ) {
    if ( q_stop() ) break;
  }

  PC.println(F("Need to open and move right clamp to the extreme."));
  SLAVE.print(MOVE);
  SLAVE.print(-255);
  listen();


  // clamp left
  PC.println(F("Left clamp needs to be clamped now."));
  QUIT_OR_CONTINUE;
  piston(CLOSE);
  delay(500);
  SLAVE.print(OPEN);

  PC.println(F("Move master to mid first and then slave to mid"));
  QUIT_OR_CONTINUE;
  while ( run( MID, 255 ) ) {
    if ( q_stop() ) break;
    update(MID_IR);
    if ( mid_ir ) {
      run ( STOP, 0 );
      PC.print(F("IR reached.... "));
      break;
    }
  }

  PC.print(F("Need to move slave"));
  //  QUIT_OR_CONTINUE;
  SLAVE.print(MOVE);
  SLAVE.print(150);
  PC.print(F("Slave moving "));
  update(MID_TRIP);
  while (1) {
    if ( q_stop() ) break;
    update(MID_TRIP);
    if ( mid_trip ) {
      SLAVE.print(STOP);
      break;
    }
  }
  PC.println("Stopped both motors !");
  listen();
  SLAVE.print(SHRINK);
  pp(EXTEND);

  PC.println(F("Right clamp needs to clamp now"));
  QUIT_OR_CONTINUE;
  //MSLAVE.print(CLOSE);

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
  delay(3000);

  SLAVE.print(SHRINK);
  pp(SHRINK);
  piston(OPEN);
  SLAVE.print(OPEN);
  delay(5000);
}
