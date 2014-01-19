//#define DEBUG

// Clamp names
#define MY_CLAMP 'l'
char NEXT_CLAMP = 'r';
// Pins
#define MOTOR_1     4
#define MOTOR_2     5
#define MOTOR_PWM   6
#define AUTONIC_PIN 7
#define PISTON_PIN  13 // Aand 5
#define HOME_TRIP   11 // -1 means no trip available
#define MIDDLE_TRIP 10 // -1 means no trip is present. 0 means trip is on other clamp

// Comm ports
#define PC Serial
#define NEXT Serial1    // Use this for simple communication with the NEXT clamp
// Analog flicker correction length
#define SAMPLE_LENGTH 100
// Basic variables
#define HOME 2
#define MID  1
#define STOP  0

#define OPEN  1
#define CLOSE 0

#define TRIPPED 0
#define TRIP_CHAR '$'

#define PC_END '~'
#define HOME_SPEED 50

int home_trip = 0, middle_trip = 0, 
  max_pwm = 150, acc_pwm = 50,
  pos = 0, target_pos = 0;

void reset();
int run(int, int);
void calc_pos();
void piston(int);
int goto_pos(int);
int goto_pos();
void go_home();
void update_trip();

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  // Init serial
  PC.begin(9600);
  while (!PC); // wait for serial port to connect.
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  PC.println("Serial started");
  
  // Pinmodes
  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(AUTONIC_PIN, INPUT);
  pinMode(PISTON_PIN, OUTPUT);
  pinMode(HOME_TRIP, INPUT);
  pinMode(MIDDLE_TRIP, INPUT);
  run(STOP, 255);

  // Init basic variables
  PC.println("Setting up basics ...");
  acc_pwm = 50;
  max_pwm = 100;
  
  run(STOP, 255);
  NEXT_CLAMP = (MY_CLAMP == 'l')? 'r' : 'l';
  
  // Display initial values :
  PC.print("My clamp : \t");
  PC.println(MY_CLAMP);
  PC.print("Next clamp : \t");
  PC.println(NEXT_CLAMP);
  PC.print("My clamp : \t");
  PC.println(MY_CLAMP);
}

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
  
  /*delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);*/
  
  delay(10);
}






