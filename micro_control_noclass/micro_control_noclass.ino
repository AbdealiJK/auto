#define SLAVE 0

#if SLAVE

// Clamp names
#define MY_CLAMP 'r'
// Comm ports
#define PC Serial1
#define NEXT 0 && Serial
// Pins
#define MOTOR_1     5
#define MOTOR_2     4
#define PISTON_PIN  13 // 13 and A5
#define HOME_TRIP   10 // -1 means no trip available
#define MIDDLE_TRIP 11 // Pin D10 : -1 means no trip is present. 0 means trip is on other clamp
#define MIDDLE_TRIPPED 0
#define HOME_TRIPPED 1

#else

// Clamp names
#define MY_CLAMP 'l'
// Comm ports
#define PC Serial
#define NEXT Serial1
// Pins
#define MOTOR_1     4
#define MOTOR_2     5
#define PISTON_PIN  A5 // 13 and A5
#define HOME_TRIP   10 // -1 means no trip available
#define MIDDLE_TRIP 0 // Pin D10 : -1 means no trip is present. 0 means trip is on other clamp
#define MIDDLE_TRIPPED 1
#define HOME_TRIPPED 1

#endif


#define MOTOR_PWM   6
#define AUTONIC_PIN 7

// Clamp names
char NEXT_CLAMP = 'r';

// Analog flicker correction length
#define SAMPLE_LENGTH 100
// Basic variables
#define HOME 2
#define MID  1
#define STOP  0

#define OPEN  1
#define CLOSE 0

#define TRIP_CHAR '$'

#define PC_END '~'
#define HOME_SPEED 255

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
  // Init serial
  Serial.begin(9600);
  Serial1.begin(9600);
  while (!SLAVE && !PC); // wait for serial port to connect.
  
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
  NEXT_CLAMP = (MY_CLAMP == 'l') ? 'r' : 'l';

  // Display initial values :
  PC.print("My clamp : \t");
  PC.println(MY_CLAMP);
  PC.print("Next clamp : \t");
  PC.println(NEXT_CLAMP);
  PC.print("My clamp : \t");
  PC.println(MY_CLAMP);
  PC.print(PC_END);
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
//  if ( MIDDLE_TRIP ) Serial.print(digitalRead(MIDDLE_TRIP));
  Serial.print(MY_CLAMP);
  Serial.println("-loop ");
  delay(100);
}






