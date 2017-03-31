var miniMapDimension = MINIMAP_PIXEL*MAP_DIMENSION;

draw_set_font(ft_small);
var helpString = "'Q' for menus";

var mapX1 = BAR_IN_X1;
var mapY1 = BAR_IN_Y1;

draw_text_colour(mapX1, mapY1, helpString, c_white, c_white, c_white, c_white, 1);
draw_set_font(ft_normal);
