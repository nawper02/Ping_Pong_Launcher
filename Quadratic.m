function root = Quadratic(a,b,c,plusOrMinus)
if ((b.^2-4.*a.*c)>=0);
root = ((-1.*b)+(plusOrMinus.*sqrt(b.^2-4.*a.*c)))./(2.*a);
else
    error(Quadratic);
end
% Nico Scialdone, u1347923, ME EN 1010, HW5b