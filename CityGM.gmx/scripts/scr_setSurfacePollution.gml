// argument0 = string info of tiles from DLL
// argument1 = string size of argument0
// argument2 = id of object that holds the surface id



// init surface (clear):
var mapDimension = MINIMAP_PIXEL*MAP_DIMENSION;
if (!surface_exists(argument0.surfacePollutionMap)) {
    argument0.surfacePollutionMap = surface_create(mapDimension, mapDimension);
    surface_set_target(argument0.surfacePollutionMap);
    draw_clear_alpha(c_black, 1);
    surface_reset_target();
}

// draw on surface:
if (surface_exists(argument0.surfacePollutionMap)) {



    // surface set up:
    surface_set_target(argument0.surfacePollutionMap);
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
                val = real(valString);
                
                // debug
                //if (c == 12 && r == 12)
                    //show_message("test");
                //if (val != 0)
                    //show_message("i = " + string(i) + ", val = " + string(val));
        
                // position to draw:
                xCoord = mapX1 + ((c)*MINIMAP_PIXEL);
                yCoord = mapY1 + ((r)*MINIMAP_PIXEL);
                
                if (val <= 5)
                    color = c_gray;
                else
                    color = make_colour_hsv(90, 255, 255); // green
                    
                if (val > 30)
                    color = make_colour_hsv(45, 170, 240); // yellow
                if (val > 50)
                    color = make_colour_hsv(0, 255, 225); // red
                if (val > 80)
                    color = c_white;
                
                draw_rectangle_colour(xCoord, yCoord, xCoord + MINIMAP_PIXEL, yCoord + MINIMAP_PIXEL, color, color, color, color, false);
            } // end if
        } // inner for
    } // outer for
    
    surface_reset_target();
} // end if surface exists

