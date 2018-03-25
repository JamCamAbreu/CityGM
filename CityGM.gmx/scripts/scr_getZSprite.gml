// argument0 = zone type
// argument1 = level
// argument2 = variation
// argument3 = shape Type (pass in SHAPE_BASIC for example, see macros)

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


// special shapes:
switch (argument3) {
    case SHAPE_BASIC: // no need to add any string name
        break;
        
    case SHAPE_TLC:
        spriteName += "TLC";
        break;
        
    case SHAPE_TRC:
        spriteName += "TRC";
        break;
        
    case SHAPE_BLC:
        spriteName += "BLC";
        break;
        
    case SHAPE_BRC:
        spriteName += "BRC";
        break;
        
    case SHAPE_BOX:
        spriteName += "Box";
        break;
        
    // lines:
    case SHAPE_H:
        spriteName += "H";
        break;
        
    case SHAPE_V:
        spriteName += "V";
        break;
        
    case SHAPE_ALL:
        spriteName += "All";
        break;
        
    case SHAPE_DONUT:
        spriteName += "Donut";
        break;
        
    case SHAPE_CROSS:
        spriteName += "Cross";
        break;
        
    default:
        spriteName += "err";
} // end variation switch




    
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

