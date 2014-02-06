#define PC                  Serial
#define SLAVE               Serial1

// Pins
#define MOTOR_1             4
#define MOTOR_2             5
#define MOTOR_PWM           6

#define PISTON_PIN          11

#define HOME_TRIP           10 // -1 means no trip available
#define MID_TRIP            A3
#define COMM_TRIP           -1
#define LADDER_IR           -1
#define COMM_IR             -1
#define MID_IR              12
#define HOME_TRIPPED        LOW
#define MID_TRIPPED         LOW
#define COMM_TRIPPED        LOW
#define LADDER_IR_FOUND     LOW
#define COMM_IR_FOUND       LOW
#define MID_IR_FOUND        LOW

#define QUIT_OR_CONTINUE if(quit_or_continue()) return;
  
// Basic variables
#define HOME 2
#define MID  1
#define STOP  0

// MY HASH TABLE
#define COMM_END    '~'
#define CLOSE       'p'
#define OPEN        'o'
#define MOVE        'v'
#define MOVE_MID    'i'
#define MOVE_LADDER 'f'
#define STOP        'q'
#define DATA        'd'

bool home_trip = 0, mid_trip = 0, comm_trip = 0,
      ladder_ir = 0, comm_ir = 0, mid_ir = 0;

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
  pinMode(MID_TRIP, INPUT);
  pinMode(LADDER_IR, INPUT);
  pinMode(COMM_TRIP, INPUT);
  pinMode(COMM_IR, INPUT);
  pinMode(MID_IR, INPUT);

  run(STOP, 255);

  // Init basic variables
  PC.println(F("Setting up basics ..."));

  home_trip = mid_trip = comm_trip = ladder_ir = comm_ir = mid_ir = 0;

  run(STOP, 255);
  update(HOME_TRIP);
  update(MID_TRIP);
  update(COMM_TRIP);
  update(LADDER_IR);
  update(COMM_IR);
  update(MID_IR);

  // Display initial values :
  PC.print(F("Trips - home:"));
  PC.println(home_trip);
  PC.print(F(" mid:"));
  PC.println(mid_trip);
  PC.print(F(" ladder:"));
  PC.println(ladder_ir);
  PC.print(F(" comm:"));
  PC.println(comm_trip);
  PC.print(F(" mid-ir:"));  
  PC.println(mid_ir);
}

void loop() {
  ui();

  while (PC.available())
    PC.read();

  while (SLAVE.available())
    SLAVE.read();

/*  
  Serial.print("\tHOME_TRIP : ");
  Serial.print(digitalRead(HOME_TRIP));
  Serial.print("\tMCOMM_TRIP : ");
  Serial.print(digitalRead(COMM_TRIP));
  Serial.print("\tMID_TRIP : ");
  Serial.print(digitalRead(MID_TRIP));
  Serial.print("\tLADDER_IR : ");
  Serial.print(digitalRead(LADDER_IR));
  Serial.print("\tCOMM_IR : ");
  Serial.print(digitalRead(COMM_IR));
  Serial.print("\tMID_IR : ");
  Serial.print(digitalRead(MID_IR));
*/
  Serial.println(F("\tmaster"));
  delay(100);

}
