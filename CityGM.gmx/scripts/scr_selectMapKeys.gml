// argument0 is the id holding the variables


// A key to move left:
if (keyboard_check_pressed(ord('A'))) {
    if (argument0.selectedMap == 0)
        argument0.selectedMap = 4; // wrap
    else
        argument0.selectedMap--;
}


// D key to move right:
else if (keyboard_check_pressed(ord('D'))) {
    if (argument0.selectedMap == 4)
        argument0.selectedMap = 0; // wrap
    else
        argument0.selectedMap++;
}


