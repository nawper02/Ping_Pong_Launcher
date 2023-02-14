function [SSE] = CompareLinkageData(params, L, thetaS, expthetaL)
theorthetaL = ThetaLaunch(L,thetaS,params);
a = theorthetaL;
b = expthetaL;
SSE = SumOfSquaredErrors(a,b);
end
% Nico Scialdone, u1347923, ME EN 1010, HW10b