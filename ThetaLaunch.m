function ThetaL = ThetaLaunch(L,thetaS,params)
thetaSC = params(1) + (params(2).*thetaS);
theta2 = 180 - thetaS + thetaSC;
angle4 = ThetaFour(L,theta2);
ThetaL = 180 - angle4 + params(3);
if (nargout == 0)
    plot1 = plot(thetaS, ThetaL)
    title('Cannon Fourbar Kinematics')
    xlabel('Servomotor Angle [deg]')
    ylabel('Launch Angle [deg]')
end
end
% Nico Scialdone, u1347923, ME EN 1010, HW8b