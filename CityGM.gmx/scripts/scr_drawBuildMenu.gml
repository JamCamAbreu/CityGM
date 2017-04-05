draw_rectangle(BUILDMENU_X1, BUILDMENU_Y1, BUILDMENU_X1 + BUILDMENU_W, BUILDMENU_Y1 + BUILDMENU_H, false);

// row 0:
draw_sprite(spr_PIconTree, image_index, BUILDICON_X1, BUILDICON_Y1);
draw_sprite(spr_PIconRoad, image_index, BUILDICON2_X1, BUILDICON_Y1);
draw_sprite(spr_PIconPLine, image_index, BUILDICON3_X1, BUILDICON_Y1);

// row 1:
draw_sprite(spr_PIconRZone, image_index, BUILDICON_X1, BUILDICON_Y1 + BUILDICON_H*1 + BUILDICON_PAD*1);
draw_sprite(spr_PIconCZone, image_index, BUILDICON2_X1, BUILDICON_Y1 + BUILDICON_H*1 + BUILDICON_PAD*1);
draw_sprite(spr_PIconIZone, image_index, BUILDICON3_X1, BUILDICON_Y1 + BUILDICON_H*1 + BUILDICON_PAD*1);

// row 2:
draw_sprite(spr_PIconPStation, image_index, BUILDICON_X1, BUILDICON_Y1 + BUILDICON_H*2 + BUILDICON_PAD*2);
draw_sprite(spr_PIconFStation, image_index, BUILDICON2_X1, BUILDICON_Y1 + BUILDICON_H*2 + BUILDICON_PAD*2);
draw_sprite(spr_PIconSchool, image_index, BUILDICON3_X1, BUILDICON_Y1 + BUILDICON_H*2 + BUILDICON_PAD*2);

// row 3:
draw_sprite(spr_PIconHospital, image_index, BUILDICON_X1, BUILDICON_Y1 + BUILDICON_H*3 + BUILDICON_PAD*3);
draw_sprite(spr_PIconCoalPlant, image_index, BUILDICON2_X1, BUILDICON_Y1 + BUILDICON_H*3 + BUILDICON_PAD*3);
draw_sprite(spr_PIconNucPlant, image_index, BUILDICON3_X1, BUILDICON_Y1 + BUILDICON_H*3 + BUILDICON_PAD*3);


// row 4:
draw_sprite(spr_PIconWaterTower, image_index, BUILDICON_X1, BUILDICON_Y1 + BUILDICON_H*4 + BUILDICON_PAD*4);
draw_sprite(spr_PIconArcade, image_index, BUILDICON2_X1, BUILDICON_Y1 + BUILDICON_H*4 + BUILDICON_PAD*4);
draw_sprite(spr_PIconAirport, image_index, BUILDICON3_X1, BUILDICON_Y1 + BUILDICON_H*4 + BUILDICON_PAD*4);


// draw selected:

var selectedRow = scr_buildMenuGetRow(argument0.selectedBuilding);
var selectedColumn = scr_buildMenuGetColumn(argument0.selectedBuilding);
var selectedX = BUILDICON_X1 + BUILDICON_W*selectedColumn + BUILDICON_PAD*selectedColumn;
var selectedY = BUILDICON_Y1 + BUILDICON_H*selectedRow + BUILDICON_PAD*selectedRow;
draw_sprite(spr_PIconSelect, image_index, selectedX, selectedY);
