// argument0 = id of object holding variables

var sprite = scr_getBuildingSprite(argument0.selectedBuilding);
draw_set_alpha(PLACEMENT_ALPHA);
draw_sprite(sprite, argument0.gameSeason, camera.x, camera.y);
draw_set_alpha(1);