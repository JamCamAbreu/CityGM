// argument0 = id of the main game state instance

// Credit: Modified Bresenham's Algorithm:
var x0 = argument0.multiPlaceStartX;
var x1 = argument0.multiPlaceFinishX;

var y0 = argument0.multiPlaceStartY;
var y1 = argument0.multiPlaceFinishY;

var deltaX = (x1 - x0);
var deltaY = (y1 - y0); // height of line

var divisor = deltaX;

if (divisor = 0)
    divisor = 1; // prevent divide by zero
    
var riseOverRun = deltaY / divisor;

var curY = y0;
var curX;
var prevY = y0;

// positive delta X (draw to right):
if (deltaX > 0) {

    for (curX = x0; curX <= x1; curX++) {
        
        // FILL IN HOLES
        if (riseOverRun >= 0) { // slope up
        
            // fill in holes:
            while (prevY < curY) {
                scr_drawSpriteAt(curX, round(prevY), argument0.selectedBuilding);
                prevY++;
            }
        }
        
        else {  // slope down
            // fill in holes:
            while (prevY > curY) {
                scr_drawSpriteAt(curX, round(prevY), argument0.selectedBuilding);
                prevY--;
            }
        }
    
        scr_drawSpriteAt(curX, round(curY), argument0.selectedBuilding);
        prevY = round(curY);
        curY += riseOverRun;
    }
}






// negative delta X (draw to left):
else if (deltaX < 0){
    riseOverRun *= (-1);
    for (curX = x0; curX >= x1; curX--) {
    
        // FILL IN HOLES
        if (riseOverRun >= 0) { // slope up
        
            // fill in holes:
            while (prevY < curY) {
                scr_drawSpriteAt(curX, round(prevY), argument0.selectedBuilding);
                prevY++;
            }
        }
        else {  // slope down
            // fill in holes:
            while (prevY > curY) {
                scr_drawSpriteAt(curX, round(prevY), argument0.selectedBuilding);
                prevY--;
            }
        }
    
        scr_drawSpriteAt(curX, round(curY), argument0.selectedBuilding);
        prevY = round(curY);
        curY += riseOverRun;
    }
}


// vertical line:
else if (deltaX == 0) {

    curX = x0;

    // going up:
    if (deltaY > 0) {
        while (curY < y1) {
            scr_drawSpriteAt(curX, curY, argument0.selectedBuilding);
            curY++;
        }
    }

    // going down:
    if (deltaY < 0) {
        while (curY > y1) {
            scr_drawSpriteAt(curX, curY, argument0.selectedBuilding);
            curY--;
        }
    }
}




