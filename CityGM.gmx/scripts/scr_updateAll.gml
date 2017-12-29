// argument0 = calling instance id (that stores the variables needed)

// update DLL string:
argument0.tileString = DLL_tileTypeToString();
argument0.tileStringSize = string_length(tileString);

// update Building string:
argument0.buildingString = DLL_buildingsToString();
argument0.buildingElements = DLL_getBuildingVectorSize();
scr_updateBuildings(argument0);

// update Road String:
argument0.roadString = DLL_roadsToString();
argument0.roadElements = DLL_getRoadsVectorSize();
scr_updateRoadsArrays(argument0);

// update miniMap:
argument0.updateSurfaces = true;

// updateMoney:
argument0.money = DLL_getGameMoney();
scr_updateMoneyString(argument0);



// update time:
argument0.gameYear = DLL_getGameYear();
argument0.gameMonth = DLL_getGameMonth();
argument0.gameTimeString = scr_setTimeString(argument0.gameSeason, argument0.gameYear);

// update Population:
scr_updatePopString(argument0);

// update gameMode
argument0.gameMode = DLL_getGameMode();


// update tile data:
scr_updatePollution();
scr_updateLandValue();
DLL_setBuildingTileData(TDT_LANDVALUE);
DLL_setBuildingTileData(TDT_FIREDANGER);

// tax rates:
argument0.resRate = DLL_getTaxRate(TAX_RES);
argument0.comRate = DLL_getTaxRate(TAX_COM);
argument0.indRate = DLL_getTaxRate(TAX_IND);

