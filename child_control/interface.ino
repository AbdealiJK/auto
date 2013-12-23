void query(char str[])
{
  int i=0;
  while(str[i]!='\0')
  {
    NEXT.print(str[i]);
    i++;
  }
  
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
    char c='\0';
    while(c!='~') // ~ is the terminating charachter for SLAVE to MASTER communication
    {
        if(NEXT.available())
        {
          c=NEXT.read();
          PC.print(c);
        }
        if ( PC.available() && PC.read() == 'q' )
        {
            NEXT.print("q");//charachter to be sent to slave for emergency stop
        }
    }
}


