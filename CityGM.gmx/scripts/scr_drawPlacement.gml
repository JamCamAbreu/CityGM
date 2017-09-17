// argument0 = id of object holding variables

var sprite = scr_getBuildingSprite(argument0.selectedBuilding);
var imageIndex;

// special rules for road sprite:
if (sprite == spr_road || sprite == spr_powerLine)
    imageIndex = 1;
else
    imageIndex = argument0.gameSeason;

draw_set_alpha(PLACEMENT_ALPHA);

draw_sprite(sprite, imageIndex, camera.x, camera.y);
draw_set_alpha(1);
