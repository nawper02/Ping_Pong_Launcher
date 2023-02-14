function [launchAngle, aveDist] = ProjectileData(filename)
data = readmatrix(filename);
launchAngle = data(:,1);
distances = data(:,2:end);
aveDistCM = mean(distances,2);
aveDist = aveDistCM ./100;
if (nargout==0)
    plot1 = plot(launchAngle,aveDist, 'ob')
    xlabel('Launch Angle [deg]')
    ylabel('Horizontal Distance Traveled [m]')
    title('Ping Pong Ball Projectile Data')
end
end
% Nico Scialdone, u1347923, ME EN 1010, HW7