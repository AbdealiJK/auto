#include<PID_v1.h>

//#define DEBUG

#define PC Serial
//#define SLAVE Serial1 //define SLAVE only if you want to control the NEXT clamp
#define NEXT Serial1    // Use this for simple communication with the NEXT clamp
#define SAMPLE_LENGTH 100

#define MY_CLAMP 'l'
char NEXT_CLAMP = 'r';


#define RIGHT 2
#define LEFT 1
#define STOP 0
#define OPEN 1
#define CLOSE 0
#define HOME_TRIP 1
#define CENTRE_TRIP 2

#define HAS_CENTRE 1
#define TRIPPED 'y'
#define TRIP_CHAR '$'

#define RISING_I 3
#define FALLING_I 2
#define CHANGE_I 1
#define LOW_I 0
#define TERMINATING_CHAR '~'
#define HOME_SPEED 50
int trip_flag = 0;



int pin1, pin2, pwm_pin, autonic_pin, piston_pin;
int pwm_lim, trip_left, trip_right;
double Input, Output, Setpoint, Kp, Ki, Kd;

float pos;
PID motor_pid; // &Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
void reset();
int run(int, int);
int stop();
void calc_pos();
void piston(int);
int goto_pos(int);
int goto_pos();
void set_params(double, double, double);
void set_params(double, double, double, int);
void go_home();
bool get_trip( int trip, int dir);
void update_trip();

void init_motor(int p1, int p2, int p, int aut, int pist, int tl, int tr);



// Motor class - pin1, pin2, pwm, autonic, piston, tripL, tripR
void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  
  PC.begin(9600);
  while (!PC) {
    ; // wait for serial port to connect.
  }

  init_motor(4, 5, 6, 7, 13, -1, 10);

  PC.println("Begun");
  set_params(50, 0, 0, 100);
  run(STOP, 255);
  if (MY_CLAMP == 'l')
  {
    NEXT_CLAMP = 'r';
  }
  else if (MY_CLAMP == 'r')
  {
    NEXT_CLAMP = 'l';
  }


}


/*ISR(INT6_vect) {
  calc_pos();
}

void setInterrupt(int i) // interrupt for INT.6 which isnt available in attachInterrupt
{
  EICRB |= ( (i % 2) << ISC60) | ((i / 2) << ISC61); // Setting the mode
  EIMSK |= (1 << INT6); // Enabling the interrupt
}*/


void loop() {

  if ( PC.available() ) {
    /*
    >>>>> UI
     rL - Motor moves to reset position
     sL - Sets the motor's initial position to current position
     vL__ - Moves motor with given pwm
     mL__ - Moves motor Mto given position (in cm)
     wl - printing stuffs
     plc - close left piston
     pxc - close both pistons
     q - Stops both motors on the spot
     z - Stops motors on spot andopens the pistons
     */
    master_ui();
  }
  update_trip();
  //  PC.println("loop : ");
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
}




