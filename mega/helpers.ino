void run(int c, int dir, int pwm) {
  int m1 = 0, m2 = 0, mp = 0;
  if ( c == LEFT ) {
    m1 = L_MOTOR_1;
    m2 = L_MOTOR_2;
    mp = L_MOTOR_PWM;
    l_running = dir;
    
   
  } else if ( c == RIGHT ) {
    m1 = R_MOTOR_1;
    m2 = R_MOTOR_2;
    mp = R_MOTOR_PWM;
    r_running = dir;
        
     }
     
       
  if ( m1 && m2 ) {
    digitalWrite(m1, dir / 2);
    digitalWrite(m2, dir % 2);
    analogWrite(mp, abs(pwm));
  }
}

void l_home_trip_isr () {
  if ( l_running == HOME ) {
    run(LEFT, STOP, 0);
    l_running = 0;
  }
    Serial.print('L');
}
void r_home_trip_isr () {
  if ( r_running == HOME ) {
    run(RIGHT, STOP, 0);
    r_running = 0;
  }
  Serial.print('R');
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
    Serial.print('M');
}

void piston(int c, int v) {
  int pin = 0;
  if ( c == LEFT )
    pin = L_PISTON_PIN;
  else if ( c == RIGHT )
    pin = R_PISTON_PIN;
  if ( pin ) {
    digitalWrite(pin, v == CLOSE);
  }
}

void pp(int c, int v) {
  int pin = 0;
  if ( c == LEFT )
    pin = L_PP_PIN;
  else if ( c == RIGHT )
    pin = R_PP_PIN;
  if ( pin ) {
    digitalWrite(pin, v == EXTEND);
  }
}

// -------------------------------------------------

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

// -------------------------------------------------

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
  return 0;
}



void go_home(char ch)
{
  
  if( ch == BOTH )
  {
    run( LEFT,  HOME , H_VEL);
    run( RIGHT, HOME , H_VEL);
  }
  else if( ch == LEFT )
  {
      run( LEFT,  HOME , H_VEL);
  }
  else if( ch == RIGHT )
  {
      run( RIGHT,  HOME , H_VEL);
  }  
  else
    return;
    
    while ( l_running || r_running ) {
      if ( q_stop() ) break;
    }
}
void go_mid(int vel)
{
  go_home(BOTH);
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
  run(RIGHT, MID, vel);
  while (r_running) {
  if ( q_stop() ) break;
  }

}

