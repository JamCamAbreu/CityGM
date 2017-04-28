// argument0 = id of object holding variables


var cameraID = argument0.camera;
var buildingType = argument0.selectedBuilding;

if (argument0.pressHoldMode) {


    // ADD RIGHT
    if (keyboard_check_pressed(vk_right)) || (keyboard_check_pressed(ord('D'))) {
        if (cameraID.x <= (room_width - TILE_SIZE*1)) {
            var placeX = scr_getX(argument0.camera) + 1;
            var placeY = scr_getY(argument0.camera);
            scr_placeBuildingHold(argument0, buildingType, placeX, placeY);
        }
    }
        
    
    // ADD LEFT
    else if (keyboard_check_pressed(vk_left)) || (keyboard_check_pressed(ord('A'))) {
        
        if (cameraID.x >= TILE_SIZE*1) {
            var placeX = scr_getX(argument0.camera) - 1;
            var placeY = scr_getY(argument0.camera);
            scr_placeBuildingHold(argument0, buildingType, placeX, placeY);
        }
     }   
     
     
     
    // ADD ABOVE
    else if (keyboard_check_pressed(vk_up)) || (keyboard_check_pressed(ord('W'))) {
        if (cameraID.y > TILE_SIZE*1) {
            var placeX = scr_getX(argument0.camera);
            var placeY = scr_getY(argument0.camera) - 1;
            scr_placeBuildingHold(argument0, buildingType, placeX, placeY);
        }
    }
    
    
    // ADD BELOW
    else if (keyboard_check_pressed(vk_down)) || (keyboard_check_pressed(ord('S'))) {
        if (cameraID.y < room_height - TILE_SIZE*1) {
            var placeX = scr_getX(argument0.camera);
            var placeY = scr_getY(argument0.camera) + 1;
            scr_placeBuildingHold(argument0, buildingType, placeX, placeY);
        }
    }

} // end if placement hold mode
