// argument0 = type:

switch (argument0) {
    case CT_RURAL:
        return "Rural Area";
        break;

    case CT_DWELLING:
        return "Dwelling";
        break;

    case CT_HAMLET:
        return "Hamlet";
        break;

    case CT_TOWN:
        return "Town";
        break;

    case CT_LARGETOWN:
        return "Large Town";
        break;

    case CT_CITY:
        return "City";
        break;

    case CT_LARGECITY:
        return "Large City";
        break;

    case CT_METROPOLIS:
        return "Metropolis";
        break;

    case CT_MEGALOPOLIS:
        return "Megalopolis";
        break;        
        
    default:
        return "ERROR getCityTypeString";
        break;
}

return "ERROR getCityTypeString";
