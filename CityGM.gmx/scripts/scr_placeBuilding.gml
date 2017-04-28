// argument 0 = id that holds all the variables
// argument 1 = int type
var myX = scr_getX(argument0.camera);
var myY = scr_getY(argument0.camera);
var placed = DLL_addBuilding(argument1, myX, myY);

// SOUND:
if (placed) {
    audio_play_sound(sfx_placement, 5, false);
    
    // update zone if zone was placed:
    if (argument1 == BT_RZONE)
        scr_updateZoneBuildings(argument0, Z_RES);
    else if (argument1 == BT_CZONE)
        scr_updateZoneBuildings(argument0, Z_COM);
    else if (argument1 == BT_IZONE)
        scr_updateZoneBuildings(argument0, Z_IND);
}
else
    audio_play_sound(sfx_error, 5, false);



// Finally, update all:
scr_updateAll(argument0)

