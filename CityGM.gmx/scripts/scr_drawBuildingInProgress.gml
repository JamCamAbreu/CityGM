var myString = "Building In Progress...";

draw_set_font(ft_title);

var textX = BUILDINGINFO_X1 - string_width(myString)/2;
var textY = BUILDINGINFO_Y1;


var boxPad = 8;
draw_set_alpha(0.5);
draw_rectangle_colour(textX - boxPad, 
    view_yview + MENU_TB_HEIGHT + 1, 
    textX + string_width(myString) + boxPad, 
    textY + string_height(myString) + boxPad, 
    c_black, c_black, c_black, c_black, false);

draw_text_colour(textX + 1, textY + 1, myString, c_black, c_black, c_black, c_black, 1);
draw_text_colour(textX + 2, textY + 1, myString, c_black, c_black, c_black, c_black, 1);
draw_text_colour(textX, textY, myString, c_white, c_white, c_white, c_white, 1);

draw_set_font(ft_normal);

