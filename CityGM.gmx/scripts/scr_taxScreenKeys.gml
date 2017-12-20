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











// HOLD BUTTON -----------------------------------

if (keyboard_check(ord('A'))) {
    // always increment:
    taxSelectTimer++;
    taxSelectPushTimer++;

    if (taxSelectTimer > TAX_SELECT_ALARM) {
        taxSelectBoostRate += TAX_SELECT_BOOST_AMOUNT;
        taxSelectTimer = 0;
    }

    // PUSH VALUE: 
    if (taxSelectPushTimer > TAX_SELECT_PUSH_ALARM) {
        if (argument0.curTaxItem == TAX_RES) {
            DLL_setTaxRate(TAX_RES, (resRate - taxSelectBoostRate));
            resRate = DLL_getTaxRate(TAX_RES);
        }
        else if (argument0.curTaxItem == TAX_COM) {
            DLL_setTaxRate(TAX_COM, (comRate - taxSelectBoostRate));
            comRate = DLL_getTaxRate(TAX_COM);
        }
        else if (argument0.curTaxItem == TAX_IND) {
            DLL_setTaxRate(TAX_IND, (indRate - taxSelectBoostRate));
            indRate = DLL_getTaxRate(TAX_IND);
        }
        
        // reset:
        taxSelectPushTimer = 0;
    } // end push value
}


else if (keyboard_check(ord('D'))) {
    // always increment:
    taxSelectTimer++;
    taxSelectPushTimer++;

    if (taxSelectTimer > TAX_SELECT_ALARM) {
        taxSelectBoostRate += TAX_SELECT_BOOST_AMOUNT;
        taxSelectTimer = 0;
    }

    // PUSH VALUE: 
    if (taxSelectPushTimer > TAX_SELECT_PUSH_ALARM) {
        if (argument0.curTaxItem == TAX_RES) {
            DLL_setTaxRate(TAX_RES, (resRate + taxSelectBoostRate));
            resRate = DLL_getTaxRate(TAX_RES);
        }
        else if (argument0.curTaxItem == TAX_COM) {
            DLL_setTaxRate(TAX_COM, (comRate + taxSelectBoostRate));
            comRate = DLL_getTaxRate(TAX_COM);
        }
        else if (argument0.curTaxItem == TAX_IND) {
            DLL_setTaxRate(TAX_IND, (indRate + taxSelectBoostRate));
            indRate = DLL_getTaxRate(TAX_IND);
        }
        
        // reset:
        taxSelectPushTimer = 0;
    } // end push value
}





// RELEASE BUTTON ---------------------------------

if (keyboard_check_released(ord('A'))) {
    taxSelectTimer = 0;
    taxSelectPushTimer = 0;
    taxSelectBoostRate = 0;
}
else if (keyboard_check_released(ord('D'))) {
    taxSelectTimer = 0;
    taxSelectPushTimer = 0;
    taxSelectBoostRate = 0;
}




