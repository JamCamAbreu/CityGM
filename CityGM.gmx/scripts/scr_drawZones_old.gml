

var x1 = scr_getViewX1();
var x2 = scr_getViewX2();
var y1 = scr_getViewY1();
var y2 = scr_getViewY2();

var padding = 2;

var i;
// R zones:
for (i = 0; i < scr_getNumZoneBuildings(argument0, Z_RES); i++) {

    var drawZoneBuilding = true;
    var zX = argument0.RzonesX[i];
    var zY = argument0.RzonesY[i];
    
    var ZT = argument0.RzonesZT[i];
    var L = argument0.RzonesL[i];
    var TV = argument0.RzonesTV[i];
    var SP = argument0.RzonesSP[i];
    
    var posX = zX*TILE_SIZE;
    var posy = zY*TILE_SIZE;
    
    
    // check x: 
    if (((zX + padding) < x1) || ((zX - padding) > x2)) {
        drawZoneBuilding = false;
    }
    
    // check y:
    if (((zY + padding) < y1) || ((zY - padding) > y2))
        drawZoneBuilding = false;

    if (drawZoneBuilding) {
        var sprite = scr_getZoneSprite(ZT);
        var index = scr_getZoneImageIndex(L, TV, SP);
        draw_sprite(sprite, index, zX*TILE_SIZE, zY*TILE_SIZE);
    }
} // end for loop



// C zones:
for (i = 0; i < scr_getNumZoneBuildings(argument0, Z_COM); i++) {

    var drawZoneBuilding = true;
    var zX = argument0.CzonesX[i];
    var zY = argument0.CzonesY[i];
    
    var ZT = argument0.CzonesZT[i];
    var L = argument0.CzonesL[i];
    var TV = argument0.CzonesTV[i];
    var SP = argument0.CzonesSP[i];
    
    var posX = zX*TILE_SIZE;
    var posy = zY*TILE_SIZE;
    
    
    // check x: 
    if (((zX + padding) < x1) || ((zX - padding) > x2)) {
        drawZoneBuilding = false;
    }
    
    // check y:
    if (((zY + padding) < y1) || ((zY - padding) > y2))
        drawZoneBuilding = false;

    if (drawZoneBuilding) {
        var sprite = scr_getZoneSprite(ZT);
        var index = scr_getZoneImageIndex(L, TV, SP);
        draw_sprite(sprite, index, zX*TILE_SIZE, zY*TILE_SIZE);
    }
} // end for loop





// I zones:
for (i = 0; i < scr_getNumZoneBuildings(argument0, Z_IND); i++) {

    var drawZoneBuilding = true;
    var zX = argument0.IzonesX[i];
    var zY = argument0.IzonesY[i];
    
    var ZT = argument0.IzonesZT[i];
    var L = argument0.IzonesL[i];
    var TV = argument0.IzonesTV[i];
    var SP = argument0.IzonesSP[i];
    
    var posX = zX*TILE_SIZE;
    var posy = zY*TILE_SIZE;
    
    
    // check x: 
    if (((zX + padding) < x1) || ((zX - padding) > x2)) {
        drawZoneBuilding = false;
    }
    
    // check y:
    if (((zY + padding) < y1) || ((zY - padding) > y2))
        drawZoneBuilding = false;

    if (drawZoneBuilding) {
        var sprite = scr_getZoneSprite(ZT);
        var index = scr_getZoneImageIndex(L, TV, SP);
        draw_sprite(sprite, index, zX*TILE_SIZE, zY*TILE_SIZE);
    }
} // end for loop










