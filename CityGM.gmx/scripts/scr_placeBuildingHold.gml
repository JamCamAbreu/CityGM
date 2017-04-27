// argument 0 = id that holds all the variables
// argument 1 = int type
// argument 2 = X
// argument 3 = Y


var type = argument1;
var placed = DLL_addBuilding(type, argument2, argument3);

// SOUND:
if (placed) {
    audio_play_sound(sfx_placement, 5, false);
}


// Finally, update all:
scr_updateAll(argument0)

