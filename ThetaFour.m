function angle4 = ThetaFour(L,theta2)
L1 = L(1);
L2 = L(2);
L3 = L(3);
L4 = L(4);

K1 = L1./L2;
K2 = L1./L4;
K3 = ((L1.^2)+(L2.^2)-(L3.^2)+(L4.^2))./(2.*L2.*L4);

A = cosd(theta2)-K1-(K2.*cosd(theta2))+K3;
B = -2.*sind(theta2);
C = K1 - ((K2+1).*cosd(theta2))+K3;

root = Quadratic(A,B,C,-1);
angle4 = 2.*atand(root);
end
% Nico Scialdone, u1347923, ME EN 1010, HW5a