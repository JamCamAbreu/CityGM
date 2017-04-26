// argument0 = zone level
// argument1 = zone variation
var imageIndex = 0;

if (argument0 < 1)
    imageIndex += argument2; // square position
else 
    imageIndex += 9;

imageIndex += ((argument0)*3);

if (argument0 > 0)
    imageIndex += argument1;

return imageIndex;
