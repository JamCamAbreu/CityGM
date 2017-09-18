// argument0 = amount of buildings in vector
// argument1 = object holding the building arrays

var x1 = scr_getViewX1();
var x2 = scr_getViewX2();
var y1 = scr_getViewY1();
var y2 = scr_getViewY2();

var padding = 2

var drawRoad;
for (i = 0; i < argument0; i++) {
    drawRoad = true;
    var bX = argument1.roadXArray[i];
    var bY = argument1.roadYArray[i];
    var bT = argument1.roadTypeArray[i];

    // check x: 
    if (((bX + padding) < x1) || ((bX - padding) > x2))
        drawRoad = false;
    
    // check y:
    if (((bY + padding) < y1) || ((bY - padding) > y2))
        drawRoad = false;

    if (drawRoad) {
    
        // When ready, add this to the bT to get the offset sprite index for the correct season
        var seasonIndex = argument1.gameSeason;
        var imageIndex;
        if (bT != 0)
            imageIndex = (bT - 1) *4 + seasonIndex + 1;
        
        draw_sprite(spr_road, imageIndex, bX*TILE_SIZE, bY*TILE_SIZE);
    }
} // end for loop







