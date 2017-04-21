// argument0 contains the variables

// black box:
draw_rectangle(MENU_MAP_D_X1, MENU_MAP_D_Y1, MENU_MAP_D_X1 + MENU_MAP_W, MENU_MAP_D_Y1 + MENU_MAP_D_H, false);

// description:
var description;
var description2;
var description3;
switch (argument0.selectedMap) {

    case MENU_MAP_OVERVIEW:
        description = "Overview Map: Contains basic data including water, vegetation, and building locations.";
        break;
        
    case MENU_MAP_POLLUTION:
        description = "Pollution Map: Contains information about the pollution caused by your buildings, zones, and other factors.";
        break;
        
    case MENU_MAP_LANDVALUE:
        description = "Land Value: High land value boosts zone development. Pollution and other factors come into play.";
        break;

    case 3:
        description = "Map 4: Coming soon!";
        break;
        
    case 4:
        description = "Map 5: Coming soon!";
        break;
        
        
    default:
        description = "scr_drawMapDescription ERROR";
}

// add locked string:
if (argument0.mapUnlocked[argument0.selectedMap] == false) {
    var posLock = 0;
    var locked = " (Locked) ";
    while (string_char_at(description, posLock) != ':') {
        posLock++;
    }
    
    // insert string:
    description = string_insert(locked, description, posLock);
}

var descriptionTop = "";
var description2 = "";
var description3 = "";


// chop string into second line:
var pos = 1;
var stringWidth;
var char = "";
while (pos < string_length(description) && (string_width(descriptionTop) < MENU_MAP_W - 80)) {
    char = string_char_at(description, pos);
    while ((char != ' ') && (pos < string_length(description))) {
        descriptionTop += char;
        pos++;
        char = string_char_at(description, pos);
    }
    descriptionTop += char;
    pos++;
}

// chop string into third line
while (pos < string_length(description) && (string_width(description2) < MENU_MAP_W - 80)) {
    char = string_char_at(description, pos);
    while ((char != ' ') && (pos < string_length(description))) {
        description2 += char;
        pos++;
        char = string_char_at(description, pos);
    }
    description2 += char;
    pos++;
}


// copy the rest into line 3:
if (string_width(description2) >= MENU_MAP_W - 80)
    description3 = string_copy(description, pos, (string_length(description) - pos + 1));



draw_text_colour(MENU_MAP_D_X1 + 8, MENU_MAP_D_Y1 + 4, descriptionTop, c_white, c_white, c_white, c_white, 1);
draw_text_colour(MENU_MAP_D_X1 + 8, MENU_MAP_D_Y1 + 16, description2, c_white, c_white, c_white, c_white, 1);
draw_text_colour(MENU_MAP_D_X1 + 8, MENU_MAP_D_Y1 + 28, description3, c_white, c_white, c_white, c_white, 1);


