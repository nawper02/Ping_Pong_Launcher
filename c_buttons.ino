void ReadButtons(void)
{

// Keep track of the previous button number

int prevButtonNumber = buttonNumber;

// Read the button value

int buttonValue;

buttonValue = analogRead(buttonPin);

// Determine the button number that corresponds to the button value

if ((buttonValue < 5))
{
    buttonNumber = 1;
    
}

else if ((buttonValue > 115) && (buttonValue < 175))
{
    buttonNumber = 2;

}

else if ((buttonValue > 305) && (buttonValue < 365))
{
    buttonNumber = 3;

}

else if ((buttonValue > 480) && (buttonValue < 540))
{
    buttonNumber = 4;

}

else if ((buttonValue > 715) && (buttonValue < 775))
{
    buttonNumber = 5;

}


else if ((buttonValue > 1015))
{
    buttonNumber = 0;

}

else
{
    buttonNumber = -1;

}

// Determine if the button number is an actual button press or a bounce

if (buttonNumber == prevButtonNumber)
{
  cibn++;
    if (cibn > 100)
    {
      buttonPressed = buttonNumber;
    }
  
}

else
{
  cibn = 0;
}
  
}

void TestButtons(void)
{

// Keep track of the previously pressed button

int prevButtonPressed = buttonPressed;

// Check what button is currently pressed

ReadButtons();

// If appropriate, print a new message

timeSinceLastPrint = millis() - printTime;

if((timeSinceLastPrint > printDelay) || (buttonPressed != prevButtonPressed))
{
  printTime = millis();
  switch(buttonPressed)
  {
    case 3:
        PRINT.print(F("UP button is pressed\n"));
    break;
    
    case 1:
        PRINT.print(F("DOWN button is pressed\n"));
    break;
    
    case 4:
        PRINT.print(F("LEFT button is pressed\n"));
    break;
    
    case 2:
        PRINT.print(F("RIGHT button is pressed\n"));
    break;
    
    case 5:
        PRINT.print(F("SELECT button is pressed\n"));
    break;
    
    case 0:
        PRINT.print(F("NO button is pressed\n"));
    break;
    
    default:
        PRINT.print(F("You're a dumbass (somehow)\n"));
    break;
    
  }
  
}

      
}
