#define LEFT_SW 6
#define SW_WIDTH 8
#define LM_LENGTH 23
#define SWING_RIGHT_SPEED 255
#define SWING_LEFT_SPEED 255

int flag_sw = 0;

void swing()
{
  PC.println("Swing begun");

  flag_sw=go_home();
  if (flag_sw)
  {
    PC.println("Swing mission Failure!");
    return;
  }
  Serial.println("Home done!..... moving to respective positions");
  
  flag_sw = move_together(LEFT_SW, -(LM_LENGTH - SW_WIDTH - LEFT_SW), SWING_LEFT_SPEED, SWING_RIGHT_SPEED); //move_together(motor m2,int pos1, int pos2, int speed1, int speed2)
  if (flag_sw)
  {
    PC.println("Swing mission Failure!");
    return;
  }
  /*
    PC.println("LEFT motor moving to the left of SWING ");
    PC.print(ml.pos);
    PC.print(" -> ");
    while ( ml.goto_pos(LEFT_SW) == 0 ) {
      if ( PC.available() && PC.read() == 'q' ) {
        ml.stop();
        PC.println("Swing Mission Failed!");
        return;
        break;
      }
    }



    delay(200);
    PC.println("RIGHT motor moving to the right of SWING ");
    PC.print(mr.pos);
    PC.print(" -> ");
    while ( mr.goto_pos(-(LM_LENGTH - SW_WIDTH - LEFT_SW)) == 0 ) {
      if ( PC.available() && PC.read() == 'q' ) {
        mr.stop();
        PC.println("Swing Mission Failed!");
        return;
        break;
      }
    }*/
  PC.println("Press a key...");
  while (!PC.available());
  if (PC.read() == 'q' ) {
    PC.println("Swing mission Failure!");
    return;
  }
  ml.piston(CLOSE);
  mr.piston(CLOSE);
  PC.println("Swing Mission Sucess!");
}

/*void swing()
{

      ml.reset();
      mr.reset();
      PC.println("LEFT motor moving to the left of SWING ");
      PC.print(ml.pos);
      PC.print(" -> ");
      while ( ml.goto_pos(LEFT_SW) == 0 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          ml.stop();
          break;
        }
      }
      delay(100);
      ml.piston(CLOSE);
      delay(500);
      PC.println("RIGHT motor moving to the right of SWING ");
      PC.print(mr.pos);
      PC.print(" -> ");
      while ( mr.goto_pos(-(LM_LENGTH - SW_WIDTH - LEFT_SW)) == 0 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          mr.stop();
          break;
        }
      }
      delay(100);
      mr.piston(CLOSE);



}*/
