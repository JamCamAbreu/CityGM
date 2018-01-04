// argument0 == id of the messageQueue object

var PAD = view_wview/10;
var xPAD = 16;
var PAD2 = PAD + 8;
var xPAD2 = xPAD + 8;
var PAD3 = PAD2 + 8;
var xPAD3 = xPAD2 + 8;
var MID = view_xview + view_wview/2;

// Black Border
draw_roundrect_colour_ext(
    view_xview + xPAD, 
    view_yview + PAD, 
    view_xview + view_wview - xPAD, 
    view_yview + view_hview - PAD, 
    45, 45, c_black, c_black, false
);
    

// Inner Window
draw_roundrect_colour_ext(
    view_xview + xPAD2, 
    view_yview + PAD2, 
    view_xview + view_wview - xPAD2, 
    view_yview + view_hview - PAD2, 
    45, 45, c_dkgray, c_dkgray, false
);
    

// Menu Title
var title = "Notifications";
draw_set_font(ft_title);
var stringSize = string_width(title);

// black backround:
draw_text_colour(
    MID - stringSize/2 - 1, // centered
    view_yview + PAD3 - 1, 
    title, c_black, c_black, c_black, c_black, 1
);

// colored:
draw_text_colour(
    MID - stringSize/2, // centered
    view_yview + PAD3, 
    title, c_yellow, c_yellow, c_yellow, c_yellow, 1
);



// inner box
var boxX1 = view_xview + xPAD3;
var boxY1 = view_yview + PAD3 + 24;
var boxX2 = view_xview + view_wview - xPAD3;
var boxY2 = view_yview + view_hview - PAD3;
var PAD4 = 8;
var boxHeight = boxY2 - boxY1 - PAD4*2;
draw_roundrect_colour_ext(
    boxX1, boxY1, boxX2, boxY2, 
    16, 16, c_gray, c_gray, false);

// messages
draw_set_font(ft_normal);
var yJump = boxHeight/10;
var yStart = boxY1 + PAD4;
var xStart = boxX1 + PAD4;

var lastMessage = argument0.lastMessage;
var amount = 10;
if (lastMessage < 10)
    amount = lastMessage;
    



// There ARE messages to display
if (amount > 0) {
    var current = lastMessage - 1;
    var curString;
    var curColor;
    var line;
    while (current > (lastMessage - 1 - amount)) {
        curString = argument0.messageStrings[current];
        
        var stringChars = string_length(curString);
        // IF STRING IS TOO LARGE TO DISPLAY
        if (stringChars > MAX_CHARS_MESSAGE_SCREEN) {
            var start = MAX_CHARS_MESSAGE_SCREEN;
            var num = stringChars - MAX_CHARS_MESSAGE_SCREEN + 1;
            curString = string_delete(curString, start, num);
            curString += "...";

        }
        
        curColor = argument0.messageColors[current];
        line = (lastMessage - 1 - current);
        draw_text_colour(
            xStart, yStart + yJump*line, 
            string(current) + ". " + curString, 
            curColor, curColor, curColor, curColor, 1
        );
        current--;
    }
}
// There are NO messages yet!
else {
    var curColor = c_yellow;
    var line = 1;
    var curString = "There are no messages to display!";
    draw_text_colour(
        xStart, yStart*line, curString, 
        curColor, curColor, curColor, curColor, 1
    );
}
                                        

