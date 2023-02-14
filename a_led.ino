void TestIRLED(void)
{

  timeSinceLastBlink = millis() - blinkTime;

    if (ledOn == 0)
    {
      
      if(timeSinceLastBlink > ledOffTime)
      {
        digitalWrite(ledPin, HIGH);
        ledOn = 1;
        blinkTime = millis();
        PRINT.println(F("Led is ON"));
      }

    }

      else
      {
        if(timeSinceLastBlink > ledOnTime)
        {
             digitalWrite(ledPin, LOW);
             ledOn = 0;
             blinkTime = millis();
             PRINT.println(F("Led is OFF"));

        }
        
    }
  
}
