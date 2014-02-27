// ----------------------------------------------------------------- MOTOR RUN
void motor_init(int p_1, int p_2, int p_pwm) {
  pinMode(p_1, OUTPUT);
  pinMode(p_2, OUTPUT);
  pinMode(p_pwm, OUTPUT);
}
void motor(int p_1, int p_2, int p_pwm, int dir, int pwm) {
  digitalWrite(p_1, dir / 2);
  digitalWrite(p_2, dir % 2);
  analogWrite(p_pwm, abs(pwm));
}
int run(int c, int dir, int pwm) {
  int m1 = 0, m2 = 0, mp = 0, stopped = 0;
  if ( q_stop() ) {
    Serial.print("QUIT");
    return 0;

  }

  if ( c == LEFT || c == BOTH ) {
    update(L_HOME_TRIP);
    update(MID_TRIP);
    if ( ! ( (dir == HOME && l_home_trip) || (dir == MID && mid_trip)  ) ) {
      motor(L_MOTOR, dir, pwm);
      stopped = stopped & 0x01;
    } else {
      if ( dir == MID && mid_trip )
        PC.println("Left motor trip middle");
      else if ( dir == HOME && l_home_trip )
        PC.println("Left motor trip home");
      motor(L_MOTOR, 0, 255);
      stopped = stopped | 0x02;
    }
  }
  if ( c == RIGHT || c == BOTH ) {
    update(R_HOME_TRIP);
    update(MID_TRIP);
    if ( !( (dir == HOME && r_home_trip) || (dir == MID && mid_trip) ) ) {
      motor(R_MOTOR, dir, pwm);
      stopped = stopped & 0x02;
    } else {
      if ( dir == MID && mid_trip )
        PC.println("Right motor trip middle");
      else if ( dir == HOME && r_home_trip )
        PC.println("Right motor trip home");
      motor(R_MOTOR, 0, 255);
      stopped = stopped | 0x01;
    }
  }

  if ( ( stopped == 3 && c == BOTH ) || 
    ( stopped == 2 && c == LEFT ) ||
    ( stopped == 1 && c == RIGHT ) ) {
    return 0;
  }
  return 1;
}

// ----------------------------------------------------------------- MOTOR HELPERS
void go_home(char ch, int vel) {
  while ( run( ch,  HOME , vel) );
}

void go_mid(int c, int vel) {
  if ( c == LEFT || c == BOTH ) {
    while ( run(LEFT, MID, vel) ) {
      update(MID_IR);
      if ( mid_ir ) {
        run ( LEFT, STOP, 0 );
        PC.print(F("IR reached.... "));
        break;
      }
    }
  }
  if ( c == RIGHT || c == BOTH ) {
    while ( run(RIGHT, MID, vel) );
  }
}

void go_away(int c, int vel) {
  if ( c == LEFT ) {
    while ( run(LEFT, MID, vel) );
  }
  if ( c == RIGHT ) {
    while ( run(RIGHT, MID, vel) );
  }
}

void go_up(int vel, int no, bool tail) {
  update(LADDER_IR);
  int flag = 0, target_flag = no, init_ladder_ir = ladder_ir;
  Serial.println("Entered go up");

  
      Serial.print("INITIAL, now it is ");
      Serial.println(ladder_ir);
  while ( run(LEFT, HOME, vel) ) {
    update(LADDER_IR);

    if ( flag % 2 == 0 && ladder_ir != init_ladder_ir ) {
      flag++;
      Serial.print("Changed, now it is ");
      Serial.println(ladder_ir);
    } else if ( flag % 2 == 1 && ladder_ir == init_ladder_ir ) {
      flag++;
      Serial.print("Changed, now it is ");
      Serial.println(ladder_ir);
    }
    if ( flag == target_flag ) {
      run( LEFT, STOP, 0 );
      PC.print(target_flag);
      PC.println(F(" changes detected by IR "));
      if(tail)
      {
        piston(RIGHT,CLOSE);
        delay(500);
      }
      break;
    }
  }
  

  long start_time = millis();
  if(!tail)
  {
  while ( run( LEFT, HOME, 255 ) ) {
    if ( millis() - start_time > LADDER_TIME ) {
      run(BOTH, STOP, 0);
      PC.println(F(" time delay done "));
      break;
    }
  }
  }

}

