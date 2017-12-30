// argument0 == id holding variables

if (argument0.gameMode != MD_TAX) {
    // update tax rates first:
    argument0.resRate = DLL_getTaxRate(TAX_RES);
    argument0.comRate = DLL_getTaxRate(TAX_COM);
    argument0.indRate = DLL_getTaxRate(TAX_IND);
    
    // change game state:
    DLL_setGameMode(MD_TAX);
    argument0.gameMode = DLL_getGameMode();
    argument0.canDraw = false;
    argument0.curTaxItem = TAX_ITEM_RES; // first selected item
    scr_setSpeed(argument0, SP_PAUSE);
}

