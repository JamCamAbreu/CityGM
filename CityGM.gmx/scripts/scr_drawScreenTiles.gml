// argument2 = id holding the variables

var tileString = argument0;
var tileStringSize = argument1;

var i;
var sprite;
var xCoord;
var yCoord;
var charPos;

var x1 = scr_getViewX1();
var x2 = scr_getViewX2();
var y1 = scr_getViewY1();
var y2 = scr_getViewY2();

for (r = y1; r < y2; r++) {
    for (c = x1; c < x2; c++) {    
    
        //xCoord = ((i - 1) mod MAP_DIMENSION)*TILE_SIZE;
        //yCoord = floor((i - 1)/MAP_DIMENSION)*TILE_SIZE;
        
        xCoord = c*TILE_SIZE;
        yCoord = r*TILE_SIZE;
        charPos = (r*MAP_DIMENSION + c);
        
        //draw_text_colour(view_xview + 16, view_yview + 16, "X1 = " + string(x1) + ", X2 = " + string(x2), c_white, c_white, c_white, c_white, 1);
        //draw_text_colour(view_xview + 16, view_yview + 32, "Y1 = " + string(y1) + ", Y2 = " + string(y2), c_white, c_white, c_white, c_white, 1);
        
        sprite = scr_getTileSprite(string_char_at(tileString, charPos + 1));
        draw_sprite(sprite, argument2.gameSeason, xCoord, yCoord);
    }
}
