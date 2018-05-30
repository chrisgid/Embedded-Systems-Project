function [vectorX, vectorY] = angletovector(hyp, angle)
%Converts angle in degrees & magnitude to X & Y vector

radians = pi/180 * angle;

vectorX = cos(radians) * hyp;
vectorY = sin(radians) * hyp;

return