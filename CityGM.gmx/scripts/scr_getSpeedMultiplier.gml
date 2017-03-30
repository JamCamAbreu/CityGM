// argument0 = gameSpeed

switch (argument0) {

    case SP_PAUSE:
        return TIME_MUL_PAUSE;
        break;
        
    case SP_SLOW:
        return TIME_MUL_SLOW;
        break;
        
    case SP_NORMAL:
        return TIME_MUL_NORMAL;
        break;
        
    case SP_FAST:
        return TIME_MUL_FAST;
        break;
        
    default:
        return TIME_MUL_NORMAL;
        break;
}

return TIME_MUL_NORMAL;
