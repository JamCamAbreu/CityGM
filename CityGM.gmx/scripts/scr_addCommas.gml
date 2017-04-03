// build a new string for the money, with commas:

var newString = string(argument0);
var stringSize = string_length(string(argument0));

if (stringSize > 3) {
    newString = string_insert(",", newString, stringSize - 2);
}

if (stringSize > 6) {
    newString = string_insert(",", newString, stringSize - 5);
}

return newString;
