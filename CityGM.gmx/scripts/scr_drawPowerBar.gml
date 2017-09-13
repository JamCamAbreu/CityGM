
// Ratio of power used to power available:
var ratio = DLL_getPowerUsageRatio();

if (ratio < 0)
    ratio = 0;

if (ratio > 0) {
    
    // Something is really screwed about about subtracting x2 from x1, so I have to do this:
    var x1 = POWER_BAR_X1;
    var x2 = POWER_BAR_X2;
    var width = x2 - x1;
    if (width < 0)
        width = 0;
    
    var powerBarWidth = width*(1 - ratio);
    if (powerBarWidth < 0)
        powerBarWidth = 0;
    
    
    //TODO
    // Choose the color based on the ratio (red is bad, yellow okay, green good
    var powerColor;
    if (ratio > 0.8)
        powerColor = c_red;
    else if (ratio > 0.6)
        powerColor = c_yellow;
    else
         powerColor = c_green;
    
    
    // draw the power icon:
    var scale = 0.6;
    draw_sprite_ext(spr_needPower, 0, 
                    x1 - BAR_UNIT*1.5, 
                    POWER_BAR_Y1 - ((sprite_get_height(spr_needPower)*scale)/2), 
                    scale, scale, 1, c_white, 1);
    
    // draw the power here:
    draw_rectangle_colour(x1, POWER_BAR_Y1, x1 + powerBarWidth, POWER_BAR_Y2, powerColor, powerColor, powerColor, powerColor, false);
    
    
    // black dots over the bar:
    var dotsAmount = 30;
    var xPos;
    var dotSize = width/(dotsAmount + 1);
    for (j = 1; j < dotsAmount; j += 2) {
        xPos = POWER_BAR_X1 + j*dotSize;
        draw_rectangle(xPos, POWER_BAR_Y1, xPos + dotSize/3, POWER_BAR_Y2, false);
    }
    
}
