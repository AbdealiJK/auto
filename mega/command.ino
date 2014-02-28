void pc_ui() {

  if ( ! PC.available() )
    return;
  Serial.println("In UI");

  char c = PC.peek();
  Serial.print(F("Got :"));
  Serial.println(c);
  if ( c == LEFT || c == RIGHT || c == BOTH ) {
    PC.read();
    while (!PC.available());
    char c2 = PC.read();
    if ( c2 == 'h' ) {
      int vel = pc_get_int();
      PC.print(c);
      PC.print(" - ");
      PC.print(F("going home at pwm = "));
      PC.print(vel);
      PC.print(F(" ... "));
      go_home(c, abs(vel));
      PC.println(F("DONE"));
    } else if ( c2 == 'v' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> VELOCITY
      int vel = pc_get_int();
      PC.print(c);
      PC.print(" - ");
      PC.print(F("motor moving at pwm = "));
      PC.print(vel);
      PC.print(F(" ... "));
      ;
      while ( run( c, ( vel < 0 ) ? HOME : MID, abs(vel)) );
      PC.println(F("DONE"));
    } else if ( c2 == 'f' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>> MOTION with fixed clamp also
      int vel = pc_get_int();
      PC.print(c);
      PC.print(" - ");
      PC.print(F("motor moving (with fixed clamp) at pwm = "));
      PC.print(vel);
      PC.print(F(" ... "));
      ;
      while ( run( c, ( vel < 0 ) ? HOME : MID, abs(vel) ) ) {
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
      ;
      while ( run( c, ( vel < 0 ) ? HOME : MID, abs(vel) ) ) {
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
  }

  if ( c == 'd' ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DATA
    PC.read();
    // Display initial values :
    update(L_HOME_TRIP);
    update(R_HOME_TRIP);
    update(L_SEESAW_IR);
    update(R_SEESAW_IR);
    update(MID_TRIP);
    update(COMM_TRIP);
    update(LADDER_IR);
    update(LADDER_FORCE);
    update(MID_IR);
    update(COMM_IR);
    PC.println(F(">>> DATA : "));
    PC.print(F("TRIPS : \n LEFT home-trip: \t"));
    PC.println(l_home_trip);
    PC.print(F(" RIGHT home-trip: \t"));
    PC.println(r_home_trip);
    PC.print(F(" mid-trip: \t"));
    PC.println(mid_trip);
    PC.print(F("SEESAW : \n LEFT seesaw-ir: \t"));
    PC.println(l_seesaw_ir);
    PC.print(F(" RIGHT seesaw-ir: \t"));
    PC.println(r_seesaw_ir);
    PC.print(F("LADDER : \n ladder-ir: \t"));
    PC.println(ladder_ir);
    PC.print(F(" ladder-force: \t"));
    PC.println(ladder_force);
    PC.print(F("POLEWALK : \n mid-ir: \t"));
    PC.println(mid_ir);
    PC.print(F("COMM : \n comm-ir: \t"));
    PC.println(comm_ir);
    PC.print(F(" comm-trip: \t"));
    PC.println(comm_trip);
    PC.println(F(" Press a key to continue ...."));
    while(!PC.available());
  } else if ( c == 'm') {
    PC.read();
    go_mid(BOTH, 255);
  } else if ( c == '4' ) {
    PC.read();
    
    delay(1);
    if ( PC.available() ) {
      char c2 = PC.read();
      if ( c2 == 'a' ) {
        ladder_init();
      } else if ( c2 == 'b' ) {
        ladder_geton();
      } else if ( c2 == 'c' ) {
        ladder();
      } else if ( c2 == 'd' ) {
        ladder_getoff();
      }
    } else {
      ladder_init();
      ladder_geton();
      ladder();
      ladder_getoff();
    }
  } else if ( c == '3' ) {
    PC.read();
    delay(1);
    if ( PC.available() ) {
      char c2 = PC.read();
      if ( c2 == 'a' ) {
        polewalk_init();
      } else if ( c2 == 'b' ) {
        polewalk_geton();
      } else if ( c2 == 'c' ) {
        polewalk();
      } else if ( c2 == 'd' ) {
        polewalk_getoff();
      }
    } else {
      polewalk_init();
      polewalk_geton();
      polewalk();
      polewalk_getoff();
    }
  } else if ( c == '2' ) {
    delay(1);
    PC.read();
    char c2 = PC.read();
    if ( c2 == 'a' ) {
      swing_init();
    } else if ( c2 == 'b' ) {
      swing_geton();
    } else if ( c2 == 'c' ) {
      swing();
    } else if ( c2 == 'd' ) {
      swing_getoff();
    }
    else{
        swing_init();
        swing_geton();
        swing();
        swing_getoff();
    
    }
  } else if ( c == '1' ) {
    delay(1);
    PC.read();
    char c2 = PC.read();
    if ( c2 == 'a' ) {
      seesaw_init();
    } else if ( c2 == 'b' ) {
      seesaw_geton();
    } else if ( c2 == 'c' ) {
      seesaw();
    } else if ( c2 == 'd' ) {
      seesaw_getoff();
    }
  }

  q_stop();
}

