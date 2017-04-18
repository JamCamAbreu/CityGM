// stuff

draw_rectangle(MENU_MAP_X1, MENU_MAP_Y1, MENU_MAP_X1 + MENU_MAP_W, MENU_MAP_Y1 + MENU_MAP_H, false);

var i;
var amountOfButtons = 3;
var x1;
var y1;
for (i = 0; i < amountOfButtons; i++) {

    x1 = MENU_MAP_ICON_X1 + i*MENU_MAP_ICON + i*MENU_MAP_PAD;
    y1 = MENU_MAP_ICON_Y1;
    
    var sprite = scr_getMapIconSprites(i);
    draw_sprite(sprite, image_index, x1, y1);
}



