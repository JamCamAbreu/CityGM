// argument0 is the id holding the variables

var row = scr_buildMenuGetRow(argument0.selectedBuilding);
var column = scr_buildMenuGetColumn(argument0.selectedBuilding);

// A key to move left:
if (keyboard_check_pressed(ord('A'))) {
    if (column == 0)
        argument0.selectedBuilding += (BUILDMENU_COLUMNS - 1); // wrap
    else
        argument0.selectedBuilding--;
}


// D key to move right:
else if (keyboard_check_pressed(ord('D'))) {
    if (column == (BUILDMENU_COLUMNS - 1))
        argument0.selectedBuilding -= (BUILDMENU_COLUMNS - 1); // wrap
    else
        argument0.selectedBuilding++;
}


// W key to move up:
else if (keyboard_check_pressed(ord('W'))) {
    if (row == 0)
        argument0.selectedBuilding += (BUILDMENU_ROWS - 1)*(BUILDMENU_COLUMNS); // wrap
    else
        argument0.selectedBuilding -= (BUILDMENU_COLUMNS);
}


// S key to move down:
else if (keyboard_check_pressed(ord('S'))) {
    if (row == (BUILDMENU_ROWS - 1))
        argument0.selectedBuilding -= (BUILDMENU_ROWS - 1)*(BUILDMENU_COLUMNS); // wrap
    else
        argument0.selectedBuilding += (BUILDMENU_COLUMNS);
}






