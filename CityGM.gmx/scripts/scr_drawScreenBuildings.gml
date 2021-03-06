// argument0 = amount of buildings in vector
// argument1 = object holding the building arrays
// argument2 = draw power? true of false


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


    // DRAW BUILDINGS:
    if (drawBuilding && (argument2 == DRAW_BUILDINGS)) {
        var sprite = scr_getBuildingSprite(bT);
        var sprIndex = 0; // default
        
        // SPECIAL DRAWING - POWER LINES
        if ((bT == BT_PLINE) || (bT == BT_POWERROAD)) {
            var typeIndex = argument1.pLineValueArray[i];
            
            if (typeIndex != 0) {
                var seasonIndex = argument1.gameSeason;
                sprIndex = (typeIndex - 1)*4 + seasonIndex + 1;
            }
            else {
                sprIndex = 0;
            }
        } // end powerline/road
        
        // SPECIAL DRAWING - TREES
        else if (bT == BT_TREE) {
            // function for getting tree pIndex here
        }
        
        // ALL OTHER SPRITES USE SEASONS:
        else {
            sprIndex = argument1.gameSeason;
        }
        
        draw_sprite(sprite, sprIndex, bX*TILE_SIZE, bY*TILE_SIZE);
    }
    
    // ELECTRICITY SYMBOL ('needs power' symbol):
    else if (drawBuilding && (argument2 == DRAW_POWER)) {
        if(scr_checkDrawElectricitySign(bE))
            draw_sprite(spr_needPower, argument1.displayPowerSign, bX*TILE_SIZE, bY*TILE_SIZE);
    }
    
} // end for loop







