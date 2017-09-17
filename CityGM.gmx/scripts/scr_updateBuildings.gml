// argument0 = buildingString;
// argument1 = buildingElements;
// argument2 = main function that holds the arrays

var sprite;
var xCoord;
var yCoord;
var type;

  /*  EXAMPLE STRING:
  Psuedo:
    myBuildingString = "x,y,power,type;x,y,power,type; ... etc"

  Actual:
    myBuildingString = "3,15,*,2;22,9,-,3; ... etc"
  */
  
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



