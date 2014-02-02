#define PC                  Serial
#define SLAVE               Serial1

// Pins
#define MOTOR_1             4
#define MOTOR_2             5
#define MOTOR_PWM           6

#define PISTON_PIN          A5

#define HOME_TRIP           10 // -1 means no trip available
#define HOME_TRIPPED        LOW

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

#define QUIT_OR_CONTINUE \
  PC.println("Waiting for 'c' ... "); \
  while ( 1 ) { \
    if ( PC.available() && PC.peek() == 'q' ) return; \
    if ( PC.available() && PC.peek() == 'c' ) { PC.read(); break; } \
  }

// Clamp names
char NEXT_CLAMP = 'r';

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

int home_trip = 0, middle_trip = 0, fixedclamp_trip = 0,
    comm_trip = 0, comm_ir_trip = 0, ir_trip = 0;

void reset();
int run(int, int);
void piston(int);
void go_home(int);
void update_trip();

void setup() {
  // Init serial
  Serial.begin(57600);
  Serial1.begin(57600);

  //  while (!SLAVE && !PC); // wait for serial port to connect.

  PC.println("Serial started");

  // Pinmodes
  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(PISTON_PIN, OUTPUT);
  pinMode(HOME_TRIP, INPUT);

  pinMode(MIDDLE_TRIP, INPUT);
  pinMode(FIXEDCLAMP_TRIP, INPUT);
  pinMode(COMM_TRIP, INPUT);
  pinMode(COMM_IR_TRIP, INPUT);
  digitalWrite(COMM_TRIP, HIGH);

  run(STOP, 255);

  // Init basic variables
  PC.println(F("Setting up basics ..."));

  home_trip = middle_trip = fixedclamp_trip = comm_trip = ir_trip = 0;

  run(STOP, 255);
  update_home_trip();
  update_middle_trip();
  update_fixedclamp_trip();
  update_comm_trip();
  update_ir_trip();

  // Display initial values :
  PC.print("Trips - home : \t");
  PC.println(home_trip);
  PC.print("Trips - mid : \t");
  PC.println(middle_trip);
  PC.print("Trips - fixedclamp : \t");
  PC.println(fixedclamp_trip);
  PC.print("Trips - comm : \t");
  PC.println(comm_trip);
  PC.print("Trips - ir : \t");
  PC.println(ir_trip);
  PC.print(COMM_END);

}

void loop() {

  ui();

  while (PC.available())
    PC.read();

  while (SLAVE.available())
    SLAVE.read();

  Serial.print(  digitalRead(COMM_IR_TRIP) );
  Serial.print(  digitalRead(COMM_TRIP) );
  Serial.println("I be master");
  delay(100);

}


