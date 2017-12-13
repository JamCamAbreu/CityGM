// argument0 is the id holding the variables

//argument0.curTaxItem = TAX_ITEM_RES;


// A key to move left:

if (keyboard_check_pressed(ord('A'))) {
    if (argument0.curTaxItem == TAX_RES) {
        DLL_setTaxRate(TAX_RES, (resRate - 1));
        resRate = DLL_getTaxRate(TAX_RES);
    }
    else if (argument0.curTaxItem == TAX_COM) {
        DLL_setTaxRate(TAX_COM, (comRate - 1));
        comRate = DLL_getTaxRate(TAX_COM);
    }
    else if (argument0.curTaxItem == TAX_IND) {
        DLL_setTaxRate(TAX_IND, (indRate - 1));
        indRate = DLL_getTaxRate(TAX_IND);
    }
}


// D key to move right:
else if (keyboard_check_pressed(ord('D'))) {
    if (argument0.curTaxItem == TAX_RES) {
        DLL_setTaxRate(TAX_RES, (resRate + 1));
        resRate = DLL_getTaxRate(TAX_RES);
    }
    else if (argument0.curTaxItem == TAX_COM) {
        DLL_setTaxRate(TAX_COM, (comRate + 1));
        comRate = DLL_getTaxRate(TAX_COM);
    }
    else if (argument0.curTaxItem == TAX_IND) {
        DLL_setTaxRate(TAX_IND, (indRate + 1));
        indRate = DLL_getTaxRate(TAX_IND);
    }
}



// CHANGE CURRENT TAX ITEM:
// W key to move up:
if (keyboard_check_pressed(ord('W'))) {
    if (argument0.curTaxItem == 0)
        argument0.curTaxItem += (TAX_ITEMS - 1); // wrap
    else
        argument0.curTaxItem -= 1;
}


// S key to move down:
else if (keyboard_check_pressed(ord('S'))) {
    if (argument0.curTaxItem == (TAX_ITEMS - 1))
        argument0.curTaxItem = 0; // wrap
    else
        argument0.curTaxItem += 1;
}

