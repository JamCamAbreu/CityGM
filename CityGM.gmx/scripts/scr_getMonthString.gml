// argument0 = integer enum for season

switch (argument0) {

    case M_JAN:
        return "January  ";
        break;
        
    case M_FEB:
        return "February ";
        break;
        
    case M_MAR:
        return "March    ";
        break;
        
    case M_APR:
        return "April    ";
        break;        
        
    case M_MAY:
        return "May      ";
        break;
                
    case M_JUN:
        return "June     ";
        break;
                
    case M_JUL:
        return "July     ";
        break;
                
    case M_AUG:
        return "August  ";
        break;
                
    case M_SEP:
        return "September";
        break;
                
    case M_OCT:
        return "October  ";
        break;
                
    case M_NOV:
        return "November ";
        break;
                
    case M_DEC:
        return "December ";
        break;
        
    default:
        return "ERROR getMonthString";
        break;
}

return "ERROR getMonthString";
