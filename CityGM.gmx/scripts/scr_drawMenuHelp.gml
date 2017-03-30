var miniMapDimension = MINIMAP_PIXEL*MAP_DIMENSION;

draw_set_font(ft_small);
var helpString = "'Q' for menus";

var mapX1 = view_xview + PAD_TITLE_LEFT;
var mapY1 = view_yview + PAD_TITLE_TOP;

draw_text_colour(mapX1, mapY1, helpString, c_white, c_white, c_white, c_white, 1);
draw_set_font(ft_normal);
