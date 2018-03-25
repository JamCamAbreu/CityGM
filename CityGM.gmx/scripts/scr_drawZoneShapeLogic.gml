// argument0 : x
// argument1 : y
// argument2 : zoneType
// argument3 : level
// argument4 : variation
// argument5 : shape code
// argument6 : season
// argument7 : subimage

// make code below more readable:
var ZT = argument2;
var L = argument3;
var V = argument4;
var S = argument5;
var Season = argument6;
var SI = argument7;

// column and row coordinates:
var col = TILE_SIZE;
var row = TILE_SIZE;

var c1 = argument0;
var c2 = argument0 + col;
var c3 = argument0 + col*2;

var r1 = argument1;
var r2 = argument1 + row;
var r3 = argument1 + row*2;

var subImage = image_index; // later make this work with animation
    // I can use the internal clock to animate. To make each 
    // building unique I can 'add' other information such as
    // x or y coordinates combined. 



// first check for large shapes (all, cross, donut, etc..)
// ALL
//  X   X   X
//  X   X   X
//  X   X   X
if (S & BM_ALL == BM_ALL) {
    var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_ALL);
    draw_sprite(zoneSprite, SI, c1, r1);
}


// DONUT
//  X   X   X
//  X   -   X
//  X   X   X
else if (S & BM_DONUT == BM_DONUT) {
    var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_DONUT);
    draw_sprite(zoneSprite, SI, c1, r1);
}

// CROSS
//  -   X   -
//  X   X   X
//  -   X   -
else if (S & BM_CROSS == BM_CROSS) {
    var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_CROSS);
    draw_sprite(zoneSprite, SI, c1, r1);
}




