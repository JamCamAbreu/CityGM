// argument0 = id holding the string to be drawn

var textX = BUILDINGINFO_X1 - string_width(argument0.selectedBuildingString)/2;
var textY = BUILDINGINFO_Y1;


var boxPad = 8;
draw_set_alpha(0.5);
draw_rectangle_colour(textX - boxPad, 
    view_yview + MENU_TB_HEIGHT + 1, 
    textX + string_width(argument0.selectedBuildingString) + boxPad, 
    textY + string_height(argument0.selectedBuildingString) + boxPad, 
    c_black, c_black, c_black, c_black, false);



draw_text_colour(textX + 1, textY + 1, argument0.selectedBuildingString, c_black, c_black, c_black, c_black, 1);
draw_text_colour(textX + 2, textY + 1, argument0.selectedBuildingString, c_black, c_black, c_black, c_black, 1);
draw_text_colour(textX, textY, argument0.selectedBuildingString, c_white, c_white, c_white, c_white, 1);






