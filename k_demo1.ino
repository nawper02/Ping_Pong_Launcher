void Demo1(void)
{
    int prevButtonPressed = buttonPressed;

    ReadButtons();

    switch(buttonPressed)
    {
        case 3:
        case 1:
            timeSinceLastIncrement = millis() - incrementTime;
            if (( buttonPressed != prevButtonPressed )||(timeSinceLastIncrement > 250))
            {
            incrementTime = millis();
                if(buttonPressed==3)
                {
                  target += 1;
                }
                else if(buttonPressed==1)
                {
                  target -= 1;
                }
                target = constrain(target,0,5);
                PRINT.print(F("Target is: "));
                PRINT.println(target);
            }
        break;

        case 4:
        case 2:
            timeSinceLastIncrement = millis() - incrementTime;
            if (( buttonPressed != prevButtonPressed )||(timeSinceLastIncrement > 250))
            {
            incrementTime = millis();
                if(buttonPressed==4)
                {
                  headed -= 1;
                }
                else if(buttonPressed==2)
                {
                  headed += 1;
                }
                headed = constrain(headed,0,2);
                PRINT.print(F("Headed is: "));
                PRINT.println(headed);
            }
        break;

        case 5:
          startMotion = 1;
          state = 1;
        break;

        case 0:
           MoveLauncher();
        break;
   
    }
  
}
