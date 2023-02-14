function [range,rangeAngle] = ProjectileRange2(d,velCoeffs)
thetaL = 0;
range = 0;
rangeAngle = 0;
for (k = [0:0.01:90])
    xland = LandingDistance(d,velCoeffs,k); %compute xland
    if (xland > range) 
    range = xland; %overwrites range if xland is bigger
    rangeAngle = k; 
    end
end
% Nico Scialdone, u1347923, ME EN 1010, HW6b