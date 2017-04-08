// argument0 = building type

switch (argument0) {

    case BT_TREE:
        return "Tree";
        break;
        
    case BT_ROAD:
        return "Road";
        break;
        
    case BT_PLINE:
        return "Power Line";
        break;
        
    case BT_RZONE:
        return "Residential Zone";
        break;
        
    case BT_CZONE:
        return "Commercial Zone";
        break;
        
    case BT_IZONE:
        return "Industrial Zone";
        break;
        
    case BT_POLICE:
        return "Police Station";
        break;
        
    case BT_FIRE:
        return "Fire Station";
        break;
        
    case BT_SCHOOL:
        return "School";
        break;
        
    case BT_HOSPITAL:
        return "Hospital";
        break;
        
    case BT_COAL:
        return "Coal Power";
        break;
        
    case BT_NUCLEAR:
        return "Nuclear Power";
        break;
        
    case BT_WATERTOWER:
        return "Water Tower";
        break;
        
    case BT_ARCADE:
        return "Arcade";
        break;
        
    case BT_AIRPORT:
        return "Airport";
        break;
        
    default:
        return "error getBuildingString";
        break;
}

return "error getBuildingString";

