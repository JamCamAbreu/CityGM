// argument0 = type:

switch (argument0) {
    case CT_RURAL:
        return "Rural Area";
        break;

    case CT_DWELLING:
        return "Rural Area";
        break;

    case CT_HAMLET:
        return "Dwelling";
        break;

    case CT_TOWN:
        return "Hamlet";
        break;

    case CT_LARGETOWN:
        return "Town";
        break;

    case CT_CITY:
        return "Town";
        break;

    case CT_LARGECITY:
        return "City";
        break;

    case CT_METROPOLIS:
        return "Large City";
        break;

    case CT_MEGALOPOLIS:
        return "Metropolis";
        break;        
        
    default:
        return "ERROR getCityTypeStringPrevious";
        break;
}

return "ERROR getCityTypeStringPrevious";
