// argument 0 = id that holds all the variables
// argument 1 = int type
// argument 2 = grid X coord
// argument 3 = grid Y coord
// argument 4 = add sound?

var myX = argument2;
var myY = argument3;
var placed = DLL_addBuilding(argument1, myX, myY);

// Check if placement was possible:
if (placed) {

    // SOUND:
    if ((argument4 == SFX_BUILDONLY) || (argument4 == SFX_ALL))
        audio_play_sound(sfx_placement, 5, false);
    
    // update zone if zone was placed:
    if (argument1 == BT_RZONE)
        scr_updateZoneBuildings(argument0, Z_RES);
    else if (argument1 == BT_CZONE)
        scr_updateZoneBuildings(argument0, Z_COM);
    else if (argument1 == BT_IZONE)
        scr_updateZoneBuildings(argument0, Z_IND);
}
else { // could not play sound:
    if ((argument4 == SFX_ERRORONLY) || (argument4 == SFX_ALL))
        audio_play_sound(sfx_error, 5, false);
}


// Finally, update all:
scr_updateAll(argument0)

