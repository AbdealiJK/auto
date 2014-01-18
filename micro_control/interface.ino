void query(char str[])
{
  int i = 0;
  while (str[i] != '\0')
  {
    NEXT.print(str[i]);
    i++;
  }

}
void query(char ch)
{
  NEXT.print(ch);
}
void query(float f)
{
  NEXT.print(f);
}
void query(int f)
{
  NEXT.print(f);
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



