var placeHolders = "..."; // possible to reach 99,999,999
var stringLength = string_length(string(argument0));

for (numDigits = 8; numDigits > 1; numDigits--) {
    if (stringLength < numDigits)
        placeHolders += ".";
}

var commaCount = scr_CommaCount(argument0);
    
// get rid of place holders to fit comma's:
placeHolders = string_delete(placeHolders, 1, commaCount); // it's all just the same character, so start at pos 1
    
return placeHolders;
