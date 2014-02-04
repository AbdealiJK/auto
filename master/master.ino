#define PC                  Serial
#define SLAVE               Serial1

// Pins
#define MOTOR_1             4
#define MOTOR_2             5
#define MOTOR_PWM           6

#define PISTON_PIN          A5

#define HOME_TRIP           10 // -1 means no trip available
#define MIDDLE_TRIP         A4
#define FIXEDCLAMP_TRIP     -1
#define COMM_TRIP           SCK
#define COMM_IR_TRIP        A0
#define IR_TRIP             12
#define HOME_TRIPPED        LOW
#define MIDDLE_TRIPPED      LOW
#define FIXEDCLAMP_TRIPPED  LOW
#define COMM_TRIPPED        LOW
#define COMM_IR_TRIPPED     LOW
#define IR_TRIPPED          LOW

#define QUIT_OR_CONTINUE if(quit_or_continue()) return;
  
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

bool home_trip = 0, middle_trip = 0, fixedclamp_trip = 0,
    comm_trip = 0, comm_ir_trip = 0, ir_trip = 0;

void setup() {
  // Init serial
  Serial.begin(57600);
  Serial1.begin(57600);

  while (!PC); // wait for serial port to connect.

  PC.println(F("Serial started"));

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
  pinMode(IR_TRIP, INPUT);

  run(STOP, 255);

  // Init basic variables
  PC.println(F("Setting up basics ..."));

  home_trip = middle_trip = fixedclamp_trip = comm_trip = comm_ir_trip = ir_trip = 0;

  run(STOP, 255);
  update_trip(HOME_TRIP);
  update_trip(MIDDLE_TRIP);
  update_trip(FIXEDCLAMP_TRIP);
  update_trip(COMM_TRIP);
  update_trip(COMM_IR_TRIP);
  update_trip(IR_TRIP);

  // Display initial values :
  PC.print(F("Trips - home:"));
  PC.println(home_trip);
  PC.print(F(" mid:"));
  PC.println(middle_trip);
  PC.print(F(" fixedclamp:"));
  PC.println(fixedclamp_trip);
  PC.print(F(" comm:"));
  PC.println(comm_trip);
  PC.print(F(" ir:"));
  PC.println(ir_trip);
}

void loop() {
  ui();

  while (PC.available())
    PC.read();

  while (SLAVE.available())
    SLAVE.read();

  Serial.println(F("master"));
  delay(100);

}
