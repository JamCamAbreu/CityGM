var miniMapDimension = MINIMAP_PIXEL*MAP_DIMENSION;

draw_set_font(ft_small);
var helpString = "'C' for menus";

var color = c_white;
var season = DLL_getGameSeason();
if (season == S_WINTER)
    color = c_black;
    
draw_text_colour(BAR_IN_X1, BAR_IN_Y1, helpString, color, color, color, color, 1);
draw_set_font(ft_normal);
