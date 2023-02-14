function VecthetaL = LaunchAngle(d,velCoeffs,xTarget)
tempthetaL = 90;
for (k = [1:length(xTarget)])
    newxTarget = xTarget(k);
[range,rangeAngle] = ProjectileRange2(d,velCoeffs);
xland = LandingDistance(d,velCoeffs,tempthetaL);
while ((xland<newxTarget)&(tempthetaL>rangeAngle))
    tempthetaL = tempthetaL -.01;
    xland = LandingDistance(d,velCoeffs,tempthetaL);
end
thetaL = tempthetaL;
VecthetaL(k) = thetaL + 0.01;
end
% Nico Scialdone, u1347923, ME EN 1010, HW9a