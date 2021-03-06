#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

#define SLAVE     0

#if SLAVE

#define MY_CLAMP            'r'
#define PC                  Serial1
#define NEXT                0 && Serial
// Pins
#define MOTOR_1             4
#define MOTOR_2             5

#define HOME_TRIP           -1 // -1 means no trip available
#define HOME_TRIPPED        LOW

#else

#define MY_CLAMP            'l'
#define PC                  Serial
#define NEXT                mySerial
// Pins
#define MOTOR_1             4
#define MOTOR_2             5

#define HOME_TRIP           -1 // -1 means no trip available
#define HOME_TRIPPED        LOW

#endif

#define MIDDLE_TRIP         A4
#define FIXEDCLAMP_TRIP     -1 // WHAT EES IT
#define COMM_TRIP           SCK
#define COMM_IR_TRIP        A0
#define IR_TRIP             12
#define MIDDLE_TRIPPED      LOW
#define FIXEDCLAMP_TRIPPED  LOW
#define COMM_TRIPPED        LOW
#define COMM_IR_TRIPPED     LOW
#define IR_TRIPPED          LOW

#define MOTOR_PWM   6
#define PISTON_PIN  A5

/*#define QUIT_OR_CONTINUE \
  PC.println("Waiting for 'c' ... "); \
  while ( 1 ) { \
    if ( PC.available() && PC.peek() == 'q' ) return; \
    if ( PC.available() && PC.peek() == 'c' ) { PC.read(); break; } \
  }*/
  
  #define QUIT_OR_CONTINUE proceed_comm()

// Clamp names
char NEXT_CLAMP = 'r';

// Basic variables
#define HOME 2
#define MID  1
#define STOP  0

#define OPEN  1
#define CLOSE 0

#define PC_BEGIN '$'
#define PC_END '~'

#define HOME_SPEED 255


int home_trip = 0, middle_trip = 0, fixedclamp_trip = 0, comm_trip = 0, comm_ir_trip = 0, ir_trip = 0,
    loop_count = 0, bot_status = 0;
//TEMPORARY
int f=1;

void reset();
int run(int, int);
void piston(int);
void go_home(int);
void update_trip();

void setup() {
  // Init serial
  Serial.begin(57600);
//  Serial1.begin(57600);
  mySerial.begin(9600);
  mySerial.println("Hello, world?");

  //  while (!SLAVE && !PC); // wait for serial port to connect.

  PC.println("Serial started");

  // Pinmodes
  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(PISTON_PIN, OUTPUT);
  pinMode(HOME_TRIP, INPUT);
  if ( !SLAVE ) {
    pinMode(MIDDLE_TRIP, INPUT);
    pinMode(FIXEDCLAMP_TRIP, INPUT);
    pinMode(COMM_TRIP, INPUT);
    pinMode(COMM_IR_TRIP, INPUT);
  }
  run(STOP, 255);

  // Init basic variables
  PC.println("Setting up basics ...");
  NEXT_CLAMP = (MY_CLAMP == 'l') ? 'r' : 'l';

  middle_trip = 0;
  fixedclamp_trip = 0;
  comm_trip = 0;

  run(STOP, 255);;
  update_home_trip();;
  update_middle_trip();
  update_fixedclamp_trip();

  // Display initial values :
  PC.print("My clamp : \t");
  PC.println(MY_CLAMP);
  PC.print("Next clamp : \t");
  PC.println(NEXT_CLAMP);
  PC.print("Trips - home : \t");
  PC.println(home_trip);
  PC.print("Trips - mid : \t");
  PC.println(middle_trip);
  PC.print("Trips - fixedclamp : \t");
  PC.println(fixedclamp_trip);
  PC.print("Trips - comm : \t");
  PC.println(comm_trip);
  PC.println(" >> begun");
  PC.print(PC_END);

}

void loop() {
  ui();
  // update_trips();

  while ( PC.available() )
    PC.read();

  while (NEXT.available())
    NEXT.read();

  Serial.print(MY_CLAMP);
  update_comm_trip();
  Serial.print( comm_trip );
  Serial.println("-loop");
  delay(100);

}
