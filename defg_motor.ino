void TestMotor(void) //Uses LEFT/RIGHT buttons to move the launcher left/right along the linear stage
{
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  
  switch(buttonPressed)
  {

    case 3: //up

    timeSinceLastIncrement = millis() - incrementTime;
    if (( buttonPressed != prevButtonPressed )||(timeSinceLastIncrement > 250))
    {
      incrementTime = millis();
      if(buttonPressed == 3)
      {
        counts++;
      }
      else if(buttonPressed == 1)
      {
        counts--;
      }
      PRINT.print(F("Counts: "));
      PRINT.println(counts);
    }
    
    case 1: //down

    timeSinceLastIncrement = millis() - incrementTime;
    if (( buttonPressed != prevButtonPressed )||(timeSinceLastIncrement > 250))
    {
      incrementTime = millis();
      if(buttonPressed == 3)
      {
        counts++;
      }
      else if(buttonPressed == 1)
      {
        counts--;
      }
      PRINT.print(F("Counts: "));
      PRINT.println(counts);
    }
    break;
    
    case 4: //left - Drive the launcher to the left

      motorRight = 0;
      TurnMotorOn();

    break;
    
    case 2: //right - Drive the launcher to the right

      motorRight = 1;
      TurnMotorOn();

    break;
    
    case 5: //select

    counts = counts * (counts == 24) + 24 * (counts != 24);

    timeSinceLastIncrement = millis() - incrementTime;
    if (( buttonPressed != prevButtonPressed )||(timeSinceLastIncrement > 250))
    {
      incrementTime = millis();
     
      PRINT.print(F("Counts is: "));
      PRINT.println(counts);
    }

    break;
    
    case 0: //no - Turn the motor off

      TurnMotorOff(25);
      if(userInput == 'g')
      {
        CountStripes();
      }

    break;
    
    default:

    break;
    
  }
  
ReadButtons();

if (motorOn == 1)
{
  
  switch(userInput)
  {
    case 'd': 

       PrintLeftRight();

    break;
    
    case 'e': 

       PrintSensorValue();

    break;
    
    case 'f': 

        PrintBlackWhite();

    break;
    
    case 'g':

        CountStripes();

    break;

    
    default:

    break;
    
  }
  
}

  
  
}

void PrintLeftRight(void) //Prints "Launcher is moving LEFT" or "Launcher is moving RIGHT" as appropriate. It should only print every printDelay milliseconds and should NOT call delay()!
{

    timeSinceLastPrint = millis() - printTime;
        if (timeSinceLastPrint > printDelay)
            {

                printTime = millis();
                
                PRINT.print(F("Launcher is moving: "));
                
                if (motorRight == 1)
                {
                  PRINT.println(F("RIGHT"));
                }
                
                else
                {
                  PRINT.println(F("LEFT"));
                }
  
            }


}


void PrintSensorValue (void) //COMP TESTING
{

    irSensorValue = analogRead(irSensorPin);

    
      timeSinceLastPrint = millis() - printTime;
        if (timeSinceLastPrint > 50)
            {
                printTime = millis();
                
                PRINT.print(F("Sensor value is: "));
                PRINT.println(irSensorValue);
  
            }

}

void PrintBlackWhite(void)
{
  
    bool prevBlack = black;
    black = GetEncoderBoolean();

    if (prevBlack != black)
    {

      if (black == 0)
      {
        PRINT.println(F("Over White"));
      }

      else if(black == 1)
      {
         PRINT.println(F("Over Black"));
      }
      
    }
    
  
}
