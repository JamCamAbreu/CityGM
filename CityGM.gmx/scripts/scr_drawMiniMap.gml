// argument0 is the id holding the surface

var miniMapDimension = MINIMAP_PIXEL*MAP_DIMENSION;

var mapX1 = view_xview + view_wview - miniMapDimension;
var mapY1 = view_yview + MENU_TB_HEIGHT;

var viewBorderWidth = round(miniMapDimension/(room_width/(view_wview)));
var viewBorderHeight = round(miniMapDimension/(room_height/(view_hview)));

// square border coordinates
var viewBorderX1 = mapX1 + floor((view_xview/room_width)*miniMapDimension);
var viewBorderX2 = viewBorderX1 + viewBorderWidth;
var viewBorderY1 = mapY1 + floor((view_yview/room_height)*miniMapDimension);
var viewBorderY2 = viewBorderY1 + viewBorderHeight;

// draw map and black border:
if (surface_exists(argument0.surfaceMiniMap)) {
    draw_set_alpha(1);
    draw_surface(surfaceMiniMap, mapX1, mapY1);
    
    // draw square border:
    draw_rectangle(viewBorderX1 - 1, viewBorderY1 - 1, viewBorderX2, viewBorderY2, true);

}





