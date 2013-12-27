#define LEFT_SS 5
#define SS_WIDTH 7
#define LM_LENGTH 23
int flag_ss=0;

void seesaw()
{
      go_home();
      
      PC.println("LEFT motor moving to the left of SEESAW ");
      PC.print(ml.pos);
      PC.print(" -> ");
      while ( ml.goto_pos(LEFT_SS) == 0 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          ml.stop();
          break;
        }
      }
      ml.piston(CLOSE);
      delay(500);
      PC.println("RIGHT motor moving to the right of SEESAW ");
      PC.print(mr.pos);
      PC.print(" -> ");
      while ( mr.goto_pos(-(LM_LENGTH - SS_WIDTH - LEFT_SS)) == 0 ) {
        if ( PC.available() && PC.read() == 'q' ) {
          mr.stop();
          break;
        }
      }
      mr.piston(CLOSE);
}
