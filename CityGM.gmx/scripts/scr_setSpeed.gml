// argument0 = id holding the variables
// argument1 = speed enum

DLL_setGameSpeed(argument1);
var gameSpeed = scr_getSpeedMultiplier(argument1);

// Case Pause:
if (gameSpeed = TIME_MUL_PAUSE) {
    // first save alarm:
    argument0.timeAlarmStorage = alarm_get(0);
    
    // set alarm to zero:
    alarm_set(0, 0);
    
    // draw the pause sprite
    argument0.drawPause = true;
}

// Case Resume:
else {
    // restore alarm:
    alarm_set(0, argument0.timeAlarmStorage);
    
    // clear the pause sprite
    argument0.drawPause = false;
}

// ALL cases:
// set speed:
argument0.gameSpeedMultiplier = gameSpeed;
    
