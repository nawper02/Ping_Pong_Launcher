function xland = LandingDistance(d,velCoeffs,thetaL)
k = velCoeffs(1);
greekL = velCoeffs(2);
v0 = k + (greekL.*thetaL);
d1 = d(1);
d2 = d(2);
d3 = d(3);
g = -9.81;
[xCoord,yCoord] = InitialCoords(d,thetaL);
[xVelocity,yVelocity] = InitialVelocityComponents(v0,thetaL);
root = Quadratic(g/2,yVelocity,yCoord,-1);
xland = xCoord + xVelocity.*root; %compute xland
if (nargout == 0)
    plot1 = plot(thetaL, xland, '-r')
    xlabel('Launch Angle [deg]')
    ylabel('Horizontal Distance Traveled [m]')
    title('Ping Pong Ball Projectile Data')
end
end
% Nico Scialdone, u1347923, ME EN 1010, HW7