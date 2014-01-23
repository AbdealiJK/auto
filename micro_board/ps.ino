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
        
        PC.print("Closing piston");
        piston(CLOSE); // clamp
        PC.print("Piston closed");
        
        Serial.println("Waiting for 'c' ... ");
        while( !Serial.available() || ( Serial.available() && Serial.read() != 'c' ) );
                
        PC.print("Going towards middle");
        while( run ( MID, 200 ) ) { // Bot goes up till fixedclamp_trip
          if ( q_stop() ) break;
          if ( fixedclamp_trip ) {
            Serial.println("Fixed clamp was pressed !");
            run ( STOP, 255 );
            break;
          }
        }
        Serial.println("Stopped");
        
        Serial.println("Waiting for 'c' ... ");        
        while( !Serial.available() || ( Serial.available() && Serial.read() != 'c' ) );
        
        Serial.println("Moving home for a while");
        long start_time = millis();
        while( run ( HOME, 200 ) ) { // Bot goes down a little 
          if ( q_stop() ) break;
          if ( millis() - start_time > 200 ) {
            break; 
          }
        }
        Serial.println("Moved for soemtime");
        
        Serial.println("Waiting for 'c' ... ");        
        while( !Serial.available() || ( Serial.available() && Serial.read() != 'c' ) );

        Serial.println("Opening piston");
        piston(OPEN); // clamp open
        Serial.println("Piston openend");

        Serial.println("Waiting for 'c' ... ");        
        while( !Serial.available() || ( Serial.available() && Serial.read() != 'c' ) );
        
        Serial.println("Goinig up !");
        while ( run( MID, 200) ) { // go up till middle_trip
          if ( q_stop() ) break;
        }
        Serial.println("Soemthing tripped");

        Serial.println("Waiting for 'c' ... ");        
        while( !Serial.available() || ( Serial.available() && Serial.read() != 'c' ) );
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
