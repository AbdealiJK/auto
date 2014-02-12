void ui() {

  if ( ! PC.available() )
    return;
  Serial.println("In UI");

  char c = PC.read();
  Serial.print(F("Got :"));
  Serial.println(c);
  while (!PC.available());
  char c2 = PC.read();
  if ( c2 == 'd' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DATA
    // Display initial values :
    update(L_HOME_TRIP);
    update(R_HOME_TRIP);
    update(MID_TRIP);
    update(COMM_TRIP);
    update(LADDER_IR);
    update(MID_IR);
    update(COMM_IR);
    PC.print(F(">>> data for master : "));
    PC.print(F("Trips - LEFT home-trip:"));
    PC.println(l_home_trip);
    PC.print(F("Trips - RIGHT home-trip:"));
    PC.println(r_home_trip);
    PC.print(F(" mid-trip:"));
    PC.println(mid_trip);
    PC.print(F(" comm-trip:"));
    PC.println(comm_trip);
    PC.print(F(" ladder-ir:"));
    PC.println(ladder_ir);
    PC.print(F(" mid-ir:"));
    PC.println(mid_ir);
    PC.print(F(" comm-ir:"));
    PC.println(comm_ir);
    PC.println(F(" >> begun"));

  } else if ( c2 == 'v' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> VELOCITY
    int vel = pc_get_int();
    PC.print(c);
    PC.print(" - ");
    PC.print(F("motor moving at pwm = "));
    PC.print(vel);
    PC.print(F(" ... "));
    run( c, ( vel < 0 ) ? HOME : MID, abs(vel));
    while ( ( c == LEFT && l_running ) || ( c == RIGHT && r_running ) ) {
      if ( q_stop() ) break;
    }
    PC.println(F("DONE"));
  } else if ( c2 == 'f' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>> MOTION with fixed clamp also
    int vel = pc_get_int();
    PC.print(c);
    PC.print(" - ");
    PC.print(F("motor moving (with fixed clamp) at pwm = "));
    PC.print(vel);
    PC.print(F(" ... "));
    run( c, ( vel < 0 ) ? HOME : MID, abs(vel) );
    while ( ( c == LEFT && l_running ) || ( c == RIGHT && r_running ) ) {
      if ( q_stop() ) break;
      update(LADDER_IR);
      if ( ladder_ir ) {
        run ( c, STOP, 0 );
        PC.println(F("fixed clamp pressed... "));
        break;
      }
    }
    PC.println(F("DONE"));
  } else if ( c2 == 'i' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>. MOTION with MID_IR
    int vel = pc_get_int();
    PC.print(c);
    PC.print(" - ");
    PC.print(F("motor moving at pwm = "));
    PC.print(vel);
    PC.print(F(" ... "));
    run( c, ( vel < 0 ) ? HOME : MID, abs(vel) );
    while ( ( c == LEFT && l_running ) || ( c == RIGHT && r_running ) ) {
      if ( q_stop() ) break;
      update(MID_IR);
      if ( mid_ir ) {
        run ( c, STOP, 0 );
        PC.print(F("IR reached.... "));
        PC.println(F("Mas-clamp Now in middle position"));
        break;
      }
    }
    PC.println(F("DONE"));
  } else if ( c2 == 'p' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PISTON CLOSE
    PC.print(c);
    PC.print(" - ");
    PC.print(F("closing piston"));
    piston(c, CLOSE);
  } else if ( c2 == 'o' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PISTON OPEN
    PC.print(c);
    PC.print(" - ");
    PC.print(F("opening piston"));
    piston(c, OPEN);
  } else if ( c2 == 'e' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PP EXTEND
    PC.print(c);
    PC.print(" - ");
    PC.print(F("extending pp"));
    pp(c, EXTEND);
  } else if ( c2 == 's' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PP SHRINK
    PC.print(c);
    PC.print(" - ");
    PC.print(F("shrinking pp"));
    pp(c, SHRINK);
  }

  q_stop();
}

