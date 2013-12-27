#define LEFT_SW 4
#define SW_WIDTH 8


void swing()
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



}
