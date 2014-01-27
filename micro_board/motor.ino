// ------------------------------------------------
int run(int dir, int pwm) {
  update_home_trip();
  update_middle_trip();

  if ( home_trip && dir == HOME ) {
    digitalWrite(MOTOR_1, 0);
    digitalWrite(MOTOR_2, 0);
    analogWrite(MOTOR_PWM, 255);
    PC.println("\t Trip switch HOME pressed for some motor ! ");
    return 0;
  }

  if ( middle_trip  && dir == MID ) {
    digitalWrite(MOTOR_1, 0);
    digitalWrite(MOTOR_2, 0);
    analogWrite(MOTOR_PWM, 255);
    PC.println("\t Trip switch MIDDLE pressed for some motor ! ~");
    return 0;
  }

  digitalWrite(MOTOR_1, dir / 2);
  digitalWrite(MOTOR_2, dir % 2);
  analogWrite(MOTOR_PWM, pwm);
  return 1;
}

// ------------------------------------------------
void piston(int v) {
  digitalWrite(PISTON_PIN, v == CLOSE);
}

void go_home(int sp) {
  while ( run(HOME, sp) == 1 ) {
    if ( PC.available() && PC.read() == 'q' ) {
      run(STOP, 255);
      break;
    }
  }
}

void update_middle_trip() {
  if ( ! SLAVE && MIDDLE_TRIP != -1 ) {
    middle_trip = digitalRead(MIDDLE_TRIP) == MIDDLE_TRIPPED;
  }
}

void update_home_trip() {
  if (HOME_TRIP != -1 ) {
    home_trip = ( digitalRead(HOME_TRIP) == HOME_TRIPPED);
  }

}

void update_fixedclamp_trip() {
  if ( !SLAVE && FIXEDCLAMP_TRIP != -1 ) { // Flicker correction for fixed clamp.
    long int temp = 0, lim = 0;
    for ( lim = 0; lim < 10000; lim++ ) {
      temp += digitalRead(FIXEDCLAMP_TRIP) == FIXEDCLAMP_TRIPPED;
    }
    //      Serial.println(temp);
    if ( temp > 0.7 * lim )
      fixedclamp_trip = 1;
    else
      fixedclamp_trip = 0;
  }
}
