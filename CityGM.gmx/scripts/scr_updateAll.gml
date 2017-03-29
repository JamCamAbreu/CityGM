// argument0 = calling instance id (that stores the variables needed)

// update DLL string:
argument0.tileString = DLL_tileTypeToString();
argument0.tileStringSize = string_length(tileString);

// update Building string:
argument0.buildingString = DLL_buildingsToString();
argument0.buildingElements = DLL_getBuildingVectorSize();

// DEBUG
//show_message("Before, xArray[o] contains: " + string(xArray[0]));

scr_updateBuildings(argument0.buildingString, argument0.buildingElements, argument0);

//DEBUG
//show_message("Now xArray[0] contains: " + string(xArray[0]));

// update miniMap:
//scr_setSurfaceMiniMap(argument0.tileString, argument0.tileStringSize, argument0);
argument0.updateSurfaces = true;

