// argument0 = id holding variables
// argument1 = amount to add

///TEST population increase
var amount = argument1;
var newCityType = DLL_setPopulation(argument0.gamePopulation + amount);
argument0.gamePopulation = DLL_getPopulation();

if (newCityType) {
    var type = DLL_getCityType();
    var oldType = scr_getCityTypeStringPrevious(type);
    var newType = scr_getCityTypeString(type);
    var congrats = "Congratulations! Your " + oldType + " has now grown into a " + newType + "!"
    show_message(congrats);
}