// ALL OTHER SHAPES
else {

    // Modified at every step to ensure no overlapping:
    var Smod = S;
    
    // LINES
    // (FAVORS HORIZONTALS OVER VERTICLES)
    // Top Horizontal:
    //  X   X   X
    //  -   -   -
    //  -   -   -
    if (Smod & BM_TH == BM_TH) {
        var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_H);
        draw_sprite(zoneSprite, SI, c1, r1);
        Smod = Smod & ~BM_TH; // remove used bits:
    }
    
    // Middle Horizontal
    //  -   -   -
    //  X   X   X
    //  -   -   -
    if (Smod & BM_MH == BM_MH) {
        var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_H);
        draw_sprite(zoneSprite, SI, c1, r2);
        Smod = Smod & ~BM_MH; // remove used bits:
    }
    
    // Bottom Horizontal
    //  -   -   -
    //  -   -   -
    //  X   X   X
    if (Smod & BM_BH == BM_BH) {
        var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_H);
        draw_sprite(zoneSprite, SI, c1, r3);
        Smod = Smod & ~BM_BH; // remove used bits:
    }
    
    // Left Verticle
    //  X   -   -
    //  X   -   -
    //  X   -   -
    if (Smod & BM_LV == BM_LV) {
        var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_V);
        draw_sprite(zoneSprite, SI, c1, r1);
        Smod = Smod & ~BM_LV; // remove used bits:
    }
    
    // Middle Verticle
    //  -   X   -
    //  -   X   -
    //  -   X   -
    if (Smod & BM_MV == BM_MV) {
        var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_V);
        draw_sprite(zoneSprite, SI, c2, r1);
        Smod = Smod & ~BM_MV; // remove used bits:
    }
    
    // Right Verticle
    //  -   -   X
    //  -   -   X
    //  -   -   X
    if (Smod & BM_RV == BM_RV) {
        var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_V);
        draw_sprite(zoneSprite, SI, c3, r1);
        Smod = Smod & ~BM_RV; // remove used bits:
    }
    
    
    // next check for medium shapes (box, corner, etc...)
    // Boxes ---------------------
    // TOP LEFT BOX
    //  X   X   -
    //  X   X   -
    //  -   -   -
    if (Smod & BM_TLB == BM_TLB) {
        var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_BOX);
        draw_sprite(zoneSprite, SI, c1, r1);
        Smod = Smod & ~BM_TLB; // remove used bits:
    }
    
    // TOP RIGHT BOX
    //  -   X   X
    //  -   X   X
    //  -   -   -
    if (Smod & BM_TRB == BM_TRB) {
        var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_BOX);
        draw_sprite(zoneSprite, SI, c2, r1);
        Smod = Smod & ~BM_TRB; // remove used bits:
    }
    
    // BOTTOM LEFT BOX
    //  -   -   -
    //  X   X   -
    //  X   X   -
    if (Smod & BM_BLB == BM_BLB) {
        var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_BOX);
        draw_sprite(zoneSprite, SI, c1, r2);
        Smod = Smod & ~BM_BLB; // remove used bits:
    }
    
    // BOTTOM RIGHT BOX
    //  -   -   -
    //  -   X   X
    //  -   X   X
    if (Smod & BM_BRB == BM_BRB) {
        var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_BOX);
        draw_sprite(zoneSprite, SI, c2, r2);
        Smod = Smod & ~BM_BRB; // remove used bits:
    }
    
    
    // Corners ---------------------
    // TOP LEFT CORNER
    //  X   X   -
    //  X   -   -
    //  -   -   -
    if (Smod & BM_TLC == BM_TLC) {
        var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_TLC);
        draw_sprite(zoneSprite, SI, c1, r1);
        Smod = Smod & ~BM_TLC; // remove used bits:
    }
    
    // TOP RIGHT CORNER
    //  -   X   X
    //  -   -   X
    //  -   -   -
    if (Smod & BM_TRC == BM_TRC) {
        var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_TRC);
        draw_sprite(zoneSprite, SI, c2, r1);
        Smod = Smod & ~BM_TRC; // remove used bits:
    }
    
    // BOTTOM LEFT CORNER
    //  -   -   -
    //  X   -   -
    //  X   X   -
    if (Smod & BM_BLC == BM_BLC) {
        var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_BLC);
        draw_sprite(zoneSprite, SI, c1, r2);
        Smod = Smod & ~BM_BLC; // remove used bits:
    }
    
    // BOTTOM RIGHT CORNER
    //  -   -   -
    //  -   -   X
    //  -   X   X
    if (Smod & BM_BRC == BM_BRC) {
        var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_BRC);
        draw_sprite(zoneSprite, SI, c2, r2);
        Smod = Smod & ~BM_BRC; // remove used bits:
    }
        
        
    // SINGLES ---------------------
    var zoneSprite = scr_getZSprite(ZT, L, V, SHAPE_BASIC);
    // No need to modify the Smod
    // TOP LEFT
    if (Smod & BM_TL == BM_TL) {
        draw_sprite(zoneSprite, SI, c1, r1);
    }

    // TOP
    if (Smod & BM_T == BM_T) {
        draw_sprite(zoneSprite, SI, c2, r1);
    }

    // TOP RIGHT
    if (Smod & BM_TR == BM_TR) {
        draw_sprite(zoneSprite, SI, c3, r1);
    }

    // LEFT
    if (Smod & BM_L == BM_L) {
        draw_sprite(zoneSprite, SI, c1, r2);
    }

    // MIDDLE
    if (Smod & BM_M == BM_M) {
        draw_sprite(zoneSprite, SI, c2, r2);
    }

    // RIGHT
    if (Smod & BM_R == BM_R) {
        draw_sprite(zoneSprite, SI, c3, r2);
    }

    // BOTTOM LEFT
    if (Smod & BM_BL == BM_BL) {
        draw_sprite(zoneSprite, SI, c1, r3);
    }

    // BOTTOM
    if (Smod & BM_B == BM_B) {
        draw_sprite(zoneSprite, SI, c2, r3);
    }

    // BOTTOM RIGHT
    if (Smod & BM_BR == BM_BR) {
        draw_sprite(zoneSprite, SI, c3, r3);
    }
        
} // end all other shapes
