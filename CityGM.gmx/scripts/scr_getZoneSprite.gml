// argument0 = zone type


if (argument0 == Z_RES)
    return spr_zoneR;
    
else if (argument0 == Z_COM)
    return spr_zoneC;
    
else if (argument0 == Z_IND)
    return spr_zoneI;
    

else return spr_zoneError;
