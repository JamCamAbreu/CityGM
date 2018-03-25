// argument0 : x
// argument1 : y
// argument2 : season
// argument3 : num rows
// arugment4 : num columns

var row;
var col;
var tileSize = TILE_SIZE;

for (col = 1; col <= argument4; col++) {
    for (row = 1; row <= argument3; row++) {
        draw_sprite(spr_ground, argument2, argument0 + tileSize*col, argument1 + tileSize*row);
    }   
}






