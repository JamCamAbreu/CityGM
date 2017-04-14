// argument0 = enum of which menu button

switch (argument0) {

    case MENU_DATA:
        return spr_menuData;
        break;
        
    case MENU_GRAPHS:
        return spr_menuGraphs;
        break;
        
    case MENU_MAPS:
        return spr_menuMaps;
        break;
        
    case MENU_FILE:
        return spr_menuFile;
        break;
        
    default:
        // ERROR
        return spr_DEBUG;
        break;

}

// ERROR:
return spr_DEBUG;
