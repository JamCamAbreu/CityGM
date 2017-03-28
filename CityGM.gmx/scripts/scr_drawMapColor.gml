
var tileString = argument0;
var tileStringSize = argument1;

var i;
var color;
var xCoord;
var yCoord;
for (i = 1; i <= tileStringSize; i++) { // change i = 1 to i = first tile in view UNTIL last tile in view

    xCoord = ((i - 1) mod MAP_DIMENSION)*TILE_SIZE;
    yCoord = floor((i - 1)/MAP_DIMENSION)*TILE_SIZE;

    // set color (or sprite):
    color = scr_getTileColor(string_char_at(tileString, i));
    draw_rectangle_colour(xCoord, yCoord, xCoord + TILE_SIZE, yCoord + TILE_SIZE, color, color, color, color, false);
}
