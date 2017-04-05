var miniMapDimension = MINIMAP_PIXEL*MAP_DIMENSION;

draw_set_font(ft_small);
var helpString = "'Q' to cancel";

draw_text_colour(view_xview + (view_wview/2) - (string_width(helpString)), BUILDMENU_Y1, helpString, c_white, c_white, c_white, c_white, 1);
draw_set_font(ft_normal);
