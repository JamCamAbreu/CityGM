// argument0 = string info of tiles from DLL
// argument1 = string size of argument0
// argument2 = id of object that holds the surface id



// init surface (clear):
var mapDimension = MINIMAP_PIXEL*MAP_DIMENSION;
if (!surface_exists(argument0.surfaceSpecialMap)) {
    argument0.surfaceSpecialMap = surface_create(mapDimension, mapDimension);
    surface_set_target(argument0.surfaceSpecialMap);
    draw_clear_alpha(c_black, 1);
    surface_reset_target();
}

// draw on surface:
if (surface_exists(argument0.surfaceSpecialMap)) {



    // surface set up:
    surface_set_target(argument0.surfaceSpecialMap);
    draw_clear_alpha(c_white, 1);
    
    // drawing algorithm:
    
    var pollutionString = DLL_tileDataToString(TDT_POLLUTION);
    
    var mapX1 = 0;
    var mapY1 = 0;
    
    var valString;
    var val;
    var stringPos = 1;
    
    var color;

    
    var xCoord;
    var yCoord; 
    
    for (r = 0; r < MAP_DIMENSION; r++) {
        for (c = 0; c < MAP_DIMENSION; c++) {    
        
            // find value (parse from string):
            valString = ""; // reset
            if (stringPos <= string_length(pollutionString)) {
                while (string_char_at(pollutionString, stringPos) != ',') {
                    valString += string_char_at(pollutionString, stringPos);
                    
                    // debug:
                    //if (string_length(valString) > 1)
                        //show_message(valString);
                        
                    stringPos++;
                }
                stringPos++;
                
                if (valString != 'W') {
                    val = real(valString); // convert to real number
                 
                    // INVERT val:
                    val = (100 - val);
                    // set color according to data:
                    if (val > 80)
                        color = make_colour_hsv(75, 200, 255); // green
                    else if (val > 70)
                        color = make_colour_hsv(60, 190, 255); // green
                    else if (val > 60)
                        color = make_colour_hsv(46, 180, 255); // green
                    else if (val > 50)
                        color = make_colour_hsv(38, 170, 240); // yellow
                    else if (val > 40)
                        color = make_colour_hsv(24, 140, 240); // yellow
                    else if (val > 30)
                        color = make_colour_hsv(16, 255, 225); // orange
                    else if (val <= 30)
                        color = c_white; // red
                }
                // Water tile:
                else 
                    color = c_blue;
        
                // position to draw:
                xCoord = mapX1 + ((c)*MINIMAP_PIXEL);
                yCoord = mapY1 + ((r)*MINIMAP_PIXEL);
                

                
                draw_rectangle_colour(xCoord, yCoord, xCoord + MINIMAP_PIXEL, yCoord + MINIMAP_PIXEL, color, color, color, color, false);
            } // end if
        } // inner for
    } // outer for
    
    surface_reset_target();
} // end if surface exists

