// argument0 = id of obj_main





var centerX = (view_xview + view_wview/2);
var yLine = (view_hview)/12;

// black outer box:
draw_rectangle(view_xview, view_yview, view_xview + view_wview, view_yview + view_hview, false);
    
// blue inner box:
var pad = 16;
draw_rectangle_colour(view_xview + pad, view_yview + pad, view_xview + view_wview - pad, view_yview + view_hview - pad, c_navy, c_navy, c_blue, c_blue, false);


// draw document background sprite
draw_sprite_ext(spr_documentBackground, image_index, view_xview + pad + 4, view_yview + pad + 4, 0.25, 0.25, 0, c_white, 0.4);


// TITLE
draw_set_colour(c_white);
draw_set_font(ft_title);
var title = "TAX";
draw_set_colour(c_black);
draw_text(centerX - (string_width(title)/2), view_yview + yLine*2, title);
draw_set_colour(c_white);
draw_text(centerX - (string_width(title)/2) + 2, view_yview + yLine*2 + 2, title);

// Tax Rates:
var indent1 = pad + 128;
draw_set_font(ft_normal);

// Current Selected:
var curSelected = argument0.curTaxItem;
var selectedHeight = 16;
drawSelectedY = view_yview + yLine*(4 + curSelected);
var selectedColor = make_colour_hsv(128, 128, 200);
draw_rectangle_colour(view_xview + pad, drawSelectedY, view_xview + view_wview - pad, drawSelectedY + selectedHeight, selectedColor, selectedColor, selectedColor, selectedColor, false);
var decrease = "<<< (-)";
var increase = "(+) >>>";
var dummyText = "Residential Tax Rate: 99";

draw_set_colour(c_black);
draw_text(view_xview + indent1 - string_width(decrease) - 8, drawSelectedY, decrease);
draw_text(view_xview + indent1 + string_width(dummyText) + 8, drawSelectedY, increase);
draw_set_colour(c_white);
draw_text(view_xview + indent1 - string_width(decrease) - 8 + 1, drawSelectedY + 1, decrease);
draw_text(view_xview + indent1 + string_width(dummyText) + 8 + 1, drawSelectedY + 1, increase);


// RESIDENTIAL:
var resRate = "Residential Tax Rate: " + string(argument0.resRate);
draw_set_colour(c_black);
draw_text(view_xview + indent1, view_yview + yLine*4, resRate);
draw_set_colour(c_white);
draw_text(view_xview + indent1 + 1, view_yview + yLine*4 + 1, resRate);

// COMMERCIAL:
var comRate = "Commercial Tax Rate: " + string(argument0.comRate);
draw_set_colour(c_black);
draw_text(view_xview + indent1, view_yview + yLine*5, comRate);
draw_set_colour(c_white);
draw_text(view_xview + indent1 + 1, view_yview + yLine*5 + 1, comRate);

// INDUSTRIAL:
var indRate = "Industrial Tax Rate: " + string(argument0.indRate);
draw_set_colour(c_black);
draw_text(view_xview + indent1, view_yview + yLine*6, indRate);
draw_set_colour(c_white);
draw_text(view_xview + indent1 + 1, view_yview + yLine*6 + 1, indRate);

// Press to Quit
var pressToQuit = "~Press 'Q' or '8' to exit#Tax screen and apply changes~";
draw_set_colour(c_black);
var centerIt = centerX - (string_width("~Press 'Q' or '8' to exit")/2);
draw_text(centerIt, view_yview + yLine*8, pressToQuit); // shadow
draw_set_colour(c_white);
draw_text(centerIt + 1, view_yview + yLine*8 + 1, pressToQuit); // actual text

