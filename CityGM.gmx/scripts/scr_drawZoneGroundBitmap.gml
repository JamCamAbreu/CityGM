// argument0 : x
// argument1 : y
// argument2 : season
// argument3 : shape bitmap code


var T = TILE_SIZE;
var shape = argument3;

var c1 = argument0;
var c2 = argument0 + T;
var c3 = argument0 + T*2;

var r1 = argument1;
var r2 = argument1 + T;
var r3 = argument1 + T*2;

var spr = spr_ground;
var season = argument2;

// TOP LEFT
if (shape & BM_TL == BM_TL) {
    draw_sprite(spr, season, c1, r1);
}

// TOP
if (shape & BM_T == BM_T) {
    draw_sprite(spr, season, c2, r1);
}

// TOP RIGHT
if (shape & BM_TR == BM_TR) {
    draw_sprite(spr, season, c3, r1);
}

// LEFT
if (shape & BM_L == BM_L) {
    draw_sprite(spr, season, c1, r2);
}

// MIDDLE
if (shape & BM_M == BM_M) {
    draw_sprite(spr, season, c2, r2);
}

// RIGHT
if (shape & BM_R == BM_R) {
    draw_sprite(spr, season, c3, r2);
}

// BOTTOM LEFT
if (shape & BM_BL == BM_BL) {
    draw_sprite(spr, season, c1, r3);
}

// BOTTOM
if (shape & BM_B == BM_B) {
    draw_sprite(spr, season, c2, r3);
}

// BOTTOM RIGHT
if (shape & BM_BR == BM_BR) {
    draw_sprite(spr, season, c3, r3);
}







