// argument0 : x
// argument1 : y
// argument2 : zoneType
// argument3 : level
// argument4 : variation
// argument5 : shape to draw
// argument6 : season
// argument7 : subimage

draw_sprite(spr_ground, argument6, argument0, argument1);
var zoneSprite = scr_getZSprite(argument2, argument3, argument4, argument5);
draw_sprite(zoneSprite, argument7, argument0, argument1);
