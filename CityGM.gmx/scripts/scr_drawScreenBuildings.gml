// argument0 = amount of buildings in vector
// argument1 = object holding the building arrays


var x1 = scr_getViewX1();
var x2 = scr_getViewX2();
var y1 = scr_getViewY1();
var y2 = scr_getViewY2();

var padding = 2


var drawBuilding;
for (i = 0; i < argument0; i++) {
    drawBuilding = true;
    var bX = argument1.xArray[i];
    var bY = argument1.yArray[i];
    var bE = argument1.powerArray[i];
    var bT = argument1.typeArray[i];

    // check x: 
    if (((bX + padding) < x1) || ((bX - padding) > x2))
        drawBuilding = false;
    
    // check y:
    if (((bY + padding) < y1) || ((bY - padding) > y2))
        drawBuilding = false;

    if (drawBuilding) {
        var sprite = scr_getBuildingSprite(bT);
        var sprIndex = 0; // default
        
        // SPECIAL DRAWING - POWER LINES
        if (bT == BT_PLINE) {
            // function for getting pLine sprite index here
        }
        
        // SPECIAL DRAWING - ROADS
        else if (bT == BT_ROAD) {
            // function for getting road sprite index here
        }
        
        // SPECIAL DRAWING - TREES
        else if (bT == BT_TREE) {
            // function for getting tree pIndex here
        }
        
        // ALL OTHER SPRITES USE SEASONS:
        else {
            sprIndex = argument1.gameSeason;
        }
        
        draw_sprite(sprite, argument1.gameSeason, bX*TILE_SIZE, bY*TILE_SIZE);
        
        // ELECTRICITY SYMBOL ('needs power' symbol):
        if(scr_checkDrawElectricitySign(bE)) {
            draw_sprite(spr_needPower, argument1.displayPowerSign, bX*TILE_SIZE, bY*TILE_SIZE);
        }
        
        
        
    }
} // end for loop







