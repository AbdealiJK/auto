void polewalk_init() {
  PC.print(F("............. Setting up Pole Walk "));

  // move left motor to extreme
  PC.println(F("Need to move both clamps to the extreme."));
  QUIT_OR_CONTINUE;
  SLAVE.print(MOVE);
  SLAVE.print(-255);
  while ( run( HOME, 255 ) ) {
    if ( q_stop() ) break;
  }
  listen();

  // ------------------------------------------------------------- GO TO MID WITH MASTER
  PC.println(F("Move master to mid first and then slave to mid"));
  QUIT_OR_CONTINUE;
  while ( run( MID, 255 ) ) {
    if ( q_stop() ) break;
    update(MID_IR);
    if ( mid_ir ) {
      run ( STOP, 255 );
      PC.print(F("IR reached.... "));
      break;
    }
  }
  SLAVE.print(MOVE);
  SLAVE.print(255);
   PC.print(F("Slave moving "));
      update(MID_TRIP);
  while ( !mid_trip ) {
    update(MID_TRIP);
  }
  SLAVE.print(STOP);
  PC.println("Stopped both motors !");
  listen();
  
  pp(OPEN);
  
/*** 
  // ------------------------------------------------------------- GO TO MID WITH SLAVE
  PC.println(F("Right clamp needs to go to the middle position."));
  QUIT_OR_CONTINUE;
  SLAVE.print(MOVE_MID);
  SLAVE.print(255);
  listen();
  
  PC.println(F("Left clamp needs to go to middle now."));
  QUIT_OR_CONTINUE;
  while ( run( MID, 255 ) ) {
    if ( q_stop() ) break;
  } 
 
 ***/ 
}

void polewalk_geton() {

  PC.println(F(">>>>>>>>>> Getting on to Pole Walk"));

  // Clamp
  PC.println(F("Need to clamp both on Pole Walk... "));
  update(COMM_TRIP);
  while ( comm_trip ) {
    update(COMM_TRIP);
  }
  SLAVE.print(CLOSE);
  piston(CLOSE);

  while(SLAVE.available()) SLAVE.read();
   
}

void polewalk() {
  PC.print(F("............. Starting Pole Walk "));
  delay(1000);
  piston(CLOSE);
  
  // move left to extreme, move right to extreme
  PC.println(F("Need to move left clamp to the extreme."));
  QUIT_OR_CONTINUE;
  while(SLAVE.available()) SLAVE.read();
  piston(OPEN);
  while ( run( HOME, 255 ) ) {
    if ( q_stop() ) break;
  }
  
  PC.println(F("Need to open and move rihgt clamp to the extreme."));
  QUIT_OR_CONTINUE;
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
      run ( STOP, 255 );
      PC.print(F("IR reached.... "));
      break;
    }
  }
  SLAVE.print(MOVE);
  SLAVE.print(255);
   PC.print(F("Slave moving "));
      update(MID_TRIP);
  while ( !mid_trip ) {
    update(MID_TRIP);
  }
  SLAVE.print(STOP);
  listen();
  
  PC.println(F("Right clamp needs to clamp now"));
  QUIT_OR_CONTINUE;
  SLAVE.print(CLOSE);
 
  PC.println(F("Polewalk completed .... "));
  
}

void polewalk_getoff() {
  PC.print(F("............. Get off to Pole Walk "));

  // move both motors to middle
  PC.println(F("Need to UNclamp both on pole walk... "));
  update(COMM_IR);
  while ( ! comm_ir ) {
    update(COMM_IR);
  }
  delay(1000);
  piston(OPEN);
  SLAVE.print(OPEN);
}
