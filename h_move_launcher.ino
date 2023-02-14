void TestMoveLauncher(void)
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
  case 4:

  case 2:

   timeSinceLastIncrement = millis() - incrementTime;
    if (( buttonPressed != prevButtonPressed )||(timeSinceLastIncrement > 250))
    {
      incrementTime = millis();
      if(buttonPressed == 4)
      {
        desiredPosition--;
      }
      else if(buttonPressed == 2)
      {
        desiredPosition++;
      }
      PRINT.print(F("Desired position: "));
      PRINT.println(desiredPosition);
    }

  break;
  case 5:
    startMotion = 1;
  break;
  case 0:
    MoveLauncher();
  break;
  default:
  //nothing
  break;
  

  }
}
