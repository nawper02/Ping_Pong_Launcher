function [clickedRGB] = ColorPicker(origImage)
figure
image(origImage)
axis image
[clickedCol,clickedRow] = ginput(1)
clickedCol = round(clickedCol);
clickedRow = round(clickedRow);
R = origImage(clickedRow,clickedCol,1);
G = origImage(clickedRow,clickedCol,2);
B = origImage(clickedRow,clickedCol,3);
clickedRGB = [R,G,B];
end
% Nico Scialdone, u1347923, ME EN 1010, HW11b