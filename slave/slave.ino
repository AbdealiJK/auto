#define MASTER              Serial1

// Pins
#define MOTOR_1             4
#define MOTOR_2             5
#define MOTOR_PWM           6

#define PISTON_PIN          A5

#define HOME_TRIP           10 // -1 means no trip available
#define HOME_TRIPPED        LOW
#define IR_TRIP             7 // -1 means no trip available
#define IR_TRIPPED          LOW

// Basic variables
#define HOME 2
#define MID  1
#define STOP  0

#define OPEN  1
#define CLOSE 0

#define COMM_END '~'

// MY HASH TABLE
#define CLOSE     'p'
#define OPEN      'o'
#define MOVE      'v'
#define MOVE_MID  'i'
#define STOP      'q'
#define DATA      'd'


int home_trip = 0, ir_trip = 0;

void setup() {
  // Init serial
  MASTER.begin(57600);

  MASTER.println(F("Serial started"));

  // Pinmodes
  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(PISTON_PIN, OUTPUT);
  pinMode(HOME_TRIP, INPUT);
  run(STOP, 255);

  // Init basic variables
  home_trip = 0;

  // Display initial values :
  update_home_trip();
  MASTER.print(F("SLAVE > home-trip : \t"));
  MASTER.println(home_trip);
  update_ir_trip();
  MASTER.print(F("SLAVE > ir-trip : \t"));
  MASTER.println(ir_trip);
  MASTER.print(COMM_END);
}

void loop() {
  slave_commands();

  while ( MASTER.available() )
    MASTER.read();

  MASTER.println(F("I be slave"));
  delay(20);

}

