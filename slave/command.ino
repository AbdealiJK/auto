void slave_commands() {

  if ( ! MASTER.available() )
    return;

  q_stop();
  
  char c = MASTER.read();
  MASTER.print("SLAVE >>>>> GOT :");
  MASTER.println(c);

  if ( c == DATA ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> WATCH
    // Display initial values :
    update_home_trip();
    MASTER.print("SLAVE > home-trip : \t");
    MASTER.println(home_trip);
    update_ir_trip();
    MASTER.print("SLAVE > ir-trip : \t");
    MASTER.println(ir_trip);
    MASTER.print(COMM_END);
  }
  else if ( c == MOVE ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> VELOCITY
    int vel = get_int(MASTER);
    MASTER.print("SLAVE > moving at pwm : \t");
    MASTER.println(vel);
    MASTER.print(COMM_END);
    while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
      if ( q_stop() ) break;
    }
    MASTER.println("SLAVE > Stopped moving");
    MASTER.print(COMM_END);
    
  }
  else if ( c == MOVE_MID  ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>. IR
    int vel = get_int(MASTER);
    MASTER.print("SLAVE > moving at pwm = ");
    MASTER.println(vel);
    MASTER.print(COMM_END);
    while ( run( ( vel < 0 ) ? HOME : MID, abs(vel)) ) {
      if ( q_stop() ) break;
      update_ir_trip();
      if ( ir_trip ) {
        run ( STOP, 255 );
        MASTER.println("SLAVE > reached middle position");
        break;
      }
    }
    if ( ! ir_trip ) // as it didnt trip yet :(
      MASTER.println("SLAVE > stopped before reaching middle position");
    MASTER.print(COMM_END);
  }
  else if ( c == CLOSE ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PISTON CLOSE
    MASTER.println("SLAVE > closing ");
    piston(CLOSE);
    MASTER.print(COMM_END);
  } else if ( c == OPEN ) { // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PISTON OPEN
    MASTER.println("SLAVE > opening ");
    piston(OPEN);
    MASTER.print(COMM_END); 
  }
  
}

