#include<PID_v1.h>

//#define DEBUG

#define PC Serial

#define SAMPLE_LENGTH 100.0
#define PULLEY_RADIUS 1.25
#define NUMBER_OF_TURNS 10
double K_FACTOR = 2.0 * PI * PULLEY_RADIUS * 10.0 / 1024.0; // cm / analogVal
#define TIME_FOR_AUTONICS 100
#define TRIPPED LOW

#define RIGHT 2
#define LEFT 1
#define STOP 0
#define OPEN 1
#define CLOSE 0


class motor {

public:
  int pin1, pin2, pwm_pin, autonic_pin, piston_pin;
  int pwm_lim, trip_left, trip_right;
  long last_pos_time;
  double Input, Output, Setpoint, Kp, Ki, Kd;
  int current_dir;
  float pos;
  PID motor_pid; // &Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
  
  motor(int, int, int, int, int, int, int); // pin1, pin2, pwm, autonic, trip_left, trip_right
  void reset();
  int run(int, int);
  int stop();
  void calc_pos();
  void piston(int);
  int goto_pos(int);
  int goto_pos();
  void set_params(double, double, double);
  void set_params(double, double, double, int);
};

// Motor class - pin1, pin2, pwm, autonic, piston, tripL, tripR
motor ml(22, 23, 9, 3, 27, A2, A0), mr(24, 25, 10, 2, 11, A0, A1);
void setup()
{
  PC.begin(115200);
  PC.println("Begun");
  
  ml.set_params(40, 0, 0, 100);
  ml.run(STOP, 255); 
  attachInterrupt(1, posl, RISING); // 1 means pin 3
  
  mr.set_params(150, 0, 0, 200);
  mr.run(STOP, 255); 
  attachInterrupt(0, posr, RISING); // 0 means pin 2
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

}




