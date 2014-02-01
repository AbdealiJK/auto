
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

void seesaw() {
  PC.println(">>>>>>>>>> Seesaw START");

  // move left motor to extreme
  PC.println("Need to move left clamp to the extreme.");
  QUIT_OR_CONTINUE;
  while ( run( HOME, 255 ) ) {
    if ( q_stop() ) break;
  }
  
  // move right motor to middle
  PC.println("Right clamp needs to go to the middle position.");
  QUIT_OR_CONTINUE;
  NEXT.print('r');
  NEXT.print('i');
  NEXT.print(255);
  listen();

  // make right motor move a small distance
  PC.println("Need to move right clamp slightly more.");
  QUIT_OR_CONTINUE;
  NEXT.print('r');
  NEXT.print('v');
  NEXT.print(200);
  delay(100);
  NEXT.print('q');
  
  // Clamp
  PC.println("Need to clamp both on seesaw.");
  QUIT_OR_CONTINUE;
  NEXT.print('r');
  NEXT.print('p');
  NEXT.print('c');
  piston(CLOSE);

  PC.println("FINISH SEESAW ... Need to UNclamp both on seesaw.");
  QUIT_OR_CONTINUE;
  NEXT.print('r');
  NEXT.print('p');
  NEXT.print('o');
  piston(OPEN);

  
  
  PC.println(">>>>>>>>>> Seesaw fully done");
}
