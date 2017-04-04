draw_rectangle(BUILDMENU_X1, BUILDMENU_Y1, BUILDMENU_X1 + BUILDMENU_W, BUILDMENU_Y1 + BUILDMENU_H, false);

/*
var c;
var r;
var numIconsH = 7;
var numIconsW = 2;
var sprite;
for (c = 0; c < numIconsW; c++) {
    for (r = 0; r < numIconsH; r++) {

    
    }
}
*/

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
draw_sprite(spr_purchaseIcon, image_index, BUILDICON_X1, BUILDICON_Y1 + BUILDICON_H*4 + BUILDICON_PAD*4);
draw_sprite(spr_purchaseIcon, image_index, BUILDICON2_X1, BUILDICON_Y1 + BUILDICON_H*4 + BUILDICON_PAD*4);
draw_sprite(spr_purchaseIcon, image_index, BUILDICON3_X1, BUILDICON_Y1 + BUILDICON_H*4 + BUILDICON_PAD*4);
