

// argument0 = char to check

switch (argument0) {

    case CHAR_GRASS:
        return c_green;
        break;
        
    case CHAR_TREE:
        return c_lime;
        break;
        
    case CHAR_BUILDING:
        return c_gray;
        break;
        
    case CHAR_WATER:
        return c_navy;
        break;
        
    case CHAR_ERROR:
        return c_orange;
        break;
        
    case CHAR_RZONE:
        return c_red;
        break;
        
    case CHAR_CZONE:
        return c_blue;
        break;
        
    case CHAR_IZONE:
        return c_yellow;
        break;
        
    default:
        return c_orange;
        break;
}

return c_orange;
