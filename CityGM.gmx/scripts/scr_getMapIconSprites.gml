// argument 0 = index

switch (argument0) {

    case MENU_MAP_OVERVIEW:
        return spr_MapsOverview;
        break;
        
    case MENU_MAP_POLLUTION:
        return spr_MapsPollution;
        break;
        
    case MENU_MAP_LANDVALUE:
        return spr_MapsError;
        break;

    default:
        return spr_MapsError;
        break;
}

// error:
return spr_MapsError;
