// argument0 contains the variables

// black box:
draw_rectangle(MENU_MAP_D_X1, MENU_MAP_D_Y1, MENU_MAP_D_X1 + MENU_MAP_W, MENU_MAP_D_Y1 + MENU_MAP_D_H, false);

// description:
var description;
var description2;
switch (argument0.selectedMap) {

    case MENU_MAP_OVERVIEW:
        description = "Overview Map: Contains basic data including water, vegetation, and building locations.";
        break;
        
    case MENU_MAP_POLLUTION:
        description = "Pollution Map: Contains information about the pollution caused by your buildings and zones.";
        break;
        
    case MENU_MAP_LANDVALUE:
        description = "Land Value: Coming soon!";
        break;

    default:
        description = "scr_drawMapDescription ERROR";
}


var descriptionTop = "";
var descriptionBottom = "";

var pos = 1;
var stringWidth;
var char = "";
while (pos < string_length(description) && (string_width(descriptionTop) < MENU_MAP_W - 50)) {
    char = string_char_at(description, pos);
    while ((char != ' ') && (pos < string_length(description))) {
        descriptionTop += char;
        pos++;
        char = string_char_at(description, pos);
    }
    descriptionTop += char;
    pos++;
}

if (string_width(descriptionTop) >= MENU_MAP_W - 50)
    descriptionBottom = string_copy(description, pos, (string_length(description) - pos + 1));



draw_text_colour(MENU_MAP_D_X1 + 8, MENU_MAP_D_Y1 + 4, descriptionTop, c_white, c_white, c_white, c_white, 1);
draw_text_colour(MENU_MAP_D_X1 + 8, MENU_MAP_D_Y1 + 16, descriptionBottom, c_white, c_white, c_white, c_white, 1);


