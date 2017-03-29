// argument0 = string info of tiles from DLL
// argument1 = string size of argument0
// argument2 = id of object that holds the surface id

var tileString = argument0;
var tileStringSize = argument1;
var mapDimension = MINIMAP_PIXEL*MAP_DIMENSION;
if (!surface_exists(argument2.surfaceMiniMap)) {
    argument2.surfaceMiniMap = surface_create(mapDimension, mapDimension);
    surface_set_target(argument2.surfaceMiniMap);
    draw_clear_alpha(c_black, 1);
    surface_reset_target();
}

if (surface_exists(argument2.surfaceMiniMap)) {

    // surface set up:
    surface_set_target(argument2.surfaceMiniMap);
    draw_clear_alpha(c_white, 1);
    
    // drawing algorithm:
    var mapX1 = 0
    var mapY1 = 0
    
    var color;
    var xCoord;
    var yCoord;
    var charPos;   
    
    for (r = 0; r < MAP_DIMENSION; r++) {
        for (c = 0; c < MAP_DIMENSION; c++) {    
            
            xCoord = mapX1 + ((c)*MINIMAP_PIXEL);
            yCoord = mapY1 + ((r)*MINIMAP_PIXEL);
            charPos = (r*MAP_DIMENSION + c) + 1;
            
            color = scr_getTileColor(string_char_at(tileString, charPos));
            draw_rectangle_colour(xCoord, yCoord, xCoord + MINIMAP_PIXEL, yCoord + MINIMAP_PIXEL, color, color, color, color, false);
        }
    }
    
    surface_reset_target();
} // end if surface exists

