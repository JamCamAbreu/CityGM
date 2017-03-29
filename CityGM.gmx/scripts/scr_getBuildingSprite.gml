// argument0 = enum to check


switch (argument0) {

    case BT_POLICE:
        return spr_polStation;
        break;
        
    case BT_FIRE:
        return spr_fireStation;
        break;
        
    case BT_SCHOOL:
        return spr_school;
        break;
        
    case BT_HOSPITAL:
        return spr_hospital;
        break;
        
    case BT_NUCLEAR:
        return spr_nucPlant;
        break;
        
    case BT_AIRPORT:
        return spr_airport;
        break;
        
        
    case BT_WATERTOWER:
        return spr_DEBUG;
        break;
        
    case BT_ARCADE:
        return spr_DEBUG;
        break;
        
    case BT_GYM:
        return spr_DEBUG;
        break;
        
    default:
        return spr_DEBUG;
        break;
}


return spr_DEBUG;
