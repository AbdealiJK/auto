
void listen()
{
  while(1) // ~ is the terminating charachter for SLAVE to MASTER communication
  {
    if(NEXT.available()) {
      if ( NEXT.peek() == '~' ) {
        PC.println('~');
      }
      PC.print( NEXT.read() );
    }
    if ( PC.available() && PC.read() == 'q' ) {
      NEXT.print("q");//charachter to be sent to slave for emergency stop
    }
  }
}



