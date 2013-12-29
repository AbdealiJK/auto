#define LADDER_LEFT_KP 40
#define LADDER_LEFT_KI 0
#define LADDER_LEFT_KD 0
#define LADDER_LEFT_SPEED 255
#define LADDER_RIGHT_KP 150
#define LADDER_RIGHT_KI 0
#define LADDER_RIGHT_KD 0
#define LADDER_RIGHT_SPEED 255
#define LAD_1  16
#define LAD_2  0
#define LAD_3  0
#define LAD_4  0
#define LAD_PISTON_DELAY 500
// 21 is the pos of l when it hits right clamp
int flag_lad = 0;

void ladder()
{
  PC.println("Ladder begun");
  ladder_init();
  go_home();
  delay(100);
  PC.println("Left motor going to its 1st position...");
  flag_lad = ml.move_right(LADDER_LEFT_SPEED, LAD_1); // go to first rung
  if (flag_lad)
  {
    PC.println("Polewalk mission Failure!");
    return;
  }
  while (!PC.available());
  if (PC.read() == 'q' ) {
    PC.println("Polewalk mission Failure!");
    return;
  }

  ml.piston(CLOSE);               //  clamp first rung
  delay(LAD_PISTON_DELAY);
  flag_lad = ml.move_left(LADDER_LEFT_SPEED, LAD_2); // LM guide moves up & fixed clamp crosses rung
  if (flag_lad)
  {
    PC.println("Polewalk mission Failure!");
    return;
  }
  delay(100);
  flag_lad = ml.move_right(LADDER_LEFT_SPEED, LAD_3); // fixed clamp comes down to the rung
  if (flag_lad)
  {
    PC.println("Polewalk mission Failure!");
    return;
  }
  while (!PC.available());
  if (PC.read() == 'q' ) {
    PC.println("Polewalk mission Failure!");
    return;
  }


  for (int i = 0; i < 3; i++)
  {
    ml.piston(OPEN);                       // moving clamp opens
    flag_lad = ml.move_right(LADDER_LEFT_SPEED); //       moving clamp reached the right motor and trips. it is now at pos =21
    if (flag_lad)
    {
      PC.println("Polewalk mission Failure!");
      return;
    }
    while (!PC.available());
    if (PC.read() == 'q' ) {
      PC.println("Polewalk mission Failure!");
      return;
    }

    ml.piston(CLOSE);                //It now clamps the rung
    ml.reset();                      // Its position is set to zero
    delay(LAD_PISTON_DELAY);
    flag_lad = ml.move_left(LADDER_LEFT_SPEED, LAD_3); // LM guide moves up & fixed clamp crosses rung
    if (flag_lad)
    {
      PC.println("Polewalk mission Failure!");
      return;
    }
    delay(100);
    flag_lad = ml.move_right(LADDER_LEFT_SPEED, LAD_4); // fixed clamp comes down to the rung
    if (flag_lad)
    {
      PC.println("Polewalk mission Failure!");
      return;
    }
    while (!PC.available());
    if (PC.read() == 'q' ) {
      PC.println("Polewalk mission Failure!");
      return;
    }




  }



}

void ladder_init()
{
  mr.set_params(LADDER_RIGHT_KP, LADDER_RIGHT_KI, LADDER_RIGHT_KD, LADDER_RIGHT_SPEED);
  ml.set_params(LADDER_LEFT_KP, LADDER_LEFT_KI, LADDER_LEFT_KD, LADDER_LEFT_SPEED );
  flag_lad = 0;
  ml.piston(OPEN);
  mr.piston(OPEN);

}
