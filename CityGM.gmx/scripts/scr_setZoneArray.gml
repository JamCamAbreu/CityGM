// argument0 = id of the object holding the variables
// argument1 = zone type
// argument2 = element type
// argument3 = value to add
// argument4 = zoneBuilding Number (array index number)

// element types:
// 0 = x
// 1 = y
// 2 = zone type
// 3 = level
// 4 = type variation
// 5 = square position


if (argument1 == Z_RES) {
    if (argument2 == 0)
        argument0.RzonesX[argument4] = argument3;

    else if (argument2 == 1)
        argument0.RzonesY[argument4] = argument3;

    else if (argument2 == 2)
        argument0.RzonesZT[argument4] = argument3;

    else if (argument2 == 3)
        argument0.RzonesL[argument4] = argument3;

    else if (argument2 == 4)
        argument0.RzonesTV[argument4] = argument3;
        
    else if (argument2 == 5)
        argument0.RzonesSP[argument4] = argument3;
}



else if (argument1 == Z_COM) {
    if (argument2 == 0)
        argument0.CzonesX[argument4] = argument3;

    else if (argument2 == 1)
        argument0.CzonesY[argument4] = argument3;

    else if (argument2 == 2)
        argument0.CzonesZT[argument4] = argument3;

    else if (argument2 == 3)
        argument0.CzonesL[argument4] = argument3;

    else if (argument2 == 4)
        argument0.CzonesTV[argument4] = argument3;
        
    else if (argument2 == 5)
        argument0.CzonesSP[argument4] = argument3;
}


else if (argument1 == Z_IND) {

    if (argument2 == 0)
        argument0.IzonesX[argument4] = argument3;

    else if (argument2 == 1)
        argument0.IzonesY[argument4] = argument3;

    else if (argument2 == 2)
        argument0.IzonesZT[argument4] = argument3;

    else if (argument2 == 3)
        argument0.IzonesL[argument4] = argument3;

    else if (argument2 == 4)
        argument0.IzonesTV[argument4] = argument3;
        
    else if (argument2 == 5)
        argument0.IzonesSP[argument4] = argument3;
}
    
    
