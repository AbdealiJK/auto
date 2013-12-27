

#define POLE_LEFT_KP 40
#define POLE_LEFT_KI 0
#define POLE_LEFT_KD 0
#define POLE_LEFT_SPEED 255
#define POLE_RIGHT_KP 150
#define POLE_RIGHT_KI 0
#define POLE_RIGHT_KD 0
#define POLE_RIGHT_SPEED 255

#define PW_PISTON_DELAY 1000

#define POLE_LEFT_1 2
#define POLE_RIGHT_1 -19
#define POLE_LEFT_2  18
//#define POLE_RIGHT_2  16
int flag_pw=0;



void polewalk()
{
  PC.println("Polewalk begun");
  polewalk_init();
  go_home();
  delay(100);
  PC.println("Left motor going to its initial position...");
  flag_pw = left_motor_to(POLE_LEFT_1);
  if (flag_pw)
  {
    PC.println("Polewalk mission Failure!");
    return;
  }
  //  PC.println("Press a key...");
  //  while(!PC.available());
  //  if (PC.read() == 'q' ){return;}

  PC.println("Right motor going to Disc 2...");
  flag_pw = right_motor_to(POLE_RIGHT_1);
  if (flag_pw)
  {
    PC.println("Polewalk mission Failure!");
    return;
  }
    PC.println("Press a key...");
    while(!PC.available());
    if (PC.read() == 'q' ){return;}    
  mr.piston(CLOSE);
  PC.println("Disc 2 clamped ...");
  delay(PW_PISTON_DELAY);
  PC.println("Moving the LM guide to the left...");
/*  flag_pw = right_motor_to(POLE_RIGHT_2);*/
  move_right_clamp(RIGHT);

  if (flag_pw)
  {
    PC.println("Polewalk mission Failure!");
    return;
  }
      PC.println("Press a key...");
    while(!PC.available());
    if (PC.read() == 'q' ){return;}    

  ml.piston(CLOSE);
  delay(PW_PISTON_DELAY);
  mr.piston(OPEN);
  PC.println("Disc 2 unclamped and Disc 3 clamped...");
  PC.println("Moving the LM guide to the left...");
  flag_pw = left_motor_to(POLE_LEFT_2);
  if (flag_pw)
  {
    PC.println("Polewalk mission Failure!");
    return;
  }
  PC.println("PP activated & Pole walk complete...");
  flag_pw = 1;
}

void polewalk_init()
{
  mr.set_params(POLE_RIGHT_KP, POLE_RIGHT_KI, POLE_RIGHT_KD, POLE_RIGHT_SPEED);
  ml.set_params(POLE_LEFT_KP, POLE_LEFT_KI, POLE_LEFT_KD, POLE_LEFT_SPEED );
  flag_pw=0;

}
int left_motor_to(int tpos)
{
  while ( ml.goto_pos(tpos) == 0 ) {
    if ( PC.available() && PC.read() == 'q' ) {
      ml.stop();
      return 1;
    }
  }
  return 0;
}
int right_motor_to(int tpos)
{
  while ( mr.goto_pos(tpos) == 0 ) {
    if ( PC.available() && PC.read() == 'q' ) {
      mr.stop();
      return 1;
    }
  }
  return 0;
}
void go_home()
{
  while ( ml.run(LEFT, RESET_SPEED_LEFT) == 1 ) {
    if ( PC.available() && PC.read() == 'q' ) {
      ml.run(STOP, 255);
      break;
    }
  }
  while ( mr.run(RIGHT, RESET_SPEED_RIGHT) == 1 ) {
    if ( PC.available() && PC.read() == 'q' ) {
      mr.run(STOP, 255);
      break;
    }
  }
  mr.reset();
  ml.reset();

}

/*

void polewalk()
{
  go_home();
  while (!flag_pw)
  {
    Serial.println("Going towards Left Clamp ..... ");
    move_right_clamp(LEFT);
    if (flag_pw == -1)
       break;
     Serial.print("Went to Left Clamp ....  Pos = ");
    Serial.println(mr.pos);
    mr.piston(CLOSE);
    Serial.println("Moving the LM guide to the left... ");
    move_right_clamp(RIGHT);
    if (flag_pw == -1)
       break;
     Serial.println("LM Guide fully towards the left...");
    ml.piston(CLOSE);
    delay(500);
    mr.piston(OPEN);
    Serial.println("Closed the left clamp and Opened the right clamp...");
    Serial.println("Moving the LM guide towards the left.");
    move_left_clamp(RIGHT);
    if (flag_pw == -1)
       break;
    Serial.println("LM Guide fully towards the left...");
    Serial.println("PP activated & Pole walk complete...");
    flag_pw=1;

  }
      if (flag_pw == -1)
        PC.println("Polewalk mission failure!");



}*/
void move_right_clamp(int dir)
{

  while ( mr.run(dir, POLE_RIGHT_SPEED) == 1 ) {
    if ( PC.available() && PC.read() == 'q' ) {
      mr.run(STOP, 255);
      ml.run(STOP, 255);
      break;
      flag_pw = 1;
    }
  }
}
/*void move_left_clamp(int dir)
{
  while ( ml.run(RIGHT, POLE_SPEED_LEFT) == 1 ) {
    if ( PC.available() && PC.read() == 'q' ) {
      ml.run(STOP, 255);
      mr.run(STOP, 255);
      break;
      flag_pw = -1;
    }
  }
}*/
