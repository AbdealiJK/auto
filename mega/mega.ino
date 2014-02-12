#define PC                  Serial

#define L_MOTOR_1           4
#define L_MOTOR_2           6
#define L_MOTOR_PWM         5
#define L_PISTON_PIN        27
#define L_HOME_TRIP         2 //
#define L_HOME_TRIPPED      LOW

#define R_MOTOR_1           9
#define R_MOTOR_2           7
#define R_MOTOR_PWM         8
#define R_PISTON_PIN        31
#define R_HOME_TRIP         20 //
#define R_HOME_TRIPPED      LOW

#define R_HOME_TRIP_INT     3
#define L_HOME_TRIP_INT     0
#define MID_TRIP_INT        1
#define L_PP_PIN            29
#define R_PP_PIN            33

#define MID_TRIP            3 //
#define COMM_TRIP           21 //
#define LADDER_IR           -1 
#define COMM_IR             -1
#define MID_IR              18 //
#define MID_TRIPPED         LOW
#define COMM_TRIPPED        HIGH
#define LADDER_IR_FOUND     LOW
#define COMM_IR_FOUND       LOW
#define MID_IR_FOUND        LOW

#define STOP        0
#define HOME        1
#define MID         2

#define LEFT        'l' // these also correspond to reference from serial
#define RIGHT       'r'
#define QUIT        'q'
#define BOTH        'b'

#define CLOSE       1
#define OPEN        0

#define EXTEND      1
#define SHRINK      0
#define H_VEL 255


int l_running = 0, r_running = 0;

#define QUIT_OR_CONTINUE delay(200);



bool l_home_trip = 0, r_home_trip = 0, mid_trip = 0, comm_trip = 0,
     ladder_ir = 0, comm_ir = 0, mid_ir = 0;

void setup() {
  PC.begin(57600);

  pinMode(L_MOTOR_1, OUTPUT);
  pinMode(L_MOTOR_2, OUTPUT);
  pinMode(L_MOTOR_PWM, OUTPUT);
  pinMode(L_PISTON_PIN, OUTPUT);
  pinMode(R_MOTOR_1, OUTPUT);
  pinMode(R_MOTOR_2, OUTPUT);
  pinMode(R_MOTOR_PWM, OUTPUT);
  pinMode(R_PISTON_PIN, OUTPUT);

  pinMode(L_PP_PIN, OUTPUT);
  pinMode(R_PP_PIN, OUTPUT);
  
  //  pinMode(L_HOME_TRIP, INPUT);
  //  pinMode(R_HOME_TRIP, INPUT);
  //  pinMode(MID_TRIP, INPUT);
  pinMode(LADDER_IR, INPUT);
  pinMode(COMM_TRIP, INPUT);
  pinMode(COMM_IR, INPUT);
  pinMode(MID_IR, INPUT);

  attachInterrupt(L_HOME_TRIP_INT, l_home_trip_isr, HIGH);
  attachInterrupt(R_HOME_TRIP_INT, r_home_trip_isr, HIGH);
  attachInterrupt(MID_TRIP_INT, mid_trip_isr, HIGH);
}

void loop() {
  ui();

  while (PC.available())
    PC.read();

  /*
    Serial.print("\tL_HOME_TRIP : ");
    Serial.print(digitalRead(L_HOME_TRIP));
    Serial.print("\tR_HOME_TRIP : ");
    Serial.print(digitalRead(R_HOME_TRIP));
    Serial.print("\tCOMM_TRIP : ");
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
  Serial.println(F("\tloop"));

  delay(100);


}
