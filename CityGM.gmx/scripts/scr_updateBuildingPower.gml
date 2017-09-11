var buildingString = argument0;
var buildingElements = argument1;
// argument2 = main function that holds the arrays


var elementsLeft = buildingElements;
var charPos = 1; // start at beginning of string
var value = "";

while (charPos <= string_length(buildingString)) {

    value = string_char_at(buildingString, charPos);

    // value was found (using special chars * for power, - for not enough power:
    if (value == '*' || value == '-') {
        // store power status in array:
        argument2.powerArray[buildingElements - elementsLeft] = string(value);
        elementsLeft--;
    }
    // next element, if exists:
    charPos++;
} // END WHILE
