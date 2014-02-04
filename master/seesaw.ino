void seesaw() {
   
  PC.println(F(">>>>>>>>>> Seesaw START"));
  
  // move left motor to extreme
  PC.println(F("Need to move left clamp to the extreme."));
  QUIT_OR_CONTINUE;
  while ( run( HOME, 255 ) ) {
    if ( q_stop() ) break;
  }
  SLAVE.print(MOVE);
  SLAVE.print(-255);
  listen();
  
  // move right motor to middle
  PC.println(F("Right clamp needs to go to the middle position."));
  QUIT_OR_CONTINUE;
  SLAVE.print(MOVE_MID);
  SLAVE.print(255);
  listen();

  // make right motor move a small distance
  PC.println(F("Need to move right clamp slightly more."));
  QUIT_OR_CONTINUE;
  SLAVE.print(MOVE);
  SLAVE.print(200);
  delay(150);
  SLAVE.print(STOP);


  // Clamp
  PC.println(F("Need to clamp both on seesaw."));
  QUIT_OR_CONTINUE;

  SLAVE.print(CLOSE);
  piston(CLOSE);
  delay(500);
  PC.println(F("FINISH SEESAW ... Need to UNclamp both on seesaw."));
  QUIT_OR_CONTINUE;

  SLAVE.print(OPEN);
  piston(OPEN);
 
  PC.println(F(">>>>>>>>>> Seesaw fully done"));
  delay(2000);
}
