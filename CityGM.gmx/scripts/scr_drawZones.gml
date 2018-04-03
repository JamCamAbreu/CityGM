// argument0 : object holding all the variables/arrays

/*
-- argument0 contains: --
zonesX[MAX_ZONES] 
zonesY[MAX_ZONES]
zonesZ[MAX_ZONES]
zonesL[MAX_ZONES]
zonesT[MAX_ZONES]
zonesS[MAX_ZONES]
zonesNum = 0;
*/



var x1 = scr_getViewX1();
var x2 = scr_getViewX2();
var y1 = scr_getViewY1();
var y2 = scr_getViewY2();

var padding = 2;
var drawZoneBuilding;
var sub = image_index; 
    
var i;
var col = TILE_SIZE;
var row = TILE_SIZE;

var numZ = 0;
for (t = Z_RES; t <= Z_IND; t++) {

    // Get the right amount of zones for each zone type:
    if (t == Z_RES) {
        numZ = argument0.RzonesNum;
    } else if (t == Z_COM) {
        numZ = argument0.CzonesNum;
    } else if (t == Z_IND) {
        numZ = argument0.IzonesNum;
    }

    for (i = 0; i < numZ; i++) {
    
        // true until proven false:
        drawZoneBuilding = true;
        
        // get x and y values:
        var zX;
        var zY;
        if (t == Z_RES) {
            zX = argument0.RzonesX[i];
            zY = argument0.RzonesY[i];
        } else if (t == Z_COM) {
            zX = argument0.CzonesX[i];
            zY = argument0.CzonesY[i];
        } else if (t == Z_IND) {
            zX = argument0.IzonesX[i];
            zY = argument0.IzonesY[i];
        }

        
        // only draw if within screen:
        // check x: 
        if (((zX + padding) < x1) || ((zX - padding) > x2))
            drawZoneBuilding = false;
        
        // check y:
        if (((zY + padding) < y1) || ((zY - padding) > y2))
            drawZoneBuilding = false;
        
            
        if (drawZoneBuilding) {
            
            // Get more information:
            var posX = zX*TILE_SIZE;       // true x coord
            var posY = zY*TILE_SIZE;       // true y coord

            var zoneType;
            var level;
            var variation;
            var shape;
            if (t == Z_RES) {
                zoneType = argument0.RzonesZ[i];
                level = argument0.RzonesL[i];
                variation = argument0.RzonesT[i];
                shape = argument0.RzonesS[i];
            } else if (t == Z_COM) {
                zoneType = argument0.CzonesZ[i];
                level = argument0.CzonesL[i];
                variation = argument0.CzonesT[i];
                shape = argument0.CzonesS[i];
            } else if (t == Z_IND) {
                zoneType = argument0.IzonesZ[i];
                level = argument0.IzonesL[i];
                variation = argument0.IzonesT[i];
                shape = argument0.IzonesS[i];
            }
            
            var season = argument0.gameSeason;
            
            
            // Use level to determine how to draw the zone:
            var minLevel = DLL_getZoneCombineLevel(zoneType);
            
            // Small buildings:
            if (level < minLevel) {
                // Only draw ground under tiles that are active (bits are set):
                scr_drawZoneGroundBitmap(posX, posY, season, shape);
                
                // All the logic for drawing and combining the zone building sprites:
                scr_drawZoneShapeLogic(posX, posY, zoneType, level, variation, shape, season, sub);
            }
            
            // Large 3X3 buildings:
            else {
                var zoneSprite = scr_getZBigSprite(zoneType, level, variation);
                draw_sprite(zoneSprite, image_index, posX, posY);
            }
                
        } // end if drawZoneBuilding
    } // end each number of zones in that zone type
} // end each zone type

