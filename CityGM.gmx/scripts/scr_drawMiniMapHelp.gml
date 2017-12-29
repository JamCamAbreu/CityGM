var miniMapDimension = MINIMAP_PIXEL*MAP_DIMENSION;

draw_set_font(ft_small);
var helpString = "'M' for map";

var mapX1 = view_xview + view_wview - miniMapDimension/2 - string_width(helpString)/2;
var mapY1 = view_yview + MENU_TB_HEIGHT + 4;

var color = c_white;
var season = DLL_getGameSeason();
if (season == S_WINTER)
    color = c_black;

draw_text_colour(mapX1, mapY1, helpString, color, color, color, color, 1);
draw_set_font(ft_normal);
