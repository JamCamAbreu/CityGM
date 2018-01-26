// argument0 = x (grid) coord
// argument1 = y (grid) coord
// argument 2 = sprite to draw

var sprite = scr_getBuildingSprite(argument2);
var imageIndex;

var drawX = scr_getRoomCoord(argument0);
var drawY = scr_getRoomCoord(argument1);

// special rules for road sprite:
if (sprite == spr_road || sprite == spr_powerLine || sprite == spr_powerRoad)
    imageIndex = 1;
else
    imageIndex = argument0.gameSeason;

// Draw the sprite:
draw_set_alpha(PLACEMENT_ALPHA);
draw_sprite(sprite, imageIndex, drawX, drawY);
draw_set_alpha(1);
