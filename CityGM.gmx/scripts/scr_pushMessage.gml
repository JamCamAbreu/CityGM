// argument0 == the id of the messageQueue instance
// argument1 == the string
// argument2 == the color
// argument3 == the life in seconds


// since the messageSequence object updates itself, we merely need to just 'push' the 
// message to it, since incrementing the last message will force a push. 
var num = argument0.lastMessage;

argument0.messageStrings[num] = argument1;
argument0.messageColors[num] = argument2;
argument0.messageLife[num] = argument3;

// finally, increment
argument0.lastMessage = argument0.lastMessage + 1;


