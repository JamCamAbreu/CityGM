// argument0 = main function that holds the arrays
// argument1 = type of zone to update;


  /*  EXAMPLE STRING:
  Psuedo:
    myBuildingString = "x,y,zoneType,level,TypeVariation.[nextZoneBuilding] ... etc"
        // seperated by dot between each zoneBuilding
  */


  
var zoneBuildingString = ""; 
zoneBuildingString += DLL_zoneBuildingsToString(argument1);

// count how many buildings with special dot char:
var charPos;
var zBuildingNum = 0;
for (charPos = 1; charPos <= string_length(zoneBuildingString); charPos++) {
    if (string_char_at(zoneBuildingString, charPos) == '.')
        zBuildingNum++;
}

// parse ALL of text:
charPos = 1;
var charAt = string_char_at(zoneBuildingString, charPos);
var zoneBuildingNum = 0;
while (( zoneBuildingNum <= zBuildingNum) && (charPos <= string_length(zoneBuildingString)) ) {

    // parse each zone building one by one (seperated by '.' char)
    var elementNum = 0;
    while ((charAt != '.') && (charPos <= string_length(zoneBuildingString)) ) {
    
        // get x (first element):
        elementString = "";
        while ((charAt != ',') && (charAt != '.') && (charPos <= string_length(zoneBuildingString)) ) {
            elementString += charAt;
            charPos++;
            charAt = string_char_at(zoneBuildingString, charPos);
        }
        //show_message("Just after inner for loop, string to add = " + elementString);
        var elementVal = real(elementString);
        
        scr_setZoneArray(argument0, argument1, elementNum, elementVal, zoneBuildingNum);
        
            if (charAt == ',') {
                charPos++;
                charAt = string_char_at(zoneBuildingString, charPos);
            }
        
        elementNum++;    
    } // inner while (process each element within building)
    
    // if char at pos charPos is now a '.'
    if (charAt == '.') {
        charPos++;
        charAt = string_char_at(zoneBuildingString, charPos);
    }
    
    // num of buildings processed (array index):
    zoneBuildingNum++;

} // outer while (process each building)

// How many buildings do we have in the array now?  
if (argument1 == Z_RES)
    RzonesNum = zoneBuildingNum;
else if (argument1 == Z_COM)
    CzonesNum = zoneBuildingNum;
else if (argument1 == Z_IND)
    IzonesNum = zoneBuildingNum;
    




