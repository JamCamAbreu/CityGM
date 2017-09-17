// argument0 = main function that holds the arrays


  /*  EXAMPLE STRING:
  Psuedo:
    myBuildingString = "x,y,power,type;x,y,power,type; ... etc"

  Actual:
    myBuildingString = "3,15,*,2;22,9,-,3; ... etc"
  */
  

var roadString = DLL_roadsToString();
var roadElements = DLL_getRoadsVectorSize();
var elementsLeft = roadElements;

var curArrayIndex = 0;
var curCharIndex = 1;
var curChar;
var parseString;



while (elementsLeft > 0) {

    // reset string for each piece of data:
    parseString = "";
    // add each VALID char to parseString:
    curChar = string_char_at(roadString, curCharIndex);
    
    while (curChar != 'X') {
        curCharIndex++;
        curChar = string_char_at(roadString, curCharIndex);
    }
    
    // now we are at 'X', we need to get the info AFTER it:
    curCharIndex++;
    curChar = string_char_at(roadString, curCharIndex);
    
    // get ALL of the characters needed from this data:
    while (curChar != 'Y') {
        parseString += curChar;
        curCharIndex++;
        curChar = string_char_at(roadString, curCharIndex);
    }
    
    // add parseString to the xArray passed in:  
    argument0.roadXArray[roadElements - elementsLeft] = real(parseString);

    
    
    // GET Y VALUE:
    // reset string for each piece of data:
    parseString = "";
    
    // we are currently at 'Y', so we need what comes after  that:
    curCharIndex++;
    curChar = string_char_at(roadString, curCharIndex);
    
    // get ALL of the characters needed from this data:
    while (curChar != 'T') {
        parseString += curChar;
        curCharIndex++;
        curChar = string_char_at(roadString, curCharIndex);
    }
    
    // add parseString to the yArray passed in:
    argument0.roadYArray[roadElements - elementsLeft] = real(parseString);
    
    
    
    
    // TYPE value:
    // reset string for each piece of data:
    parseString = "";
    
    // we are currently at 'T', so we need what comes after that:
    curCharIndex++;
    curChar = string_char_at(roadString, curCharIndex);
    
    // get ALL of the characters needed from this data:
    while (curChar != ';') {
        parseString += curChar;
        curCharIndex++;
        curChar = string_char_at(roadString, curCharIndex);
    }
    
    // add parseString to the yArray passed in:
    argument0.roadTypeArray[roadElements - elementsLeft] = real(parseString);
    
    
    // FINAL STEP
    // move to next element:
    elementsLeft--;
    curCharIndex++;
}


