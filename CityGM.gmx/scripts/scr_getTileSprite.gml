

// argument0 = char to check

switch (argument0) {

    case CHAR_GRASS:
        return spr_ground;
        break;
        
    case CHAR_TREE:
        return spr_tree;
        break;
        
    case CHAR_BUILDING:
        return spr_empty;
        break;
        
    case CHAR_WATER:
        return spr_water;
        break;
        
    case CHAR_RZONE:
        return spr_dirt;
        break;
        
    case CHAR_CZONE:
        return spr_dirt;
        break;
        
    case CHAR_IZONE:
        return spr_dirt;
        break;
        
    case CHAR_ERROR:
        return spr_zoneError;
        break;
        
    default:
        return spr_zoneError;
        break;
}

return spr_zoneError;
