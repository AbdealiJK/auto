#define LADDER_LEFT_KP 40
#define LADDER_LEFT_KI 0
#define LADDER_LEFT_KD 0
#define LADDER_LEFT_SPEED 255
#define LADDER_RIGHT_KP 150
#define LADDER_RIGHT_KI 0
#define LADDER_RIGHT_KD 0
#define LADDER_RIGHT_SPEED 255
#define LAD_1  0
#define LAD_2  0
#define LAD_3  0
#define LAD_4  0
#define LAD_PISTON_DELAY 500

int flag_lad=0;
/*
void ladder()
{
    PC.println("Ladder begun");
    ladder_init();
    go_home();
    delay(100);
    PC.println("Left motor going to its 1st position...");
    flag_lad = left_motor_to(LAD_1); // go to first rung
    ml.piston(CLOSE);               //  clamp first rung
    delay(LAD_PISTON_DELAY);
    flag_lad = left_motor_to(LAD_2);// move LM guide so that fixed clamp crosses second rung
    flag_lad = left_motor_to(LAD_3);// pull back so that second clamp gets fixed.    
    ml.piston(OPEN);                // bot is now supported on the second rung using fixed clamp
    flag_lad = left_motor_to(LAD_3);    
    
    
}
*/
void ladder_init()
{
  mr.set_params(LADDER_RIGHT_KP, LADDER_RIGHT_KI, LADDER_RIGHT_KD, LADDER_RIGHT_SPEED);
  ml.set_params(LADDER_LEFT_KP, LADDER_LEFT_KI, LADDER_LEFT_KD, LADDER_LEFT_SPEED );
  flag_lad=0;

}
