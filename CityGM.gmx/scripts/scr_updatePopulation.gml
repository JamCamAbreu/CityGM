// argument0 = id holding variables

/// UPDATE and TEST population increase
var newCityType = DLL_updatePopulationZones();

// update population and popString:
argument0.gamePopulation = DLL_getPopulation();


scr_updatePopString(argument0);

if (newCityType) {
    var type = DLL_getCityType();
    var oldType = scr_getCityTypeStringPrevious(type);
    var newType = scr_getCityTypeString(type);
    var congrats = "Congratulations! Your " + oldType + " has now grown into a " + newType + "!"
    scr_pushMessage(argument0.messageQueue, congrats, MC_CONGRAT, 60*4);
}
