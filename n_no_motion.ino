void AtTarget(void)
{
  switch (state)
  {
    case 1:

      //AimForTarget();

      // ^^^ MOVED so that angle is set before motion starts //TESTING 1: this is where the servo command originally was

      state = 2;
      stateChangeTime = millis();
      break;

    case 2:
      timeSinceLastStateChange = millis() - stateChangeTime;
      if (timeSinceLastStateChange > 10) // basically no pause so it fires while moving? //TESTING 2: tesing shorter delays
      {


        //        digitalWrite(solenoidDirectionPin, HIGH);
        //
        //        analogWrite(solenoidPowerPin, solenoidPower);
        //
        //        PRINT.println(F("Firing solenoid!"));
        state = 3;
        //        stateChangeTime = millis();


      }
      break;

    case 3:
      //      timeSinceLastStateChange = millis() - stateChangeTime;
      //      if (timeSinceLastStateChange > solenoidActivationTime) //TESTING 2: tesing shorter delays - solenoid activation time is delay
      //      {
      //        analogWrite(solenoidPowerPin, 0);
      //        PRINT.println(F("Done firing solenoid!"));

      state = 4;
      //        stateChangeTime = millis();
      //      }
      break;


    case 4:
      //      timeSinceLastStateChange = millis() - stateChangeTime;
      //      if (timeSinceLastStateChange > 10) //TESTING 2: tesing shorter delays
      //      {
      //        launcherServo.write(reloadAngle); //RELOADER NOT WORKING
      //        PRINT.println("Commanding launcher servo to reload angle.");
      //
      state = 5;
      //      }
      break;

    case 5:
      startMotion = 1;
      if (target < 5)
      {
        headed = 2;

      }
      else
      {
        headed = 0;
      }
      PRINT.println(F("Target actions complete. Setting motion variables."));
      //userInput = 'x';
      state = 1;
      break;


  }
}

void AtHome(void)
{
  switch (state)
  {
    case 1:

      digitalWrite(ledPin, HIGH);
      PRINT.println("Starting timer - LED on");
      doneWithStartingStuff = true;

      stateChangeTime = millis();
      state = 2;

      break;

    case 2:

      timeSinceLastStateChange = millis() - stateChangeTime;
      if (timeSinceLastStateChange > 1000) //TESTING 2: tesing shorter delays - this one may need to stay long to make sure timer starts
      {
        digitalWrite(ledPin, LOW);
        PRINT.println(F("Triggering Timer - LED off"));
        state = 3;

      }


      break;

    case 3:

      PRINT.println(F("Setting motion variables"));
      if (target < 5)
      {
        if ((target == 0) && (userInput == 'v'))
        {
          PRINT.println(F("Calling FirstTargetServoAngle()"));
          FirstTargetServoAngle(kappa, lambda, alpha, beta, thetaL0, xTarget0, FirstTargetServoAngleAccuracy);
          //ComputeStuff(computeStuffAccuracy);
          //GetServoAngles(); BANNED :(:(
          //AdjustStripeNum(); //for move while shooting(test later)
        }
        startMotion = 1;
        headed = 1;
        state = 1;

      }
      else
      {
        target = 0;
        state = 0;
        PRINT.println(F("Finished UWUUUUU ;w; ;) bye alex"));
        if (userInput == 'v')
        {
          CODEMESSAGE.println("done");
        }
        userInput = 'x';
      }

      break;

  }
}

void NotMoving(void)
{
  if (leftSwitchState == 1)
  {
    AtHome();

  }
  else if (rightSwitchState == 1)
  {
    AtReloader();

  }
  else if (desiredPosition == counts)
  {
    AtTarget();
  }
}


void AtReloader(void)
{
  switch (state)
  {
    case 1:
      reloaderServo.write(dispenseAngle);
      PRINT.println(F("Dispensing UWU"));
      firstTimeShooting = true;
      firstTimeSolenoid = true;
      state = 2;
      stateChangeTime = millis();
      break;

    case 2:
      startMotion = 1;
      headed = 1;
      target++;
//      timeSinceLastStateChange = millis() - stateChangeTime;
//      if (timeSinceLastStateChange > dispenseDelay)
//      {
//delay(dispenseDelay);
        //reloaderServo.write(holdAngle);
        PRINT.println(F("NOT Hodling UWU"));
        state = 1;
        //stateChangeTime = millis();

//      }
      break;

//    case 3:
//      timeSinceLastStateChange = millis() - stateChangeTime;
//      if (timeSinceLastStateChange > 5) //TESTING 2: tesing shorter delays
//      {
//        startMotion = 1;
//        headed = 1;
//        target++;
//        PRINT.println(F("Ball Reloaded, setting motion variables..."));
//        state = 1;
//      }
//      break;

  }
}
