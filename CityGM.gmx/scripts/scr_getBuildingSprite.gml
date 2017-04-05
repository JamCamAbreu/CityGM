// argument0 = enum to check


switch (argument0) {
    
    case BT_TREE:
        return spr_tree;
        break;
        
    case BT_ROAD:
        return spr_road;
        break;
        
    case BT_PLINE:
        return spr_powerLine;
        break;
        
    case BT_RZONE:
        return spr_zone;
        break;
        
    case BT_CZONE:
        return spr_zone;
        break;

    case BT_IZONE:
        return spr_zone;
        break;
        
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
        
    case BT_COAL:
        return spr_coalPlant;
        break;
        
    case BT_NUCLEAR:
        return spr_nucPlant;
        break;
        
    case BT_WATERTOWER:
        return spr_waterTower;
        break;
        
    case BT_ARCADE:
        return spr_arcade;
        break;
        
    case BT_AIRPORT:
        return spr_airport;
        break;
        
    default:
        return spr_DEBUG;
        break;
}


return spr_DEBUG;
