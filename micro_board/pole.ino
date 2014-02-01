
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

void polewalk() {

  PC.print("............. Pole Walk start ");

  // move both motors to middle
  PC.println("Right clamp needs to go to the middle position.");
  QUIT_OR_CONTINUE;
  NEXT.print('r');
  NEXT.print('i');
  NEXT.print(255);
  listen();
  
  PC.println("Left clamp needs to go to middle now.");
  QUIT_OR_CONTINUE;
  while ( run( MID, 255 ) ) {
    if ( q_stop() ) break;
  }
  
  // clamp right piston
  PC.println("Need to clamp right poston to the second pole.");
  QUIT_OR_CONTINUE;
  NEXT.print('r');
  NEXT.print('p');
  NEXT.print('c');
  
  // move left to extreme, move right to extreme
  PC.println("Need to move right clamp to the extreme.");
  QUIT_OR_CONTINUE;
  while(NEXT.available()) NEXT.read();
  NEXT.print('r');
  NEXT.print('v');
  NEXT.print(-255);
  listen();
  
  PC.println("Need to move left clamp to the extreme.");
  QUIT_OR_CONTINUE;
  while ( run( HOME, 255 ) ) {
    if ( q_stop() ) break;
  }
  
  
  // clamp left
  PC.println("Left clamp needs to be clamped now.");
  QUIT_OR_CONTINUE;
  piston(CLOSE);
  delay(500);
  NEXT.print('r');
  NEXT.print('p');
  NEXT.print('o');
  
  // move right to middle and left to middle
  PC.println("Right clamp needs to go to the middle position.");
  QUIT_OR_CONTINUE;
  NEXT.print('r');
  NEXT.print('i');
  NEXT.print(255);
  listen();
  
  PC.println("Left clamp needs to go to middle now.");
  QUIT_OR_CONTINUE;
  while ( run( MID, 255 ) ) {
    if ( q_stop() ) break;
  }
  Serial.println("Right clamp needs to clamp now");
  QUIT_OR_CONTINUE;
  NEXT.print('r');
  NEXT.print('p');
  NEXT.print('c');
  Serial.println("Both clamps need to unclamp now");
  QUIT_OR_CONTINUE;
  piston(OPEN);
  NEXT.print('r');
  NEXT.print('p');
  NEXT.print('o');
 
 
  
  PC.println("Polewalk completed .... ");
  
}
