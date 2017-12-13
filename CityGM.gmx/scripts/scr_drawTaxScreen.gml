// argument0 = id of obj_main


var centerX = (view_xview + view_wview/2);
var yLine = (view_hview)/12;

// black outer box:
draw_rectangle(view_xview, view_yview, view_xview + view_wview, view_yview + view_hview, false);
    
// blue inner box:
var pad = 16;
draw_rectangle_colour(view_xview + pad, view_yview + pad, view_xview + view_wview - pad, view_yview + view_hview - pad, c_navy, c_navy, c_blue, c_blue, false);

// TITLE
draw_set_colour(c_white);
draw_set_font(ft_title);
var title = "TAX";
draw_text(centerX - (string_width(title)/2), view_yview + yLine*2, title);

// Tax Rates:
var indent1 = pad + 128;
draw_set_font(ft_normal);

// Current Selected:
var curSelected = argument0.curTaxItem;
var selectedHeight = 16;
drawSelectedY = view_yview + yLine*(4 + curSelected);
var selectedColor = make_colour_hsv(128, 128, 200);
draw_rectangle_colour(view_xview + pad, drawSelectedY, view_xview + view_wview - pad, drawSelectedY + selectedHeight, selectedColor, selectedColor, selectedColor, selectedColor, false);
var decrease = "<-- (-)";
draw_text(view_xview + indent1 - string_width(decrease) - 8, drawSelectedY, decrease);
var increase = "(+) -->";
var dummyText = "Residential Tax Rate: 99";
draw_text(view_xview + indent1 + string_width(dummyText) + 8, drawSelectedY, increase);

// RESIDENTIAL:
var resRate = "Residential Tax Rate: " + string(argument0.resRate);
draw_text(view_xview + indent1, view_yview + yLine*4, resRate);

// COMMERCIAL:
var comRate = "Commercial Tax Rate: " + string(argument0.comRate);
draw_text(view_xview + indent1, view_yview + yLine*5, comRate);

// INDUSTRIAL:
var indRate = "Industrial Tax Rate: " + string(argument0.indRate);
draw_text(view_xview + indent1, view_yview + yLine*6, indRate);



