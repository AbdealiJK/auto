void seesaw_init() {
  long start_time = 0;
  /***  
  --------------------------------------------------------- MAKE IT GO TO THE CORNER
    int go_towards = 'r';
    PC.println(F(">>>>>>>>>> Setting up Seesaw"));

    // move left motor to extreme
    PC.println(F("Need to move both clamps to the extreme."));
    QUIT_OR_CONTINUE;
    SLAVE.print(MOVE);
    SLAVE.print(-255);
    while ( run( HOME, 255 ) ) {
      if ( q_stop() ) break;
    }
    listen();

    // move right motor to middle
    if ( go_towards == 'l' ) {
      PC.println(F("Right clamp needs to go to the middle position."));
      QUIT_OR_CONTINUE;
      SLAVE.print(MOVE_MID);
      SLAVE.print(255);
      listen();
      // make right motor move a small distance
      PC.println(F("Need to move left clamp slightly more."));
      QUIT_OR_CONTINUE;
      SLAVE.print(MOVE);
      SLAVE.print(200);
      delay(150);
      SLAVE.print(STOP);
      PC.print(F(" Seesaw position reached "));
      listen();
    } else {

      PC.println(F("Left clamp needs to go to the middle position."));
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
      PC.println(F("Left clamp needs to go slightly more."));
      QUIT_OR_CONTINUE;
      start_time = millis();
      while ( run( MID, 255 ) ) {
        if ( q_stop() ) break;
        update(MID_IR);
        if ( millis() - start_time > 600 ) {
          run ( STOP, 255 );
          PC.print(F(" Seesaw position reached "));
          break;
        }
      }
    }
  ***/

  /***  
  ------------------------------------------------------- MAKE IT GO TO THE CCENTRE AND DELAY
  PC.println(F(">>>>>>>>>> Setting up Seesaw"));

  // move left motor to extreme
  PC.println(F("Need to move both clamps to the extreme."));
  QUIT_OR_CONTINUE;
  SLAVE.print(MOVE);
  SLAVE.print(-255);
  while ( run( HOME, 255 ) ) {
    if ( q_stop() ) break;
  }
  listen();

  PC.println(F("Both clamps go to mid."));
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
  update(MID_TRIP);
  while ( !mid_trip ) {
    update(MID_TRIP);
  }
  SLAVE.print(STOP);
  
  PC.println(F("Both clamps go out slightly."));
  QUIT_OR_CONTINUE;
  start_time = millis();
  while ( run( HOME, 255 ) ) {
    if ( q_stop() ) break;
    if ( millis() - start_time > 500 ) {
      run ( STOP, 255 );
      break;
    }
  }
  SLAVE.print(MOVE);
  SLAVE.print(-255);
  delay(500);
  SLAVE.print(STOP);
  ***/
  
  //------------------------------------------------------- MAKE IT GO TO THE EDGE and DELYS
  PC.println(F(">>>>>>>>>> Setting up Seesaw"));
 
  // move left motor to extreme
  PC.println(F("Need to move both clamps to the extreme."));
  QUIT_OR_CONTINUE;
  SLAVE.print(MOVE);
  SLAVE.print(-255);
  while ( run( HOME, 255 ) ) {
    if ( q_stop() ) break;
  }
  listen();

  PC.println(F("Both clamps go mid slightly."));
  QUIT_OR_CONTINUE;
  start_time = millis();
  while ( run( MID, 255 ) ) {
    if ( q_stop() ) break;
    if ( millis() - start_time > 1200 ) {
      run ( STOP, 255 );
      break;
    }
  }
  SLAVE.print(MOVE);
  SLAVE.print(255);
  delay(1200);
  SLAVE.print(STOP);
  
}

void seesaw_geton() {

  PC.println(F(">>>>>>>>>> Getting on to Seesaw"));

  // Clamp
  PC.println(F("Need to clamp both on seesaw... "));
  update(COMM_TRIP);
  while ( comm_trip ) {
    update(COMM_TRIP);
  }
  SLAVE.print(CLOSE);
  piston(CLOSE);

}

void seesaw() {
  
}

void seesaw_getoff() {
  PC.println(F(">>>>>>>>>> Seesaw START"));

  PC.println(F("FINISH SEESAW ... Need to UNclamp both on seesaw."));
  //  QUIT_OR_CONTINUE;

  update(COMM_TRIP);
  while ( ! comm_trip ) {
    update(COMM_TRIP);
  }
  SLAVE.print(OPEN);
  piston(OPEN);

  PC.println(F(">>>>>>>>>> Seesaw fully done"));

}
