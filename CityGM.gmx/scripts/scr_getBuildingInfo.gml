// Get's info about a building with a given x and y
// If a building does not exist there, it will say so

// argument0: x
// argument1: y


var curX = argument0;
var curY = argument1;


var type = DLL_getBuildingInfo(BDT_TYPE, curX, curY);
var size = DLL_getBuildingInfo(BDT_SIZE, curX, curY);
var curPower = DLL_getBuildingInfo(BDT_CURPOWER, curX, curY);
var reqPower = DLL_getBuildingInfo(BDT_REQPOWER, curX, curY);
var pollution = DLL_getBuildingInfo(BDT_POLLUTION, curX, curY);
var LVB = DLL_getBuildingInfo(BDT_LANDVALUEBOOST, curX, curY);

show_message(   "BUILDING INFO: " + 
                "##Type: " + type + 
                "#Dimensions: " + size + " by " + size +
                "#Current Power: " + curPower + 
                "#Required Power: " + reqPower + 
                "#Pollution Factor: " + pollution + 
                "#Land Value Boost: " + LVB);

