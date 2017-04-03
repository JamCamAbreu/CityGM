var commaCount = 0; // possible to reach 99,999,999
var stringLength = string_length(string(argument0));

if (stringLength > 3)
    commaCount++;
    
if (stringLength > 6)
    commaCount++;
    
return commaCount;
