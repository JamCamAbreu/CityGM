// argument0 = id holding all the variables








var elementsLeft = buildingElements;
var charPos = 1; // start at beginning of string
var parseString = "";
while (elementsLeft) {
    // reset string for each element:
    parseString = "";
    // add each VALID char to parseString:
    var char = string_char_at(buildingString, charPos);
    while (char != ',') {
        parseString += char;
        charPos++;
        char = string_char_at(buildingString, charPos);
    }

    // store actual decimal value in array:
    argument2.xArray[buildingElements - elementsLeft] = real(parseString);

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
