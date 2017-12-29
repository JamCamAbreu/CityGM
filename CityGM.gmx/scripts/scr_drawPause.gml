// argument0 = id of object calling instance
// argument1 = drawPause?

if (argument1) {
    var pauseString = "Game Paused";
    var color = c_white;
    if (argument0.gameSeason == S_WINTER)
        color = c_black;
    
    draw_text_colour(view_xview + view_wview/2 - (string_width(pauseString)/2), view_yview + view_hview/2, pauseString, color, color, color, color, 1);
}
