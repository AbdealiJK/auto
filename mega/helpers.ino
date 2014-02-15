// ----------------------------------------------------------------- MOTOR RUN
void run(int c, int dir, int pwm) {
  int m1 = 0, m2 = 0, mp = 0;
  if ( c == LEFT || c == BOTH ) {
    update(L_HOME_TRIP);
    update(MID_TRIP);
    if ( ! ( (dir == HOME && l_home_trip) || (dir == MID && mid_trip)  ) ) {
      digitalWrite(L_MOTOR_1, dir / 2);
      digitalWrite(L_MOTOR_2, dir % 2);
      analogWrite(L_MOTOR_PWM, abs(pwm));
      l_running = dir;
    } else {
      if ( dir == MID && mid_trip )
        Serial.print("Left motor trip middle");
      else if ( dir == HOME && mid_trip )
        Serial.print("Left motor trip middle");
          
       digitalWrite(L_MOTOR_1, 0);
      digitalWrite(L_MOTOR_2, 0);
      analogWrite(L_MOTOR_PWM, 0);
      l_running = STOP;
    }
  }
  if ( c == RIGHT || c == BOTH ) {
    update(R_HOME_TRIP);
    update(MID_TRIP);
    if ( !( (dir == HOME && r_home_trip) || (dir == MID && mid_trip) ) ) {
      digitalWrite(R_MOTOR_1, dir / 2);
      digitalWrite(R_MOTOR_2, dir % 2);
      analogWrite(R_MOTOR_PWM, abs(pwm));
      r_running = dir;
    } else {
      Serial.print("Right motor trip");
      digitalWrite(R_MOTOR_1, 0);
      digitalWrite(R_MOTOR_2, 0);
      analogWrite(R_MOTOR_PWM, 0);
      r_running = STOP;
    }
  }
}

// ----------------------------------------------------------------- MOTOR HELPERS
void go_home(char ch, int vel) {
  run( ch,  HOME , vel);

  while ( l_running || r_running ) {
    if ( q_stop() ) break;
    if ( ! l_running ) run(LEFT,  STOP, 0);
    if ( ! r_running ) run(RIGHT, STOP, 0);
  }
}

void go_mid(int c, int vel) {
  if ( c == LEFT || c == BOTH ) {
    run(LEFT, MID, vel);
    while (l_running ) {
      if ( q_stop() ) break;
      update(MID_IR);
      if ( mid_ir ) {
        run ( LEFT, STOP, 0 );
        PC.print(F("IR reached.... "));
        break;
      }
    }
  }
  if ( c == RIGHT || c == BOTH ) {
    run(RIGHT, MID, vel);
    while (r_running) {
      if ( q_stop() ) break;
    }
  }
}

void go_away(int c, int vel) {
  if ( c == LEFT ) {
    run(LEFT, MID, vel);
    while (l_running ) {
      if ( q_stop() ) break;
    }
  }
  if ( c == RIGHT ) {
    run(RIGHT, MID, vel);
    while (r_running) {
      if ( q_stop() ) break;
    }
  }
}

void go_up(int vel, int no) {
  update(LADDER_IR);
  int flag = 0, target_flag = no, init_ladder_ir = ladder_ir;
  Serial.println("Entered go up");
  
  run(LEFT, HOME, 200);
  while ( l_running || r_running ) {
    if ( q_stop() ) break;
    update(LADDER_IR);
    
    if ( flag % 2 == 0 && ladder_ir != init_ladder_ir ) {
      flag++;
      Serial.println("Changed");
    } else if ( flag % 2 == 1 && ladder_ir == init_ladder_ir ) {
      flag++;      Serial.println("Changed");
    }
    if ( flag == target_flag ) {
      delay(600);// to be changed for battery voltage
      run( LEFT, STOP, 0 );
      PC.print(target_flag);
      PC.println(F(" changes detected by IR "));
      break;
    }
  }

  long start_time = millis();
  run( LEFT, MID, 255 );
  while ( l_running ) {
    if ( q_stop() ) break;
    if ( millis() - start_time > LADDER_TIME ) {
      run(BOTH, STOP, 0);
      PC.println(F(" time delay done "));
      break;
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
    val = &ladder_ir;  pin = LADDER_IR;   tripped = LADDER_IR_FOUND;   loops = 10000;
  } else if ( tr == COMM_IR ) {
    val = &comm_ir;  pin = COMM_IR;   tripped = COMM_IR_FOUND;   loops = 10000;
  } else if ( tr == MID_IR ) {
    val = &mid_ir;  pin = MID_IR;   tripped = MID_IR_FOUND;   loops = 10000;
  }

  if ( loops > 0 && pin >= 0) {

    long int temp = 0;
    for ( long int lim = 0; lim < loops; lim++ ) {
      temp += digitalRead(pin);
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

// ----------------------------------------------------------------- MOTOR TRIP ISR
void l_home_trip_isr () {
  if ( l_running == HOME ) {
    run(LEFT, STOP, 0);
    l_running = 0;
  }
  //  Serial.print('L');
}
void r_home_trip_isr () {
  if ( r_running == HOME ) {
    run(RIGHT, STOP, 0);
    r_running = 0;
  }
  //  Serial.print('R');
}
void mid_trip_isr () {
  if ( l_running == MID) {
    run(LEFT, STOP, 0);
    l_running = 0;
  }
  if ( r_running == MID) {
    run(RIGHT, STOP, 0);
    r_running = 0;

  }
  //  Serial.print('M');
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
    if ( ps2x.Button(PSB_L1) ) { // print stick values if either is TRUE
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
  }
  if ( ps2_on ) {
    ps2x.read_gamepad(false, vibrate);
    if ( ps2x.Button(PSB_L1) ) {
      return 0;
    }
  }
}

