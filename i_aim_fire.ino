void TestAimFire (void)
{

  int prevButtonPressed = buttonPressed;
  ReadButtons();


switch (buttonPressed)
{

  case 3:
      
    
  case 1:
      
    
  case 4: 


  case 2: 
    switch (buttonPressed)
    {
      case 3:
      servoAngleIncrement = 5;

      break;

      case 1:
      servoAngleIncrement = -5;

      break;

      case 4:
      servoAngleIncrement = -1;

      break;

      case 2:
      servoAngleIncrement = 1;

      break;

    }
    timeSinceLastIncrement = millis() - incrementTime;

    //readButtons(); ?

    if((prevButtonPressed != buttonPressed) || (timeSinceLastIncrement > 250))
    {
      incrementTime = millis();
      desiredServoAngle = desiredServoAngle + servoAngleIncrement;
      desiredServoAngle = constrain(desiredServoAngle,0,180);

      PRINT.print(F("New desired servo angle is : "));
      PRINT.println(desiredServoAngle);
    }

  
    break;
    
  case 5: 
   if((prevButtonPressed != buttonPressed))
    {
        if(state>0)
        {
            PRINT.println(F("The previous aim/fire sequence is still in progress"));
          
        }
        else
        {
          state = 1;
          stateChangeTime = millis();
          
        }
      
    }
  
  break;
  case 0: 

    
  break;

  default:
   
  break;
    
}


switch(state)
{
  case 1:
  // delay, then command the servo  
  timeSinceLastStateChange = millis() - stateChangeTime;

        if (timeSinceLastStateChange > 1000)
        {
            // command the servo
              launcherServo.write(desiredServoAngle);
          
              PRINT.print(F("Launcher servo commanded to "));
              PRINT.println(desiredServoAngle);
          
            // change the state, update the time
              state = 2;
              stateChangeTime = millis();
      
        }


  case 2: // delay, then turn the solenoid on

    timeSinceLastStateChange = millis() - stateChangeTime;
    if (timeSinceLastStateChange > 1000)
    {

        digitalWrite(solenoidDirectionPin, HIGH);

        analogWrite(solenoidPowerPin, solenoidPower);

        PRINT.println(F("Firing solenoid!"));

        state = 3;

        stateChangeTime = millis();

    }

  break;

  case 3:
    // delay, then turn the solenoid off

    timeSinceLastStateChange = millis() - stateChangeTime;
    if(timeSinceLastStateChange > solenoidActivationTime)
    {

          analogWrite(solenoidPowerPin, 0);
          PRINT.println(F("Done firing..."));

          state = 0;
    }

  break;
  
}
}
