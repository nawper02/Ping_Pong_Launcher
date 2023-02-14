function [SSE] = CompareProjectileData(velCoeffs,d,thetaL,eXland)
xland = LandingDistance(d,velCoeffs,thetaL);
SSE = SumOfSquaredErrors(xland,eXland);
end
% Nico Scialdone, u1347923, ME EN 1010, HW9b