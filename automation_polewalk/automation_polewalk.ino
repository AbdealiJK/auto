#include<PID_v1.h>

//#define DEBUG

#define PC Serial

#define SAMPLE_LENGTH 20.0
#define PULLEY_RADIUS 1.25
#define NUMBER_OF_TURNS 10
double K_FACTOR = 2.0 * PI * PULLEY_RADIUS * 10.0 / 1024.0; // cm / analogVal
//#define TIME_FOR_AUTONICS 200
#define TRIPPED HIGH
#define RESET_SPEED_LEFT 160
#define RESET_SPEED_RIGHT 255

#define RIGHT 2
#define LEFT 1
#define STOP 0
#define OPEN 1
#define CLOSE 0

#define HEARTBEAT_TIME 500
int prev_beat_time=0;
boolean bflag=1;

class motor {

public:
  int pin1, pin2, pwm_pin, autonic_pin, piston_pin;
  int pwm_lim, trip_left, trip_right;
  int atime;// Time for autonics
  long last_pos_time;
  double Input, Output, Setpoint, Kp, Ki, Kd;
  int current_dir;
  float pos;
  PID motor_pid; // &Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
  
  motor(int, int, int, int, int, int, int,int); // pin1, pin2, pwm, autonic, trip_left, trip_right, autonics time
  void reset();
  int run(int, int);
  int stop();
  void calc_pos();
  void piston(int);
  int goto_pos(int);
  int goto_pos();
  void set_params(double, double, double);
  void set_params(double, double, double, int);
  int move_right(int, int);
  int move_right(int);
  int move_left(int, int);  
  int move_left(int);  

};

// Motor class - pin1, pin2, pwm, autonic, piston, tripL, tripR, Autonics time
motor ml(23, 22, 9, 2, 11, A12, A10, 150), mr(24, 25, 10, 3, 27, A10, A9,150);
void setup()
{
  pinMode(13,OUTPUT);
  PC.begin(115200);
  PC.println("Begun");
  
  ml.set_params(40, 0, 0, 255);
  ml.run(STOP, 255); 
 attachInterrupt(1, posr, RISING); // 1 means pin 3
  
  mr.set_params(150, 0, 0, 255);
  mr.run(STOP, 255); 
  attachInterrupt(0, posl, RISING); // 0 means pin 2
}

void posr() {
  mr.calc_pos();
}
void posl() {
  
  ml.calc_pos();
}

void loop() {

  if ( PC.available() ) {
    /*
      rL - Motor moves to reset positionrr
     sL - Sets the motor's initial position to current position
     vL__ - Moves motor with given pwm
     mL__ - Moves motor Mto given position (in cm)
     wl - printing stuffs
     plc - close left piston
     pxc - close both pistons
     q - Stops both motors on the spot
     z - Stops motors on spot andopens the pistons     
    */
    heartbeat();
    ui();

  }
  //  ml.goto_pos();
  //  mr.goto_pos();  

  /*ml.run(1, 70);
   
   while(!Serial.available());
   Serial.read();
   
   ml.run(0, 70);
   ml.reset();
   ml.set_params(20, 5, 2, 100);
   
   //r_motor.calc_pos();
   
   while(!Serial.available());
   Serial.read();
   while(1) {
   ml.goto_pos(-8);
   Serial.println(ml.cur_pos);
   delay(100);
   }*/
  heartbeat();
}




