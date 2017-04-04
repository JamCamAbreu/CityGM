var miniMapDimension = MINIMAP_PIXEL*MAP_DIMENSION;

draw_set_font(ft_small);
var helpString = "'C' for menus";

draw_text_colour(BAR_IN_X1, BAR_IN_Y1, helpString, c_white, c_white, c_white, c_white, 1);
draw_set_font(ft_normal);
