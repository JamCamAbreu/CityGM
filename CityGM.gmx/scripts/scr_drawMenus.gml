


// debug:
//draw_set_alpha(1);
var dX1 = view_xview + BAR_PAD;
var dY1 = view_yview + BAR_PAD;
var dX2 = view_xview + view_wview - BAR_PAD;
var dY2 = dY1 + MENU_TB_HEIGHT - BAR_PAD*2;
draw_set_alpha(0.5);
scr_drawMenuTopBar();

/*
draw_rectangle_colour(BAR_IN_X1, BAR_IN_Y1, BAR_IN_X2, BAR_IN_Y2, c_orange, c_orange, c_orange, c_orange, true);

// DEBUG
var color;
var x1;
var x2;
var y1;
var y2;
var r;
var c;
for (r = 0; r < 6; r++) {
    for (c = 0; c < 59; c++) {
        x1 = BAR_IN_X1 + c*BAR_UNIT;
        x2 = x1 + BAR_UNIT;
        y1 = BAR_IN_Y1 + r*BAR_UNIT;
        y2 = y1 + BAR_UNIT;
        if ( (c) mod 8 == 0)
            color = c_blue;
        else if ( (r + c) mod 2 == 0)
            color = c_white;
        else
            color = c_red;
        draw_rectangle_colour(x1, y1, x2, y2, color, color, color, color, false);
    }
}
*/
draw_set_alpha(1);
scr_drawMenuButtons();

//scr_drawLeftBar();

