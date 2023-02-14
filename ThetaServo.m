function [thetaS] = ThetaServo(H,thetaL,params)
alpha = params(1);
beta = params(2);
thetaLO = params(3);
theta2 = thetaL - thetaLO;
angle4 = ThetaFour(H,theta2);
thetaS = (angle4+alpha)./(1-beta);
end
% Team 8 function