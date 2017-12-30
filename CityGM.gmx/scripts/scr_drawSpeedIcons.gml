// draw each of the speed icons

// TODO: highlight cur speed
var spriteWidth = 32;
var spriteHeight = 32;
// bar behind:
draw_set_alpha(MENU_ALPHA);
draw_roundrect_ext(SPEEDICON_X1 - 4, SPEEDICON_Y1 - 4, SPEEDICON_X1 + spriteWidth*4 + 4, SPEEDICON_Y1 + spriteHeight + 4, 10, 10, false);
draw_set_alpha(1);
var selected = 0;

// pause
if (DLL_getGameSpeed() == SP_PAUSE)
    selected = 1;
draw_sprite(spr_SPpause, selected, SPEEDICON_X1 + spriteWidth*0, SPEEDICON_Y1);
selected = 0;


// slow
if (DLL_getGameSpeed() == SP_SLOW)
    selected = 1;
draw_sprite(spr_SPslow, selected, SPEEDICON_X1 + spriteWidth*1, SPEEDICON_Y1);
selected = 0;

// normal
if (DLL_getGameSpeed() == SP_NORMAL)
    selected = 1;
draw_sprite(spr_SPnormal, selected, SPEEDICON_X1 + spriteWidth*2, SPEEDICON_Y1);
selected = 0;

// fast
if (DLL_getGameSpeed() == SP_FAST)
    selected = 1;
draw_sprite(spr_SPfast, selected, SPEEDICON_X1 + spriteWidth*3, SPEEDICON_Y1);


