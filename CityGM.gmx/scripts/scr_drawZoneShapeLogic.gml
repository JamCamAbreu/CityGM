// argument0 : x
// argument1 : y
// argument2 : zoneType
// argument3 : level
// argument4 : variation
// argument5 : shape code
var S = argument5;
// argument6 : season

var col = TILE_SIZE;
var row = TILE_SIZE;

var subImage = image_index; // later make this work with animation
    // I can use the internal clock to animate. To make each 
    // building unique I can 'add' other information such as
    // x or y coordinates combined. 


// first check for large shapes (all, cross, donut, etc..)
if (S & BM_ALL) {
    
}

else if (S & BM_DONUT) {

}

else if (S & BM_CROSS) {

}

// next check for lines (top vertical, etc...)
else if (S & BM_TH) {

}

else if (S & BM_LV) {

}

else if (S & BM_RV) {

}

else if (S & BM_BH) {

}


else {

    // next check for medium shapes (box, corner, etc...)
    // Boxes:
    if (S & BM_TLB) {
    
    }
    
    else if (S & BM_TRB) {
    
    }
    
    else if (S & BM_BLB) {
    
    }
    
    else if (S & BM_BRB) {
    
    }
    
    
    // Corners:
    else if (S & BM_TLC) {
    
    }
    
    else if (S & BM_TRC) {
    
    }
    
    else if (S & BM_BLC) {
    
    }
    
    else if (S & BM_BRC) {
    
    }
    
    
    
    else {
        // next just draw small shapes
        
        if (S & BM_TL)
            scr_drawZoneShape(argument0, argument1, argument2, argument3, argument4, SHAPE_BASIC);
        
        if (S & BM_T)
            scr_drawZoneShape(argument0 + col, argument1, argument2, argument3, argument4, SHAPE_BASIC);
            
        if (S & BM_TR)
            scr_drawZoneShape(argument0 + col*2, argument1, argument2, argument3, argument4, SHAPE_BASIC);
            
        if (S & BM_L)
            scr_drawZoneShape(argument0, argument1 + row, argument2, argument3, argument4, SHAPE_BASIC);
        
        if (S & BM_M)
            scr_drawZoneShape(argument0 + col, argument1 + row, argument2, argument3, argument4, SHAPE_BASIC);
            
        if (S & BM_R)
            scr_drawZoneShape(argument0 + col*2, argument1 + row, argument2, argument3, argument4, SHAPE_BASIC);
            
        if (S & BM_BL)
            scr_drawZoneShape(argument0, argument1 + row*2, argument2, argument3, argument4, SHAPE_BASIC);
        
        if (S & BM_B)
            scr_drawZoneShape(argument0 + col, argument1 + row*2, argument2, argument3, argument4, SHAPE_BASIC);
            
        if (S & BM_BR)
            scr_drawZoneShape(argument0 + col*2, argument1 + row*2, argument2, argument3, argument4, SHAPE_BASIC);
        
    } // end level 2 check
} // end level 1 check
