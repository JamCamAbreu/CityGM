// argument0 = buildingString;
// argument1 = buildingElements;
// argument2 = main function that holds the arrays

/*

var sprite;
var xCoord;
var yCoord;
var type;


  
// process x:
scr_updateBuildingX(argument0, argument1, argument2);
//show_message("done process x");

// process y:
scr_updateBuildingY(argument0, argument1, argument2);
//show_message("done process y");

// process power:
scr_updateBuildingPower(argument0, argument1, argument2);
//show_message("done process power");

// process type:
scr_updateBuildingType(argument0, argument1, argument2);
//show_message("done process type and all");



*/






  /*  EXAMPLE STRING:
  Psuedo:
    myBuildingString = "x,y,power,type;x,y,power,type; ... etc"

  Actual:
    myBuildingString = "3,15,*,2;22,9,-,3; ... etc"
  */








var buildingString = DLL_buildingsToString();
var buildingElements = DLL_getBuildingVectorSize();
var elementsLeft = buildingElements;

var curArrayIndex = 0;
var curCharIndex = 1; // because how game maker strings work lol
var curChar;
var parseString;

while (elementsLeft > 0) {

    // reset string for each piece of data:
    parseString = "";
    // add each VALID char to parseString:
    curChar = string_char_at(buildingString, curCharIndex);
    
    // GET X VALUE:
    while (curChar != 'X') {
        curCharIndex++;
        curChar = string_char_at(buildingString, curCharIndex);
    }
    
    // now we are at 'X', we need to get the info AFTER it:
    curCharIndex++;
    curChar = string_char_at(buildingString, curCharIndex);
    
    // get ALL of the characters needed from this data:
    while (curChar != 'Y') {
        parseString += curChar;
        curCharIndex++;
        curChar = string_char_at(buildingString, curCharIndex);
    }
    
    // add parseString to the xArray passed in:  
    argument0.xArray[buildingElements - elementsLeft] = real(parseString);

    
    
    // GET Y VALUE:
    // reset string for each piece of data:
    parseString = "";
    
    // we are currently at 'Y', so we need what comes after  that:
    curCharIndex++;
    curChar = string_char_at(buildingString, curCharIndex);
    
    // get ALL of the characters needed from this data:
    while (curChar != 'E') {
        parseString += curChar;
        curCharIndex++;
        curChar = string_char_at(buildingString, curCharIndex);
    }
    
    // add parseString to the yArray passed in:
    argument0.yArray[buildingElements - elementsLeft] = real(parseString);
    
    

    // ELECTRICITY value:
    // reset string for each piece of data:
    parseString = "";
    
    // we are currently at 'E', so we need what comes after  that:
    curCharIndex++;
    curChar = string_char_at(buildingString, curCharIndex);
    
    // get ALL of the characters needed from this data:
    while (curChar != 'P') {
        parseString += curChar;
        curCharIndex++;
        curChar = string_char_at(buildingString, curCharIndex);
    }
    
    // add parseString to the yArray passed in:
    argument0.powerArray[buildingElements - elementsLeft] = parseString;
    
    
    
    
    
    // PLINE value:
    // reset string for each piece of data:
    parseString = "";
    
    // we are currently at 'P', so we need what comes after  that:
    curCharIndex++;
    curChar = string_char_at(buildingString, curCharIndex);
    
    // get ALL of the characters needed from this data:
    while (curChar != 'T') {
        parseString += curChar;
        curCharIndex++;
        curChar = string_char_at(buildingString, curCharIndex);
    }
    
    // add parseString to the yArray passed in:
    argument0.pLineValueArray[buildingElements - elementsLeft] = real(parseString);
    
    
    
    
    // BUILDING TYPE value:
    // reset string for each piece of data:
    parseString = "";
    
    // we are currently at 'T', so we need what comes after that:
    curCharIndex++;
    curChar = string_char_at(buildingString, curCharIndex);
    
    // get ALL of the characters needed from this data:
    while (curChar != ';') {
        parseString += curChar;
        curCharIndex++;
        curChar = string_char_at(buildingString, curCharIndex);
    }
    
    // add parseString to the yArray passed in:
    argument0.typeArray[buildingElements - elementsLeft] = real(parseString);
    
    // FINAL STEP
    // move to next element:
    elementsLeft--;
    curCharIndex++;
}









