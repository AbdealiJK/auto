#define RETREAT_TIME 150
#define PROCEED_TIME 100
void ladder() {
  long start_time;
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
        
        Serial.println("Closing piston");
        piston(CLOSE); // clamp
        Serial.println("Piston closed");
        
        if ( n == 1 ) {
              Serial.println("Activating tail piston through slave");
              NEXT.write('r');
              NEXT.write('p');
              NEXT.write('c');    
              listen();
        }
        
        Serial.println("Waiting for 'c' ... ");
        while( !Serial.available() || ( Serial.available() && Serial.read() != 'c' ) );
        
                
        Serial.println("Going towards home");
        while( run ( HOME, 200 ) ) { // Bot goes up till fixedclamp_trip
          if ( q_stop() ) break;
          if ( fixedclamp_trip ) {
            Serial.println("Fixed clamp was pressed !");
            run ( STOP, 255 );
            break;
          }
        }
        while( run ( HOME, 200 ) ) { // Bot goes up till fixedclamp_trip
          if ( q_stop() ) break;
          if ( !fixedclamp_trip ) {
            Serial.println("Fixed clamp was removed !");
            run ( STOP, 255 );
            break;
          }
        }
        Serial.println("Stopped ... but not done");
        
        Serial.println("Waiting for 'c' ... ");        
        while( !Serial.available() || ( Serial.available() && Serial.read() != 'c' )  );
        
        
        start_time = millis();
        while( run ( HOME, 200 ) ) { // Bot goes up till fixedclamp_trip
          if ( q_stop() ) break;
          if ( millis() - start_time > PROCEED_TIME ) {
            run(STOP, 255);
            break; 
          }
        }
        Serial.println("Stopped");

        Serial.println("Waiting for 'c' ... ");        
        while( !Serial.available() || ( Serial.available() && Serial.read() != 'c' ) );
        

        Serial.println("Moving middle for a while");
        start_time = millis();
        while( run ( MID, 200 ) ) { // Bot goes down a little 
          if ( q_stop() ) break;
          if ( millis() - start_time > RETREAT_TIME ) {
            run(STOP, 255);
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
        Serial.println("Something tripped");

        Serial.println("Waiting for 'c' ... ");        
        while( !Serial.available() || ( Serial.available() && Serial.read() != 'c' ) );
      }
  
  
    
    
  
      // Last rung
      /*  Serial.println("Going towards home");
        while( run ( HOME, 200 ) ) { // Bot goes up till fixedclamp_trip
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
      */
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
