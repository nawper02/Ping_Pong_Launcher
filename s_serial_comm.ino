void GetDataFromMatlab(void)
{
  CODEMESSAGE.println("ready for data");
  PRINT.println(F("Getting data from MATLAB"));

  for (target = 0; target <= 5; target++)
  {
    String dataString1 = Serial.readStringUntil('\n');
    String dataString2 = Serial.readStringUntil('\n');
    int stripeComm = dataString1.toInt();
    float xTargetComm = dataString2.toFloat();

    driveTo[target] = stripeComm;
    xTargetVec[target] = xTargetComm;

    PRINT.print(F("Target "));
    PRINT.print(target);
    PRINT.print(F(" ---> Drive to stripe "));
    PRINT.print(driveTo[target]);
    PRINT.print(F(" and aim for "));
    PRINT.print(xTargetVec[target], 4);
    PRINT.println(F(" m."));
  }
  target = 0;
  xTarget0 = xTargetVec[0];
  AdjustStripeNum();

  //get linkage params from MATLAB

  String paramString;
  paramString = Serial.readStringUntil('\n');
  alpha = paramString.toFloat();

  paramString = Serial.readStringUntil('\n');
  beta = paramString.toFloat();

  paramString = Serial.readStringUntil('\n');
  thetaL0 = paramString.toFloat();
  
  PRINT.print(F("Alpha: "));
  PRINT.print(alpha,3);
  PRINT.print(F("; Beta: "));
  PRINT.print(beta,3);
  PRINT.print(F("; ThetaL0: "));
  PRINT.println(thetaL0,3);

  String coeffString;
  coeffString = Serial.readStringUntil('\n');
  kappa = coeffString.toFloat();

  coeffString = Serial.readStringUntil('\n');
  lambda = coeffString.toFloat();
  
  PRINT.print(F("Kappa: "));
  PRINT.print(kappa,4);
  PRINT.print(F("; Lambda: "));
  PRINT.println(lambda,4);

}
