// argument0 = main function that holds the arrays
// argument1 = type of zone to update;

  /*  EXAMPLE STRING:
  Psuedo:
    zoneString = "x,y,zoneType,zoneLevel,typeVar,shape;x,y... etc"

  Actual:
    zoneString = "3,15,1,2,1,128;22,9... etc"
  */


var zoneString = DLL_zonesToString(argument1);
var zoneElements = DLL_getNumZonesType(argument1);
var elementsLeft = zoneElements;

// DEBUGGING:
//show_message("Import. Type=" + string(argument1) + zoneString);
//show_message("elementsLeft = " + string(elementsLeft));

var curArrayIndex = 0;
var curCharIndex = 1; // because how game maker strings work lol
var curChar;
var parseString = "";
var curElementNum = 0;

while (elementsLeft > 0 && (curCharIndex <= string_length(zoneString)) ) {

    // reset string for each piece of data:
    parseString = "";
    curChar = string_char_at(buildingString, curCharIndex);


    // GET X VALUE:
    while (curChar != 'X') {
        curCharIndex++;
        curChar = string_char_at(zoneString, curCharIndex);
    }

    // now we are at 'X', we need to get the info AFTER it:
    curCharIndex++;
    curChar = string_char_at(zoneString, curCharIndex);
    
    // get ALL of the characters needed from this data:
    while (curChar != 'Y') {
        parseString += curChar;
        curCharIndex++;
        curChar = string_char_at(zoneString, curCharIndex);
    }

    // add parseString to the Array passed in:  
    if (argument1 == Z_RES)
        argument0.RzonesX[curElementNum] = real(parseString);
    else if (argument1 == Z_COM)
        argument0.CzonesX[curElementNum] = real(parseString);
    else if (argument1 == Z_IND)
        argument0.IzonesX[curElementNum] = real(parseString);

    
    
    
    
    
    // GET Y VALUE:
    // reset string for each piece of data:
    parseString = "";
    
    // we are currently at 'Y', so we need what comes after that:
    curCharIndex++;
    curChar = string_char_at(zoneString, curCharIndex);
    
    // get ALL of the characters needed from this data:
    while (curChar != 'Z') {
        parseString += curChar;
        curCharIndex++;
        curChar = string_char_at(zoneString, curCharIndex);
    }
    
    // add parseString to the Array passed in:
    if (argument1 == Z_RES)
        argument0.RzonesY[curElementNum] = real(parseString);
    else if (argument1 == Z_COM)
        argument0.CzonesY[curElementNum] = real(parseString);
    else if (argument1 == Z_IND)
        argument0.IzonesY[curElementNum] = real(parseString);
    
    

    
    // get zone Type:
    // reset string for each piece of data:
    parseString = "";
    
    // we are currently at 'Z', so we need what comes after that:
    curCharIndex++;
    curChar = string_char_at(zoneString, curCharIndex);
    
    // get ALL of the characters needed from this data:
    while (curChar != 'L') {
        parseString += curChar;
        curCharIndex++;
        curChar = string_char_at(zoneString, curCharIndex);
    }
    
    // add parseString to the Array passed in:
    if (argument1 == Z_RES)
        argument0.RzonesZ[curElementNum] = real(parseString);
    else if (argument1 == Z_COM)
        argument0.CzonesZ[curElementNum] = real(parseString);
    else if (argument1 == Z_IND)
        argument0.IzonesZ[curElementNum] = real(parseString);
    
    
    
    
    
    
    
    // get zone Level:
    // reset string for each piece of data:
    parseString = "";
    
    // we are currently at 'L', so we need what comes after that:
    curCharIndex++;
    curChar = string_char_at(zoneString, curCharIndex);
    
    // get ALL of the characters needed from this data:
    while (curChar != 'T') {
        parseString += curChar;
        curCharIndex++;
        curChar = string_char_at(zoneString, curCharIndex);
    }
    
    // add parseString to the Array passed in:
    if (argument1 == Z_RES)
        argument0.RzonesL[curElementNum] = real(parseString);
    else if (argument1 == Z_COM)
        argument0.CzonesL[curElementNum] = real(parseString);
    else if (argument1 == Z_IND)
        argument0.IzonesL[curElementNum] = real(parseString);
    
    
    
    
    
    
    // get zone Type Variation:
    // reset string for each piece of data:
    parseString = "";
    
    // we are currently at 'T', so we need what comes after that:
    curCharIndex++;
    curChar = string_char_at(zoneString, curCharIndex);
    
    // get ALL of the characters needed from this data:
    while (curChar != 'S') {
        parseString += curChar;
        curCharIndex++;
        curChar = string_char_at(zoneString, curCharIndex);
    }
    
    // add parseString to the array passed in:
    if (argument1 == Z_RES)
        argument0.RzonesT[curElementNum] = real(parseString);
    else if (argument1 == Z_COM)
        argument0.CzonesT[curElementNum] = real(parseString);
    else if (argument1 == Z_IND)
        argument0.IzonesT[curElementNum] = real(parseString);

    
    
    // get zone Shape:
    // reset string for each piece of data:
    parseString = "";
    
    // we are currently at 'S', so we need what comes after that:
    curCharIndex++;
    curChar = string_char_at(zoneString, curCharIndex);
    
    // get ALL of the characters needed from this data:
    while (curChar != ';') {
        parseString += curChar;
        curCharIndex++;
        curChar = string_char_at(zoneString, curCharIndex);
    }
    
    // add parseString to the array passed in:
    if (argument1 == Z_RES)
        argument0.RzonesS[curElementNum] = real(parseString);
    else if (argument1 == Z_COM)
        argument0.CzonesS[curElementNum] = real(parseString);
    else if (argument1 == Z_IND)
        argument0.IzonesS[curElementNum] = real(parseString);
    
    
    // FINAL STEP
    // move to next element:
    elementsLeft--;
    curElementNum++;
}

// finally, update the total amount of zones:
if (argument1 == Z_RES)
    argument0.RzonesNum = curElementNum;
else if (argument1 == Z_COM)
    argument0.CzonesNum = curElementNum;
else if (argument1 == Z_IND)
    argument0.IzonesNum = curElementNum;