// ----------------------------------------------------------------- SOLENOID
void piston(int c, int v) {
  if ( c == LEFT || c == BOTH )
    digitalWrite(L_PISTON_PIN, v == CLOSE);
  if ( c == RIGHT || c == BOTH )
    digitalWrite(R_PISTON_PIN, v == CLOSE);
}

void pp(int c, int v) {
  if ( c == LEFT || c == BOTH || c == MID )
    digitalWrite(L_PP_PIN, v == EXTEND);
  if ( c == RIGHT || c == BOTH )
    digitalWrite(R_PP_PIN, v == EXTEND);
}

// ----------------------------------------------------------------- TRIP UPDATES
void update(int tr) {
  long int temp = 0, lim = 0;
  bool *val;
  int tripped, pin;
  long int loops = -1;

  if ( tr == L_HOME_TRIP ) {
    val = &l_home_trip;  pin = L_HOME_TRIP;   tripped = L_HOME_TRIPPED;  loops = 1;
  } else if ( tr == R_HOME_TRIP ) {
    val = &r_home_trip;  pin = R_HOME_TRIP;   tripped = R_HOME_TRIPPED;  loops = 1;
  } else if ( tr == MID_TRIP ) {
    val = &mid_trip;  pin = MID_TRIP;   tripped = MID_TRIPPED;     loops = 1;
  } else if ( tr == COMM_TRIP ) {
    val = &comm_trip;  pin = COMM_TRIP;   tripped = COMM_TRIPPED;   loops = 1;
  } else if ( tr == LADDER_IR ) {
    val = &ladder_ir;  pin = LADDER_IR;   tripped = LADDER_IR_FOUND;   loops = 50000;
  } else if ( tr == COMM_IR ) {
    val = &comm_ir;  pin = COMM_IR;   tripped = COMM_IR_FOUND;   loops = 10000;
  } else if ( tr == MID_IR ) {
    val = &mid_ir;  pin = MID_IR;   tripped = MID_IR_FOUND;   loops = 10000;
  }

  if ( loops > 0 && pin >= 0) {

    long int temp = 0;
    for ( long int lim = 0; lim < loops; lim++ ) {
      temp += digitalRead(pin);
//      if ( temp < 0.3 * lim && lim > 500 ) {
 //       break;
  //    }
    }

    if ( temp > 0.9 * loops ) {
      if ( tripped == 1 ) {
        *val = 1;
      } else {
        *val = 0;
      }
    } else {
      if ( tripped == 1 ) {
        *val = 0;
      } else {
        *val = 1;
      }
    }
  }
}

// ----------------------------------------------------------------- MISC
int pc_get_int() {
  int temp = 0, next_val, neg = 1;
  char temp_c;

  while (!PC.available());
  delay(2);
  next_val = PC.peek();
  if ( next_val == '-' ) {
    neg = -1;
    PC.read();
    next_val = PC.peek();
  }
  while ( PC.available() && next_val <= '9' && next_val >= '0' ) {
    PC.read();
    temp *= 10;
    temp += next_val - '0';
    next_val = PC.peek();
  }
  return temp * neg;
}

int q_stop () {
  if ( PC.available() && PC.peek() == QUIT ) {
    PC.read();
    run(LEFT, STOP, 0);
    run(RIGHT, STOP, 0);
    PC.println(F("Stopping all motors ! > Manual stop"));
    return 1;
  }
  if ( ps2_on ) {
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    if ( ps2x.ButtonPressed(PSB_L1) ) { // print stick values if either is TRUE
      return 1;
    }
  }

  return 0;
}

bool quit_or_continue() {
  PC.println(F("Press 'c' ... "));
  while ( 1 ) {
    if ( PC.available() && PC.peek() == 'q' ) return 1;
    if ( PC.available() && PC.peek() == 'c' ) {
      PC.read();
      return 0;
    }
    if ( ps2_on ) {
      ps2x.read_gamepad(false, vibrate);
      if ( ps2x.ButtonPressed(PSB_L1) ) {
        return 0;
      }
    }
  }
}

/*
  Left Motor
  Right Motor
  10, 11, 12 - Motor 1
  A0,  8,  9 - Motor 2

 Piston 44, 46, 30, 28

 Middle trip - 6

 4 - comm tsop
 3 - right trip
 2 - comm trip

 A4  - LEFT TRIP
 SDA - MIDDLE TSOP
 SCL - LADDER IR




*/
