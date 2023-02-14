//void GetServoAngles(void) GOT BANNED :(:(:( can't use
//{
//  String thetaSString;
//  for (int i = 0; i < 6; i++)
//  {
//    thetaSString = Serial.readStringUntil('\n');
//    writeToServo[i] = thetaSString.toInt();
//    PRINT.print(F("Servo Angle: "));
//    PRINT.println(writeToServo[i]);
//  }
//
//}

void AdjustStripeNum(void) //TESTING 3: target offsets to shoot while moving
{
  if (xTargetVec[0] >= 1)
  {
    driveTo[0] -= 2;
  }
  else
  {
    driveTo[0] -= 2; //was 1
  }

  for (int i = 1; i < 5; i++)
  {
    if (xTargetVec[i] >= 1)
    {
      driveTo[i] += 2;
    }
    else
    {
      driveTo[i] += 2; //was 1
    }
  }


}

void AimForTarget(void)
{
  //  currAimTime = millis() - aimTime;
  //  if(aimTime > 1000)
  //  {
  desiredServoAngle = writeToServo[target];
  launcherServo.write(desiredServoAngle);
  PRINT.print(F("Commanding launcher servo to "));
  PRINT.print(desiredServoAngle);
  PRINT.print(F(" for target "));
  PRINT.println(target);
  //  }

}

float sqrt3(const float x)
{
  union
  {
    int i;
    float x;
  } u;

  u.x = x;
  u.i = (1 << 29) + (u.i >> 1) - (1 << 22);
  return u.x;
}

void ForceFire(void)
{

  digitalWrite(solenoidDirectionPin, HIGH);

  analogWrite(solenoidPowerPin, solenoidPower);

  PRINT.println(F("Firing solenoid!"));

  if ((target != 0) && (headed = 2))
  {
    if (target != 5)
    {
      delay(55);

      PRINT.print("should start going right");

      TurnMotorOff(25);
      motorRight = 1;
      TurnMotorOn();
    }
  }
  delay(solenoidActivationTime);
  analogWrite(solenoidPowerPin, 0);
  PRINT.println(F("Done firing solenoid!"));


}


//thetaSString = Serial.readStringUntil('\n');
//  int thetaSTarget1 = thetaSString.toInt();
//
//  thetaSString = Serial.readStringUntil('\n');
//  int thetaSTarget2 = thetaSString.toInt();
//
//  thetaSString = Serial.readStringUntil('\n');
//  int thetaSTarget3 = thetaSString.toInt();
//
//  thetaSString = Serial.readStringUntil('\n');
//  int thetaSTarget4 = thetaSString.toInt();
//
//  thetaSString = Serial.readStringUntil('\n');
//  int thetaSTarget5 = thetaSString.toInt();
//
//  thetaSString = Serial.readStringUntil('\n');
//  int thetaSTarget6 = thetaSString.toInt();
//
//  PRINT.print(F("Servo Angle 1: "));
//  PRINT.print(thetaSTarget1);
//  PRINT.print(F("; Servo Angle 2: "));
//  PRINT.print(thetaSTarget2);
//  PRINT.print(F("; Servo Angle 3: "));
//  PRINT.println(thetaSTarget3);
//  PRINT.print(F("Servo Angle 4: "));
//  PRINT.print(thetaSTarget4);
//  PRINT.print(F("; Servo Angle 5: "));
//  PRINT.print(thetaSTarget5);
//  PRINT.print(F("; Servo Angle 6: "));
//  PRINT.println(thetaSTarget6);

//  int cloneWriteToServoWIN[] = {thetaSTarget1,thetaSTarget2,thetaSTarget3,thetaSTarget4,thetaSTarget5,thetaSTarget6};
//  for(int i = 0; i < 6; i++)
//  {
//    writeToServo[i] = cloneWriteToServoWIN[i];
//  }
//}
