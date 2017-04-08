// argument0 = type of building

var building = scr_getBuildingString(argument0);
var price = string(DLL_getBuildingPrice(argument0));

var buildingString = building + ": " + price;
return buildingString;

