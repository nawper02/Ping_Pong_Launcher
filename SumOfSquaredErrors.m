function SSE = SumOfSquaredErrors(a,b)
errors = a-b;
sqaurerrors = errors.^2;
SSE = sum(sqaurerrors);
end
% Nico Scialdone, u1347923, ME EN 1010, HW7