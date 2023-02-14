void ComputeStuff(float accuracy)
{

  float d[] = {0.0400, 0.1583, 0.0553};
  float H[] = {0.1301, 0.0960, 0.0880, 0.0465};

  TargetServoAngles(d, kappa, lambda, H, alpha, beta, thetaL0, xTargetVec, accuracy);
  for (int n = 1; n <= 5; n = n + 1) {
    PRINT.print(F("To hit a target at "));
    PRINT.print(xTargetVec[n], 2);
    PRINT.print(F(" m, command the servo to "));
    PRINT.print(writeToServo[n]);
    PRINT.println(F(" deg"));
  }



}

float Deg2Rad(float angleDeg) {

  float angleRad = angleDeg * M_PI / 180.0;
  return angleRad;

}

float Rad2Deg(float angleRad) {

  float angleDeg = angleRad * 180.0 / M_PI;
  return angleDeg;

}

float Quadratic (float a, float b, float c, int plusOrMinus) { //TESTING 4

  float root = (- b + plusOrMinus * sqrt( b * b - 4 * a * c )) / ( 2 * a );

  return root;

}

float LandingDistance (float d[], float kappa, float lambda, float thetaL) { //TESTING 4
  float thetaLRad = Deg2Rad(thetaL);
  float v0 = kappa + lambda * thetaL;

  float d1 = d[0];
  float d2 = d[1];
  float d3 = d[2];
  float g = 9.81;

  float x0 = d2 * cos(thetaLRad) - d3 * sin(thetaLRad);
  float y0 = d1 + d2 * sin(thetaLRad) + d3 * cos(thetaLRad);
  float v0x = v0 * cos(thetaLRad);
  float v0y = v0 * sin(thetaLRad);

  float a = -0.5 * g;
  float b = v0y;
  float c = y0;
  float plusOrMinus = -1;

  float tLand = Quadratic(a, b, c, plusOrMinus);
  float xLand = x0 + tLand * v0x;

  return xLand;

}

float RangeAngle (float d[], float kappa, float lambda, float accuracy) { //TESTING 4

  float thetaL = 0.00;
  float currentMax = 0;

  while (thetaL <= 90)
  {

    float currentDistance = LandingDistance(d, kappa, lambda, thetaL);

    if (currentDistance > currentMax)
    {
      currentMax = currentDistance;
    }

    else
    {
      return thetaL;
    }

    thetaL = thetaL + accuracy; //True value is almost exactly 1 degree less than accuracy = 0.03.
  }

}

float LaunchAngle(float d[], float kappa, float lambda, float xTarget, float accuracy) { //TESTING 4

  float rangeAngle = RangeAngle(d, kappa, lambda, accuracy);
  float thetaL = rangeAngle;
  float landingDistance = LandingDistance(d, kappa, lambda, thetaL);

  while (landingDistance >= xTarget)
  {

    landingDistance = LandingDistance(d, kappa, lambda, thetaL);
    thetaL = thetaL + accuracy; //True value is almost exactly 1 degree less than accuracy = 0.03.

  }

  return thetaL;

}

float ThetaServo(float H[], float thetaL, float alpha, float beta, float thetaL0) //TESTING 4
{

  float thetaLRad = Deg2Rad(thetaL);
  float alphaRad = Deg2Rad(alpha);
  float thetaL0Rad = Deg2Rad(thetaL0);

  float k1 = H[0] / H[1];
  float k2 = H[0] / H[3];
  float k3 = (  H[0] * H[0] + H[1] * H[1] + H[3] * H[3] - H[2] * H[2] ) / ( 2 * H[1] * H[3] );

  float theta2 = thetaLRad - thetaL0Rad;

  float A = cos(theta2) - k1 - k2 * cos(theta2) + k3;
  float B = -2 * sin(theta2);
  float C = k1 - (k2 + 1) * cos(theta2) + k3;

  float quadResult = Quadratic(A, B, C, -1);
  float theta4 = 2 * atan(quadResult);

  float thetaS = (theta4 + alphaRad) / (1 - beta);

  float thetaSDeg = Rad2Deg(thetaS);
  return thetaSDeg;

}

void TargetServoAngles(float d[], float kappa, float lambda, float H[], float alpha, float beta, float thetaLO, float xTargetVec[], float accuracy) {
  
  float launchVec[6];
  float servoVec[6];
  
  for  (int i = 1; i < 6; i++) {
    PRINT.print(F("Computing target "));
    PRINT.println(i);

    launchVec[i] = LaunchAngle(d, kappa, lambda, xTargetVec[i], accuracy);
    servoVec[i] = ThetaServo(H, launchVec[i], alpha, beta, thetaLO);
    writeToServo[i] = int(round(servoVec[i]));

    PRINT.print(F("xTarget [m] = "));
    PRINT.print(xTargetVec[i]);
    PRINT.print(F(" --> thetaL [deg] = "));
    PRINT.print(launchVec[i]);
    PRINT.print(F(" --> thetaS [deg] = "));
    PRINT.print(servoVec[i]);
    PRINT.print(F(" --> Rounded thetaS [deg] = "));
    PRINT.println(writeToServo[i]);
  }
  
}

void FirstTargetServoAngle(float kappa, float lambda, float alpha, float beta, float thetaLO, float xTarget0, float accuracy) {
  float d[] = {0.0400, 0.1583, 0.0553};
  float H[] = {0.1301, 0.0960, 0.0880, 0.0465};
  
  float firstLaunchAngle;
  float firstServoAngle;
  
  PRINT.print(F("Computing target "));
  PRINT.println(0);

  firstLaunchAngle = LaunchAngle(d, kappa, lambda, xTarget0, accuracy);
  firstServoAngle = ThetaServo(H, firstLaunchAngle, alpha, beta, thetaLO);
  writeToServo[0] = int(round(firstServoAngle));

  PRINT.print(F("xTarget [m] = "));
  PRINT.print(xTargetVec[0]);
  PRINT.print(F(" --> thetaL [deg] = "));
  PRINT.print(firstLaunchAngle);
  PRINT.print(F(" --> thetaS [deg] = "));
  PRINT.print(firstServoAngle);
  PRINT.print(F(" --> Rounded thetaS [deg] = "));
  PRINT.println(writeToServo[0]);

}
