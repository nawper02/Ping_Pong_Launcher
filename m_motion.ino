void MoveLauncher(void)
{

  //DebugPrint("Calling Demo1 function; startMotion = ", startMotion);

  if (motorOn)
  {
    Moving();
  }
  else
  {
    if (startMotion)
    {
      PreparingToMove();
    }
    else
    {
      NotMoving();
    }

  }

}


void PreparingToMove(void)
{
  // set desiredPosition

  if ((userInput == 'k') || (userInput == 'v'))
  {
    switch (headed)
    {
      case 0:
        leftSwitchState = digitalRead(leftSwitchPin);
        if (leftSwitchState == 1)
        {
          PRINT.println("Already home...");
          counts = 5;
          desiredPosition = 5;
          startMotion = 0;
          headed = 1;
        }
        else
        {
          PRINT.println("Headed home...");
          desiredPosition = -69;
        }
        break;

      case 1:
        //aimTime = millis();
        //AimForTarget(); //TESTING 1

        desiredPosition = driveTo[target];
        break;

      case 2:
        desiredPosition = 69;
        break;

    }
  }


  // set motorRight

  if (desiredPosition > counts)
  {
    motorRight = 1;
  }
  else
  {
    motorRight = 0;
  }



  // turn motor on

  if (counts != desiredPosition)
  {
    TurnMotorOn();
    startMotion = 0;
  }

}

void Moving(void)
{

  // count stripes

  CountStripes();

  // stop at target

  if ((target == 0) && (counts == 6) && (firstTimeShooting) && (doneWithStartingStuff))
  {
    PRINT.print("Setting firstitmesbooting to false");
    AimForTarget();
    firstTimeShooting = false;
  }

  if ((counts == desiredPosition)) //&& (firstTimeSolenoid))
  {
    //TurnMotorOff(25); //TESTING 5: dont turn motor off when get to target, just keep going?
    CountStripes();
    PRINT.print(F("Launcher at stripe: "));
    PRINT.println(counts);
    ForceFire();
    //firstTimeSolenoid = false;
    CountStripes();

    startMotion = 1;
      if (target < 5)
      {
        headed = 2;

      }
      else
      {
        headed = 0;
      }
  }

  CountStripes();
  if ((counts == (driveTo[0]+1)) && (headed == 2) && (firstTimeCompute))
  {
    ComputeStuff(computeStuffAccuracy);
    firstTimeCompute = false;
  }

  if ((counts == 37) && (desiredPosition < 48) && (firstTimeShooting))
  {
    AimForTarget();
    reloaderServo.write(holdAngle);
    firstTimeShooting = false;

  }

  if (headed == 2)    //((counts == 34) && (desiredPosition > 48))
  {
    launcherServo.write(reloadAngle);

  }


  // read switches

  leftSwitchState = digitalRead(leftSwitchPin);
  rightSwitchState = digitalRead(rightSwitchPin);

  // stop at home (moving left, left switch tripped)

  if ((!motorRight) && (leftSwitchState == 1))
  {
    TurnMotorOff(25);
    CountStripes();
    counts = 5;
    PRINT.println(F("Launcher at home - counts set to 5"));
  }

  // stop at reloader (moving right, right switch tripped)

  if ((motorRight) && (rightSwitchState == 1))
  {
    TurnMotorOff(25);
    CountStripes();
    counts = 43;
    PRINT.println(F("Launcher at reloader - counts set to 43"));
  }


}
