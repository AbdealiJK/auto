#define MASTER              Serial

// Slave Pin chars
char MOTOR_1             = 4,
     MOTOR_2             = 5,
     MOTOR_PWM           = 6,
     PISTON_PIN          = 10,
     HOME_TRIP           = A4, // -1 means no trip available
     MID_IR              = 12,
     HOME_TRIPPED        = LOW,
     MID_IR_FOUND        = LOW;


// Basic variables
#define HOME  2
#define MID   1
#define STOP  0

// MY HASH TABLE
#define COMM_END  '~'
#define CLOSE     'p'
#define OPEN      'o'
#define MOVE      'v'
#define MOVE_MID  'i'
#define STOP      'q'
#define DATA      'd'
#define PINS      '='


int home_trip = 0, mid_ir = 0;

void setup() {
  // Init serial
  Serial.begin(57600);
  MASTER.begin(57600);

  MASTER.println(F("Serial started"));

  // Pinmodes
/*  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(PISTON_PIN, OUTPUT);
  pinMode(HOME_TRIP, INPUT);
  pinMode(MID_IR, INPUT);
*/
  run(STOP, 255);

  // Init basic variables
  home_trip = mid_ir =  0;

  // Display initial values :
  update_home_trip();
  MASTER.print(F("SLAVE > home-trip : \t"));
  MASTER.println(home_trip);
  update_mid_ir();
  MASTER.print(F("SLAVE > mid-ir : \t"));
  MASTER.println(mid_ir);
  MASTER.print(COMM_END);
}

void loop() {
  slave_commands();

  while ( MASTER.available() )
    MASTER.read();

  //  Serial.println(F("I be slave"));
  delay(20);

}

