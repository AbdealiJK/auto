
void ps2_init() {
  error = ps2x.config_gamepad(52, 51, 53, 50, true, true); //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

  if (error == 0) {
    PC.println("Found Controller, configured successful");
    //    PC.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    //    PC.println("holding L1 or R1 will print out the analog stick values.");
  }

  else if (error == 1)
    PC.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    PC.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    PC.println("Controller refusing to enter Pressures mode, may not support it. ");

  //PC.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch (type) {
    case 0:
      PC.println("Unknown Controller type");
      break;
    case 1:
      PC.println("DualShock Controller Found");
      break;
    case 2:
      PC.println("GuitarHero Controller Found");
      break;
  }
}

void ps2_ui() {

  delay(20);
  if ( ps2_on == 0 ) {
    ps2x.read_gamepad(false, vibrate);
    if (ps2x.Button(PSB_START))
      ps2_on = 1;
    else
      return;
  }

  ps2x.read_gamepad(false, vibrate);

  if ( ps2x.Button(PSB_L1) ) {
    run(BOTH, STOP, 0);
  }

  if ( ps2x.Button(PSB_L1) && ps2x.Button(PSB_L2) && ps2x.Button(PSB_R1) && ps2x.Button(PSB_R2) ) {
      seesaw_init();
      seesaw_geton();
      seesaw();
      seesaw_getoff();
      delay(10000);
      swing_init();
      swing_geton();
      swing();
      swing_getoff();
      delay(10000);
      polewalk_init();
      polewalk_geton();
      polewalk();
      polewalk_getoff();
  }

  if ( ps2x.Button(PSB_PAD_UP) ) {
    PC.println("SEESAW");
    if ( ps2x.Button(PSB_GREEN) ) {
      seesaw_init();
    } else if ( ps2x.Button(PSB_PINK) ) {
      seesaw_geton();
    } else if ( ps2x.Button(PSB_RED) ) {
      seesaw();
    } else if ( ps2x.Button(PSB_BLUE) ) {
      seesaw_getoff();
    } else if ( ps2x.ButtonPressed(PSB_R1) ) {
      seesaw_init();
      seesaw_geton();
      seesaw();
      seesaw_getoff();
    }
  }
  else if ( ps2x.Button(PSB_PAD_LEFT) ) {
    PC.println("SWING");
    if ( ps2x.Button(PSB_GREEN) ) {
      swing_init();
    } else if ( ps2x.Button(PSB_PINK) ) {
      swing_geton();
    } else if ( ps2x.Button(PSB_RED) ) {
      swing();
    } else if ( ps2x.Button(PSB_BLUE) ) {
      swing_getoff();
    } else if ( ps2x.ButtonPressed(PSB_R1) ) {
      swing_init();
      swing_geton();
      swing();
      swing_getoff();
    }
  }
  else if ( ps2x.Button(PSB_PAD_RIGHT) ) {
    PC.println("POLEWALK");
    if ( ps2x.Button(PSB_GREEN) ) {
      polewalk_init();
    } else if ( ps2x.Button(PSB_PINK) ) {
      polewalk_geton();
    } else if ( ps2x.Button(PSB_RED) ) {
      polewalk();
    } else if ( ps2x.Button(PSB_BLUE) ) {
      polewalk_getoff();
    } else if ( ps2x.ButtonPressed(PSB_R1) ) {
      polewalk_init();
      polewalk_geton();
      polewalk();
      polewalk_getoff();
    }
  }
  if ( ps2x.Button(PSB_PAD_DOWN) ) {
    PC.println("LADDER");
    if ( ps2x.Button(PSB_GREEN) ) {
      ladder_init();
    } else if ( ps2x.Button(PSB_PINK) ) {
      ladder_geton();
    } else if ( ps2x.Button(PSB_RED) ) {
      ladder();
    } else if ( ps2x.Button(PSB_BLUE) ) {
      ladder_getoff();
    } else if ( ps2x.ButtonPressed(PSB_R1) ) {
      ladder_init();
      ladder_geton();
      ladder();
      ladder_getoff();
    }
  }

  // ---------------------------------- SOLENOID ACTUATIONS
  if (ps2x.ButtonPressed(PSB_L2)) {
    l_piston_state = ! l_piston_state;
    if ( l_piston_state ) {
      piston(LEFT, OPEN);
      PC.println(F("Left piston opened"));
    } else {
      piston(LEFT, CLOSE);
      PC.println(F("Left piston closed"));
    }
  }
  if (ps2x.ButtonPressed(PSB_R2)) {
    r_piston_state = ! r_piston_state;
    if ( r_piston_state ) {
      piston(RIGHT, OPEN);
      PC.println(F("Right piston opened"));
    } else {
      piston(RIGHT, CLOSE);
      PC.println(F("Right piston closed"));
    }
  }

  if (ps2x.ButtonPressed(PSB_L3)) {
    l_pp_state = ! l_pp_state;
    if ( l_pp_state ) {
      pp(LEFT, EXTEND);
      PC.println(F("Left PP extended"));
    } else {
      pp(LEFT, SHRINK);
      PC.println(F("Left PP shrunk"));
    }
  }
  if (ps2x.ButtonPressed(PSB_SELECT)) {
    r_pp_state = ! r_pp_state;
    if ( r_pp_state ) {
      pp(RIGHT, EXTEND);
      PC.println(F("Right PP extended"));
    } else {
      pp(RIGHT, SHRINK);
      PC.println(F("Right PP shrunk"));
    }
  }

  // ----------------------------------------- MOTOR MOVEMENT
  if ( ps2x.Button(PSB_R1) && ps2x.Button(PSB_L1) ) { // print stick values if either is TRUE
    if ( ps2x.Analog(PSS_LX) < 65 ) {
      run(LEFT, HOME, 250);
    } else if ( ps2x.Analog(PSS_LX) > 165 ) {
      run(LEFT, MID, 250);
    } else {
      run(LEFT, STOP, 0);
    }

    if ( ps2x.Analog(PSS_RX) > 165 ) {
      run(RIGHT, HOME, 250);   
    } else if ( ps2x.Analog(PSS_RX) < 65 ) {
      run(RIGHT, MID, 250);
    } else {
      run(RIGHT, STOP, 0);
    }
  } else if ( ps2x.Button(PSB_R1) ) { // print stick values if either is TRUE
    if ( ps2x.Analog(PSS_LX) < 65 ) {
      run(LEFT, HOME, 75);   
    } else if ( ps2x.Analog(PSS_LX) > 165 ) {
      run(LEFT, MID, 75);
    } else {
      run(LEFT, STOP, 0);
    }

    if ( ps2x.Analog(PSS_RX) > 165 ) {
      run(RIGHT, HOME, 75);   
    } else if ( ps2x.Analog(PSS_RX) < 65 ) {
      run(RIGHT, MID, 75);
    } else {
      run(RIGHT, STOP, 0);
    }
  } else {
    run(RIGHT, STOP, 0);
    run(LEFT, STOP, 0);
  }
}

