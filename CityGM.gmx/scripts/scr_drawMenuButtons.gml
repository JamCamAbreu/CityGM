var i;
var amountOfButtons = 4;
var x1;
var y1;
var color = c_black;
for (i = 0; i < amountOfButtons; i++) {

    x1 = MENU_BUTTONS_X1 + i*MENU_BUTTONS_WIDTH + i*BAR_UNIT;
    y1 = MENU_BUTTONS_Y1;
    
    draw_rectangle_colour(x1, y1, x1 + MENU_BUTTONS_WIDTH, y1 + MENU_BUTTONS_HEIGHT, color, color, color, color, false);
    
}

