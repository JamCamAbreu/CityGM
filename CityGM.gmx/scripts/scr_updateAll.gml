// argument0 = calling instance id (that stores the variables needed)

// update DLL string:
argument0.tileString = DLL_tileTypeToString();
argument0.tileStringSize = string_length(tileString);

// update Building string:
argument0.buildingString = DLL_buildingsToString();
argument0.buildingElements = DLL_getBuildingVectorSize();
scr_updateBuildings(argument0.buildingString, argument0.buildingElements, argument0);

// update miniMap:
argument0.updateSurfaces = true;

// update time:
scr_updateTime(argument0);

// updateMoney:
argument0.money = DLL_getGameMoney();
scr_updateMoneyString(argument0);

// update Population:
scr_updatePopString(argument0);

