void ladder() {
  while (1) {
    if ( MY_CLAMP == 'r' ) {
      // First rung -- right : go home
 //     go_home(200);
      break;
    } else {
      // First rung -- left : go to 2nd rung


      // Repetitive rungs -- left : clamp, go left till fixedclamp_trip, come back sli, open clamp, go right till middle trip
      int n = 4;
      while (n--) {
        piston(CLOSE); // clamp
        while( run ( HOME, 200 ) ) { // Bot goes up till fixedclamp_trip
          q_stop();
          if ( fixedclamp_trip == FIXEDCLAMP_TRIPPED ) {
            run ( STOP, 255 );
            break;
          }
        }
        long start_time = millis();
        while( run ( MID, -200 ) ) { // Bot goes down a little 
          q_stop();
          if ( millis() - start_time > 200 ) {
            break; 
          }
        }
        piston(OPEN); // clamp open
        while ( run( MID, 200) ) { // go up till middle_trip
          q_stop();
        }
      }

      // Last rung

      // Flag
    }
  }
}

void seesaw() {
  
}
void swing() {

}

void polewalk() {

}
