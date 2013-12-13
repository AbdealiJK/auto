#include<PID_v1.h>

#define PC Serial

#define SAMPLE_ANALOG 100.0
#define PULLEY_RADIUS 1
#define NUMBER_OF_TURNS 10
double K_FACTOR = 2.0 * PI * PULLEY_RADIUS * 10.0 / 1024.0; // cm / analogVal

#define RIGHT 1
#define LEFT 2
#define STOP 0
//#define DEBUG

class motor {
private:
  long long int time_prev;
  float prev_pos, prev_turns;
  int pin1, pin2, pwm_pin, pot_pin;
  int pwm_lim, trip_left, trip_right;
  double Input, Output, Setpoint, Kp, Ki, Kd;

public:
  float init_pos, init_turns;
  float cur_pos, cur_turns;
  float vel, vel_turns;
  float target_pos;
  PID motor_pid; // &Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


  void reset();
  int run(int, int);
  void calc_vel();
  void calc_pos();
  void set_trips(int, int);
  int goto_pos(float);
  int goto_pos();
  void set_params(double, double, double);
  void set_params(double, double, double, int);
  motor(int, int, int, int); // pin1, pin2, pwm, pot
};

// Motor class - pin1, pin2, pwm, pot, tripL, tripR
motor ml(28, 29, 12, A0),
mr(28, 29, 12, A0);
void setup()
{
  PC.begin(115200);
  PC.println("Begun");

}

void loop() {

  if ( PC.available() ) {
    /*
      rL - Motor moves to reset position
     sL - Sets the motor's initial position to current position
     vL__ - Moves motor with given pwm
     mL__ - Moves motor to given position (in cm)
     q - Stops both motors on the spot
     */
    ui();

  }
  ml.goto_pos();
  mr.goto_pos();  

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


