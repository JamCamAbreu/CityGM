// argument0 = drawPause?

if (argument0) {
    var pauseString = "Game Paused";
    draw_text_colour(view_xview + view_wview/2 - (string_width(pauseString)/2), view_yview + view_hview/2, pauseString, c_white, c_white, c_white, c_white, 1);
}
