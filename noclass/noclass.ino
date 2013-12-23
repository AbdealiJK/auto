#include<PID_v1.h>

//#define DEBUG

#define PC Serial
//#define SLAVE Serial1 //define SLAVE only if you want to control the NEXT clamp
#define NEXT Serial1    // Use this for simple communication with the NEXT clamp
#define SAMPLE_LENGTH 100

#define MY_CLAMP 'l'

#define TRIPPED LOW

#define RIGHT 2
#define LEFT 1
#define STOP 0
#define OPEN 1
#define CLOSE 0

#define RISING_I 3
#define FALLING_I 2
#define CHANGE_I 1
#define LOW_I 0

int pin1, pin2, pwm_pin, autonic_pin, piston_pin,flag;
int pwm_lim, trip_left, trip_right;
double Input, Output, Setpoint, Kp, Ki, Kd;

float pos;
PID motor_pid; // &Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

/*  void motor_init(int, int, int, int, int, int, int); // pin1, pin2, pwm, autonic, trip_left, trip_right
 void reset();
 int run(int, int);
 int stop();
 void calc_pos();
 void piston(int);
 int goto_pos(int);
 int goto_pos();
 void set_params(double, double, double);
 void set_params(double, double, double, int);
 */

// Motor class - pin1, pin2, pwm, autonic, piston, tripL, tripR
//motor m(4, 5, 6, 7, 13, -1, 10);

/*ISR(INT6_vect) {
  calc_pos();
}

void setInterrupt(int i) // interrupt for INT.6 which isnt available in attachInterrupt
{
  EICRB |= ( (i%2) << ISC60) | ((i/2) << ISC61); // Setting the mode
  EIMSK |= (1<<INT6);// Enabling the interrupt
}*/

void setup() {
  // put your setup code here, to run once:
  PC.begin(9600);
  while (!PC) {
    ; // wait for serial port to connect. 
  }

  motor_init(4, 5, 6, 7, 13, -1, -1);
  PC.println("Begun");
}

void loop() {
  // put your main code here, to run repeatedly: 
  if ( PC.available() ) {
    
    simple_ui();
  }

  Serial.println("d");
  delay(100);
}

