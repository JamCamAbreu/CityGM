var miniMapDimension = MINIMAP_PIXEL*MAP_DIMENSION;

draw_set_font(ft_small);
var helpString = "'M' for map";

var mapX1 = view_xview + view_wview - miniMapDimension/2 - string_width(helpString)/2;
var mapY1 = view_yview + MENU_TB_HEIGHT + 4;



draw_text_colour(mapX1, mapY1, helpString, c_white, c_white, c_white, c_white, 1);
draw_set_font(ft_normal);
