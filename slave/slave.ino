#define MASTER              Serial

// Slave Pin chars
#define MOTOR_1             4
#define MOTOR_2             5
#define MOTOR_PWM           6
#define PISTON_PIN          10
#define HOME_TRIP           A4 // -1 means no trip available
#define IR_TRIP             12
#define HOME_TRIPPED        LOW
#define IR_TRIPPED          LOW

// Basic variables
#define HOME 2
#define MID  1
#define STOP  0

// MY HASH TABLE
#define COMM_END  '~'
#define CLOSE     'p'
#define OPEN      'o'
#define MOVE      'v'
#define MOVE_MID  'i'
#define STOP      'q'
#define DATA      'd'


int home_trip = 0, ir_trip = 0;

void setup() {
  // Init serial
  Serial.begin(57600);
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

//  Serial.println(F("I be slave"));
  delay(20);

}

