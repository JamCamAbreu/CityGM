// argument0 = id of object that holds the surface id







if (!surface_exists(argument0.surfaceZones)) {
    argument0.surfaceZones = surface_create(view_wview, view_hview);
    surface_set_target(argument0.surfaceZones);
    draw_clear_alpha(c_black, 0);
    surface_reset_target();
}

if (surface_exists(argument0.surfaceZones)) {
    
    // surface set up:
    surface_set_target(argument0.surfaceZones);
    draw_clear_alpha(c_white, 0.5);
    
    draw_set_alpha(1);
    
    // drawing algorithm:
    
    var x1 = scr_getViewX1();
    var x2 = scr_getViewX2();
    var y1 = scr_getViewY1();
    var y2 = scr_getViewY2();
    
    var padding = 2;
    for (i = 0; i < scr_getNumZoneBuildings(argument0, Z_RES); i++) {
    

        
        var drawZoneBuilding = true;
        var zX = argument0.RzonesX[i];
        var zY = argument0.RzonesY[i];
        
        var ZT = argument0.RzonesZT[i];
        var L = argument0.RzonesL[i];
        var TV = argument0.RzonesTV[i];
        
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
            var index = scr_getZoneImageIndex(L, TV);
            draw_sprite(sprite, image_index, zX*TILE_SIZE - view_xview, zY*TILE_SIZE - view_yview);
        }
    } // end for loop
    
    
    surface_reset_target();
} // end if surface exists

