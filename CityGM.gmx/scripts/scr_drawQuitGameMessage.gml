// argument0 = id of instance holding variables

var quit_m1 = argument0.quit_m1;
var quit_m2 = argument0.quit_m2;
var quit_m3 = argument0.quit_m3;

var centerX = view_xview + view_wview/2;
var quitY = view_yview + view_hview/3;
var Qcolor = c_yellow; 

// black box:
var x1 = view_xview + view_wview/10;
var y1 = quitY - view_hview/12;
var x2 = view_xview + view_wview - view_wview/10;
var y2 = quitY + view_hview/4;
draw_roundrect_colour_ext(x1, y1, x2, y2, 120, 60, c_black, c_black, false); 
//draw_roundrect_colour_ext(x1, y1, x2, y2, xrad, yrad, col1, col2, outline);

draw_set_font(ft_title);
draw_text_colour(centerX - string_width(quit_m1)/2, quitY, quit_m1, Qcolor, Qcolor, Qcolor, Qcolor, 1);
quitY += (string_height(quit_m1) + 8);

draw_set_font(ft_normal);
draw_text_colour(centerX - string_width(quit_m2)/2, quitY, quit_m2, Qcolor, Qcolor, Qcolor, Qcolor, 1);
quitY += (string_height(quit_m2) + 8);
draw_text_colour(centerX - string_width(quit_m3)/2, quitY, quit_m3, Qcolor, Qcolor, Qcolor, Qcolor, 1);

