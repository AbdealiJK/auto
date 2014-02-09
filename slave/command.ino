void slave_commands() {

  if ( ! MASTER.available() )
    return;

  q_stop();

  char c = MASTER.read();
  MASTER.print(F("SLAVE >>>>> GOT :"));
  MASTER.println(c);

  if ( c == DATA ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> WATCH
    // Display initial values :
    update_home_trip();
    MASTER.print(F("SLAVE > home-trip : \t"));
    MASTER.println(home_trip);
    update_mid_ir();
    MASTER.print(F("SLAVE > mid-ir : \t"));
    MASTER.println(mid_ir);
    MASTER.print(COMM_END);
  }
  else if ( c == MOVE ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> VELOCITY
    int vel = get_int();
    MASTER.print(F("SLAVE > moving at pwm : \t"));
    MASTER.println(vel);

    while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
      if ( q_stop() ) break;

    }
    MASTER.println(F("SLAVE > Stopped moving"));
    MASTER.print(COMM_END);

  }
  else if ( c == MOVE_MID  ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>. IR
    int vel = get_int();
    MASTER.print(F("SLAVE > moving at pwm = "));
    MASTER.println(vel);

    while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
      if ( q_stop() ) break;
      update_mid_ir();
      if ( mid_ir ) {
        run ( STOP, 255 );
        MASTER.println(F("SLAVE > reached middle position"));
        break;
      }
    }
    if ( ! mid_ir ) // as it didnt trip yet :(
      MASTER.println(F("SLAVE > stopped before reaching middle position"));
    MASTER.print(COMM_END);
  }
  else if ( c == CLOSE ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PISTON CLOSE
    MASTER.println(F("SLAVE > closing "));
    piston(CLOSE);
    MASTER.print(COMM_END);
  } else if ( c == OPEN ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PISTON OPEN
    MASTER.println(F("SLAVE > opening "));
    piston(OPEN);
    MASTER.print(COMM_END);
  } else if ( c == EXTEND ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PP EXTEND
    MASTER.print(F("Extending pp Mas"));
    pp(OPEN);
    MASTER.print(COMM_END);
  } else if ( c == SHRINK ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PP SHRINK
    MASTER.print(F("Shrinking pp Mas"));
    pp(CLOSE);
    MASTER.print(COMM_END);
  }

  /*else if ( c == PINS ) {
    pinMode(MOTOR_1, INPUT);
    pinMode(MOTOR_2, INPUT);
    pinMode(MOTOR_PWM, INPUT);
    pinMode(PISTON_PIN, INPUT);
    pinMode(HOME_TRIP, INPUT);
    pinMode(MID_IR, INPUT);

    MOTOR_1      = MASTER.read();
    MOTOR_2      = MASTER.read();
    MOTOR_PWM    = MASTER.read();
    PISTON_PIN   = MASTER.read();
    HOME_TRIP    = MASTER.read();
    MID_IR       = MASTER.read();
    HOME_TRIPPED = MASTER.read();
    MID_IR_FOUND = MASTER.read();


    pinMode(MOTOR_1, OUTPUT);
    pinMode(MOTOR_2, OUTPUT);
    pinMode(MOTOR_PWM, OUTPUT);
    pinMode(PISTON_PIN, OUTPUT);
    pinMode(HOME_TRIP, INPUT);
    pinMode(MID_IR, INPUT);
  }
  */
}

