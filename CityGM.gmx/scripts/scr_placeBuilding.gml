// argument 0 = id that holds all the variables
// argument 1 = int type
var myX = scr_getX(argument0.camera);
var myY = scr_getY(argument0.camera);
var type = argument1;
var placed = DLL_addBuilding(type, myX, myY);

// SOUND:
if (placed) {
    audio_play_sound(sfx_placement, 5, false);
}
else
    audio_play_sound(sfx_error, 5, false);



// Finally, update all:
scr_updateAll(argument0)

