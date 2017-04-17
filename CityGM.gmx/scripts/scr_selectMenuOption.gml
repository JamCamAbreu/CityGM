// argument0 = ID of the object holding the variables.

switch (argument0.selectedMenu) {

    case MENU_TAX:
        DLL_setGameMode(MD_TAX);
        break;
        
    case MENU_GRAPHS:
        DLL_setGameMode(MD_GRAPHS);
        break;
        
    case MENU_MAPS:
        DLL_setGameMode(MD_MAPS);
        break;
        
    case MENU_FILE:
        DLL_setGameMode(MD_FILE);
        break;
        
    default:
        break;
}

argument0.gameMode = DLL_getGameMode();


