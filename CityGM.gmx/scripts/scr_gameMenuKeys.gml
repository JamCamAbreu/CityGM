// argument0 is the id holding the variables


// A key to move left:
if (keyboard_check_pressed(ord('A'))) {
    if (argument0.selectedMenu == 0)
        argument0.selectedMenu = MENU_FILE; // wrap
    else
        argument0.selectedMenu--;
}


// D key to move right:
else if (keyboard_check_pressed(ord('D'))) {
    if (argument0.selectedMenu == MENU_FILE)
        argument0.selectedMenu = 0; // wrap
    else
        argument0.selectedMenu++;
}


