void TestSwitches(void)
{

timeSinceLastPrint = millis() - printTime;

  
// Keep track of previous switch states for comparison

int prevLeftSwitchState = leftSwitchState;
int prevRightSwitchState = rightSwitchState;


// Update the switch state variables

int leftSwitchTempState = digitalRead(leftSwitchPin);
int rightSwitchTempState = digitalRead(rightSwitchPin);


// Left switch debounce code

if (leftSwitchTempState != prevLeftSwitchState)
{
    timeSinceLastLeftSwitchChange = millis() - leftSwitchChangeTime;
    
    if (timeSinceLastLeftSwitchChange > switchDebounceTime)
    
    {
      leftSwitchChangeTime = millis();
      leftSwitchState = leftSwitchTempState;
    }

  
}


// Right switch debounce code

if (rightSwitchTempState != prevRightSwitchState)
{
    timeSinceLastRightSwitchChange = millis() - rightSwitchChangeTime;
    
    if (timeSinceLastRightSwitchChange > switchDebounceTime)
    
    {
      rightSwitchChangeTime = millis();
      rightSwitchState = rightSwitchTempState;
    }

  
}


// If appropriate, print a new message


 if((timeSinceLastPrint > printDelay) || (leftSwitchState != prevLeftSwitchState) || (rightSwitchState != prevRightSwitchState))
      {
        
        printTime = millis();
        
        PRINT.print(F("Left switch is: "));
                PRINT.print(leftSwitchState);

        PRINT.print(F(" ... Right switch is: "));
                PRINT.println(rightSwitchState);
        
      }

    
}
