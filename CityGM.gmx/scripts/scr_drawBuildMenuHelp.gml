var miniMapDimension = MINIMAP_PIXEL*MAP_DIMENSION;

draw_set_font(ft_small);
var helpString = "'E' to build";

draw_text_colour(BUILDMENU_X1, BUILDMENU_Y1, helpString, c_white, c_white, c_white, c_white, 1);
draw_set_font(ft_normal);
