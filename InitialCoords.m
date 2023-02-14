function [xCoord,yCoord] = InitialCoords(d, thetaL)
d1 = d(1);
d2 = d(2);
d3 = d(3);
xCoord = (d2.*cosd(thetaL))-(d3.*sind(thetaL));
yCoord = d1+(d2.*sind(thetaL))+(d3.*cosd(thetaL));
end
% Nico Scialdone, u1347923, ME EN 1010, HW2b