

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
        
    case CHAR_ERROR:
        return spr_icon;
        break;
        
    default:
        return spr_icon;
        break;
}

return spr_icon;
