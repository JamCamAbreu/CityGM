

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
        return c_blue;
        break;
        
    case CHAR_ERROR:
        return c_orange;
        break;
        
    default:
        return c_orange;
        break;
}

return c_orange;
