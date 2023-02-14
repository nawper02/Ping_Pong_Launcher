function [servoAngles] = TargetServoAngles(d, optimalVelCoeffs, H, params, xTargetVec) 

  launchVec = LaunchAngle(d, optimalVelCoeffs, xTargetVec);
  servoVec = ThetaServo(H, launchVec, params);
  servoAngles = round(servoVec);
    
end