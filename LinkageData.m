function [thetaS, avethetaL] = LinkageData(filename)
data = readmatrix(filename);
thetaS = data(:,1);
thetaLs = data(:,2:end);
avethetaL = mean(thetaLs, 2);
if (nargout==0)
    plot1 = plot(thetaS,avethetaL, 'ob')
    xlabel('Servomotor Angle [deg]')
    ylabel('Launch Angle [deg]')
    title('Cannon Fourbar Kinematics')
end
end
% Nico Scialdone, u1347923, ME EN 1010, HW8b