var buildingString = argument0;
var buildingElements = argument1;
// argument2 = main function that holds the arrays


var elementsLeft = buildingElements;
var charPos = 1; // start at beginning of string
var parseString = "";
while (elementsLeft) {
    // reset string for each element:
    parseString = "";
    // add each VALID char to parseString:
    var char = string_char_at(buildingString, charPos);
    
    // find the first comma:
    for (j = 1; j <= 2; j++) {
        while (char != ',') {
            if (j == 2) // second position
                parseString += char;
            charPos++;
            char = string_char_at(buildingString, charPos);
        }
        
        // next piece of data:
        charPos++;
        char = string_char_at(buildingString, charPos);
    }

    // store actual decimal value in array:
    argument2.yArray[buildingElements - elementsLeft] = real(parseString);

    // NEXT ELEMENT ---------------------------
    // get position of next element:
    while (char != ';') {
        charPos++;
        char = string_char_at(buildingString, charPos);
    }
    // one more:
    charPos++;
    
    // next element, if exists:
    elementsLeft--;
}
