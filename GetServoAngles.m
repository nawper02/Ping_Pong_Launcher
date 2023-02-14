function [thetaLWIN,servoAngles] = GetServoAngles(d,optimalVelCoeffs,xTarget_m,H,optimalParams)

[thetaLWIN] = LaunchAngle(d,optimalVelCoeffs,xTarget_m);
[servoAngles] = TargetServoAngles(d, optimalVelCoeffs, H, optimalParams, xTarget_m);

end