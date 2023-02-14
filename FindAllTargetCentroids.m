function [centroidRowVec, centroidColVec, imageArray] = FindAllTargetCentroids(imageArray,targetRGB)
for (i=1:6)
    [centroidRow,centroidCol, imageArray] = FindTargetCentroid(imageArray,targetRGB);
    centroidRowVec(i) = centroidRow;
    centroidColVec(i) = centroidCol;
end
end