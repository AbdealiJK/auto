#define SLAVE 0

#if SLAVE

#define MY_CLAMP            'r'
#define PC                  Serial1
#define NEXT                0 && Serial
// Pins
#define MOTOR_1             5
#define MOTOR_2             4

#define HOME_TRIP           11 // -1 means no trip available
#define MIDDLE_TRIP         0 // -1 means no trip is present. 0 means trip is on other clamp
#define FIXEDCLAMP_TRIP     10  // -1 means no trip is present. 0 means trip is on other clamp
#define COMM_TRIP           0 // -1 means no trip is present. 0 means trip is on other clamp
#define HOME_TRIPPED        LOW

#else

#define MY_CLAMP            'l'
#define PC                  Serial
#define NEXT                Serial1
// Pins
#define MOTOR_1             5
#define MOTOR_2             4

#define HOME_TRIP           -1 // -1 means no trip available
#define MIDDLE_TRIP         11 // -1 means no trip is present. 0 means trip is on other clamp
#define FIXEDCLAMP_TRIP     0 // -1 means no trip is present. 0 means trip is on other clamp
#define COMM_TRIP           0 // -1 means no trip is present. 0 means trip is on other clamp
#define HOME_TRIPPED        HIGH

#endif

#define MIDDLE_TRIPPED      LOW
#define FIXEDCLAMP_TRIPPED  LOW
#define COMM_TRIPPED        LOW

#define MOTOR_PWM   6
#define AUTONIC_PIN 7
#define PISTON_PIN  A5

// Clamp names
char NEXT_CLAMP = 'r';

// Basic variables
#define HOME 2
#define MID  1
#define STOP  0

#define OPEN  1
#define CLOSE 0

#define COMM_CHAR '$'

#define PC_END '~'
#define HOME_SPEED 255


int home_trip = 0, middle_trip = 0, fixedclamp_trip = 0, comm_trip = 0,
    last_home_trip = 0, last_middle_trip = 0, last_fixedclamp_trip = 0, last_comm_trip = 0,
    avs_value = 0,
    loop_count = 0, bot_status = 0;

void reset();
int run(int, int);
void calc_pos();
void piston(int);
int goto_pos(int);
int goto_pos();
void go_home(int);
void update_trip();

void setup() {
  // Init serial
  Serial.begin(57600);
  Serial1.begin(57600);

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
  NEXT_CLAMP = (MY_CLAMP == 'l') ? 'r' : 'l';

  //setup_vcnl();
  run(STOP, 255);
  update_trips();
  //update_avs();

  #ifdef TEST
    test();
   #endif

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
  PC.print("AVS Value : \t");
  PC.println(avs_value);
  PC.println(" >> begun");
  PC.print(PC_END);

}

void loop() {

  ui();
  
    update_trips();
//    update_avs();
//    Serial.print(MY_CLAMP);
//    Serial.print("-loop -- ");
//    Serial.println(loop_count);
  
  while (PC.available())
    PC.read();

  while (NEXT.available())
    NEXT.read();
    
  loop_count++;
  delay(10);
}

