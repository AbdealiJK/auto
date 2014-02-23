#include <PS2X_lib.h>

#define PC                  Serial

#define MIRROR              0
#define SEESAW_TIME         1200
#define SWING_TIME          400
#define LADDER_TIME         200

#define SEESAW_PWM          100
#define SWING_PWM           200
#define POLEWALK_PWM        100
#define LADDER_PWM          100

//#define QUIT_OR_CONTINUE if(quit_or_continue()) return
#define QUIT_OR_CONTINUE delay(200);

#define L_MOTOR             8, A1, 9
#define L_PISTON_PIN        46
#define L_HOME_TRIP         A4
#define L_HOME_TRIPPED      LOW

#define R_MOTOR             12, 7, 10
#define R_PISTON_PIN        28
#define R_HOME_TRIP         3
#define R_HOME_TRIPPED      LOW

#define L_PP_PIN            44
#define R_PP_PIN            30

#define MID_TRIP            A2
#define COMM_TRIP           2
#define LADDER_IR           SCL
#define COMM_IR             4
#define MID_IR              SDA
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
#define BOTH        'b'
#define QUIT        'q'

#define CLOSE       1
#define OPEN        0

#define EXTEND      1
#define SHRINK      0
#define H_VEL       255


PS2X ps2x;
int error = 0;
byte type = 0, vibrate = 0, ps2_on = 0,
     l_piston_state = 0, r_piston_state = 0,
     l_pp_state = 0, r_pp_state = 0;

bool l_home_trip = 0, r_home_trip = 0, mid_trip = 0, comm_trip = 0,
     ladder_ir = 0, comm_ir = 0, mid_ir = 0;

void setup() {
  PC.begin(9600);


  motor_init(L_MOTOR);
  motor_init(R_MOTOR);
//  TCCR2A = (TCCR2A & ~TIMER_PRESCALE_MASK) | TIMER_CLK_DIV8);
//  TCCR2B = (TCCR2B & ~TIMER_PRESCALE_MASK) | TIMER_CLK_DIV8);
  pinMode(L_PISTON_PIN, OUTPUT);
  pinMode(R_PISTON_PIN, OUTPUT);

  pinMode(L_PP_PIN, OUTPUT);
  pinMode(R_PP_PIN, OUTPUT);

  pinMode(L_HOME_TRIP, INPUT);
  pinMode(R_HOME_TRIP, INPUT);
  pinMode(MID_TRIP, INPUT);
  pinMode(LADDER_IR, INPUT);
  pinMode(COMM_TRIP, INPUT);
  pinMode(COMM_IR, INPUT);
  pinMode(MID_IR, INPUT);

  // run(BOTH, STOP, 0);
  /*  attachInterrupt(L_HOME_TRIP_INT, l_home_trip_isr, HIGH);
    attachInterrupt(R_HOME_TRIP_INT, r_home_trip_isr, HIGH);
    attachInterrupt(MID_TRIP_INT, mid_trip_isr, HIGH);
    */
  ps2_init();

}

void loop() {
  ps2_ui();
  pc_ui();

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

  /*
      update(L_HOME_TRIP);
      update(R_HOME_TRIP);
      update(MID_TRIP);
      update(COMM_TRIP);
      update(LADDER_IR);
      update(MID_IR);
      update(COMM_IR);
      Serial.print("\tL_HOME_TRIPval : ");
      Serial.print(l_home_trip);
      Serial.print("\tR_HOME_TRIPval : ");
      Serial.print(r_home_trip);
      Serial.print("\tCOMM_TRIPval : ");
      Serial.print(comm_trip);
      Serial.print("\tMID_TRIPval : ");
      Serial.print(mid_trip);
      Serial.print("\tLADDER_IRval : ");
      Serial.print(ladder_ir);
      Serial.print("\tCOMM_IRval : ");
      Serial.print(comm_ir);
      Serial.print("\tMID_IRval : ");
      Serial.print(mid_ir);
    */
  Serial.println(F("\tloop"));

  delay(20);


}
