function [xVelocity,yVelocity] = InitialVelocityComponents(v0,thetaL)
xVelocity = v0.*cosd(thetaL);
yVelocity = v0.*sind(thetaL);
end
% Nico Scialdone, u1347923, ME EN 1010, HW2b