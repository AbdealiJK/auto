int get_int() {
  int temp = 0, next_val;
  char temp_c;
  while(!PC.available());
  next_val = PC.peek();
  while ( PC.available() && next_val <= '9' && next_val >= '0' ) {
    PC.read();
    temp *= 10;
    temp += next_val - '0';
    next_val = PC.peek();
  }
  return temp;
}
void listen()
{
  while (1) // ~ is the terminating charachter for SLAVE to MASTER communication
  {
    if (NEXT.available()) {
      if ( NEXT.peek() == TERMINATING_CHAR ) {
        PC.println(NEXT.read());
        break;
      }

      PC.print( NEXT.read() );
    }
    if ( PC.available() && PC.read() == 'q' ) {
      NEXT.print("q");//charachter to be sent to slave for emergency stop
    }
  }
}



