// argument0 = id holding the variables

if  (keyboard_check_pressed(ord('A')) ||
    keyboard_check_pressed(ord('W')) ||
    keyboard_check_pressed(ord('S')) ||
    keyboard_check_pressed(ord('D')) ||
    keyboard_check_pressed(vk_up) ||
    keyboard_check_pressed(vk_down) ||
    keyboard_check_pressed(vk_left) ||
    keyboard_check_pressed(vk_right) ) {
    
    scr_updateZoneBuildings(id, Z_RES);
    scr_updateZoneBuildings(id, Z_COM);
    scr_updateZoneBuildings(id, Z_IND);
    scr_setSurfaceZones(argument0);
    
    }
