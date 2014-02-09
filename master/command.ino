void ui() {

  if ( ! PC.available() )
    return;
  Serial.println("In UI");
  
  char c = PC.peek();
  Serial.print(F("Got :"));
  Serial.println(c);
  if ( c == 'l' ) {
    PC.read();
    while (!PC.available());
    char c2 = PC.read();
    if ( c2 == DATA ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DATA
      // Display initial values :

      update(HOME_TRIP);
      update(MID_TRIP);
      update(COMM_TRIP);
      update(LADDER_IR);
      update(MID_IR);
      update(COMM_IR);
      PC.print(F(">>> data for master : "));
      PC.print(F("Trips - home-trip:"));
      PC.println(home_trip);
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
      PC.print(COMM_END);
    } else if ( c2 == MOVE ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> VELOCITY
      int vel = pc_get_int();
      PC.print(F("Mas-motor moving at pwm = "));
      PC.print(vel);
      PC.print(F(" ... "));
      while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
        if ( q_stop() ) break;
      }
      PC.println(F("DONE"));
      PC.print(COMM_END);
    } else if ( c2 == MOVE_LADDER ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>> MOTION with fixed clamp also
      int vel = pc_get_int();
      PC.print(F("Mas-motor moving (with fixed clamp) at pwm = "));
      PC.print(vel);
      PC.print(F(" ... "));
      while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
        if ( q_stop() ) break;
        update(LADDER_IR);
        if ( ladder_ir ) {
          run ( STOP, 255 );
          PC.println(F("fixed clamp pressed... "));
          break;
        }
      }
      PC.println(F("DONE"));
      PC.print(COMM_END);
    } else if ( c2 == MOVE_MID ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>. MOTION with MID_IR
      int vel = pc_get_int();
      PC.print(F("Mas-motor moving at pwm = "));
      PC.print(vel);
      PC.print(F(" ... "));
      while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
        if ( q_stop() ) break;
        update(MID_IR);
        if ( mid_ir ) {
          run ( STOP, 255 );
          PC.print(F("IR reached.... "));
          PC.println(F("Mas-clamp Now in middle position"));
          break;
        }
      }
      PC.println(F("DONE"));
      PC.print(COMM_END);
    } else if ( c2 == CLOSE ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PISTON CLOSE
      PC.print(F("Closing piston Mas"));
      piston(CLOSE);
      PC.print(COMM_END);
    } else if ( c2 == OPEN ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PISTON OPEN
      PC.print(F("Opening piston Mas"));
      piston(OPEN);
      PC.print(COMM_END);
    } else if ( c2 == EXTEND ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PP EXTEND
      PC.print(F("Extending pp Mas"));
      pp(OPEN);
      PC.print(COMM_END);
    } else if ( c2 == SHRINK ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PP SHRINK
      PC.print(F("Shrinking pp Mas"));
      pp(CLOSE);
      PC.print(COMM_END);
    }
  } else if ( c == 'r' ) {
    // >>>>>>>>>>>>>>>>>>>>> MAKE THE OTHER GUY DO IT !!!!!!!!!!!!!!!!!
    PC.read();
    delay(2);
    if ( ! SLAVE )
      PC.println(F("Oops, SLAVE not found :(((("));
    else {
      PC.println(F("Sending to other clamp"));
      while (PC.available())
        SLAVE.write(PC.read());
      listen();
    }
  }

  if ( c == '4' ) {
    delay(1);
    PC.read();
    char c2 = PC.read();
    if ( c2 == 'a' ) {
      ladder_init();
    } else if ( c2 == 'b' ) {
      ladder();
    }
  } else if ( c == '3' ) {
    delay(1);
    PC.read();
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
  
  /*else if ( c == PINS ) {
    slave_pins();
  }*/
  q_stop();
}

