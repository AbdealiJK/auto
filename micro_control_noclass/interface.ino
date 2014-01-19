int pc_get_int() {
  int temp = 0, next_val;
  char temp_c;
  
  while(!PC.available());
  delay(2);
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
  char temp;
  while (temp != PC_END)
  {
    if (NEXT.available()) {
      temp  = NEXT.read();
      PC.print( temp );
    }
    if ( PC.available() && PC.read() == 'q' ) {
      NEXT.print('q'); // charachter to be sent to slave for emergency stop
    }
  }
}



