void TestReloader(void)
{
int prevButtonPressed = buttonPressed;
ReadButtons();

  switch(buttonPressed){
  
    case 5://SELECT
        if(prevButtonPressed!=buttonPressed)
        {
          if(state>0)
          {
            PRINT.println(F("Reloading"));
          }
          else
          {
            state = 1;
          }
          
        }
        break;
    }

    switch(state)
    {
          case 1:  
            reloaderServo.write(dispenseAngle);
            PRINT.println(F("Dispensing"));
            state = 2;
            stateChangeTime = millis();
          break;

          
          case 2: 
            timeSinceLastStateChange = millis() - stateChangeTime;
            if (timeSinceLastStateChange > dispenseDelay)
            {
              reloaderServo.write(holdAngle);
              PRINT.println(F("Holding"));
              state = 0;
            }
          break;
           
    }

}
