// Tests the execution timing of any function put inside of it
// argument0 = id of the controller object


timeStart = DLL_getClock();

// FUNCTION HERE -----------------------------------
    // EXAMPLE:
    /*
    var someNum;
    for (j = 0; j < 999999; j++) {
        someNum = DLL_getRandomRange(0, 10000);
        someNum = someNum/2 + j;
    }
    */


    
scr_updateAll(argument0);
scr_updateZoneBuildings(argument0, Z_RES);
scr_updateZoneBuildings(argument0, Z_COM);
scr_updateZoneBuildings(argument0, Z_IND);
    

// END FUNCTION HERE -------------------------------

timeFinish = DLL_getClock();

totalTime = DLL_getTime(timeStart, timeFinish);

show_message("The code took " + string(totalTime) + " seconds to complete.");


