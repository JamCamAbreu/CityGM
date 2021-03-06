// argument0 = zone type
// argument1 = level
// argument2 = variation

// basis for all sprites:
var spriteName = "spr_";

// zone type:
if (argument0 == Z_RES)
    spriteName += "res";
else if (argument0 == Z_COM)
    spriteName += "com";
else if (argument0 == Z_IND)
    spriteName += "ind";

// level
spriteName += string(argument1);

// variation:
//var a = 97; // ASCII for 'a'
//spriteName += chr(a + argument2); // converts to a...b...etc..
var apparentlyNeedToUseItSomehow = argument2;

// Look up the sprite:
var ret = asset_get_index(spriteName);

// Sprite doesn't exist, return error sprite:
if (ret == -1) {
    //show_message("ERROR: sprite with name " + spriteName + " not found!");
    return spr_ZBerror;
}
// Sprite does exist, return it:
else
    return ret;

