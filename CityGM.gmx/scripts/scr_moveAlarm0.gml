if (keyboard_check(vk_left)) || (keyboard_check(ord('A'))) {
    x -= TILE_SIZE;
}
if (keyboard_check(vk_up)) || (keyboard_check(ord('W'))) {
    y -= TILE_SIZE;
}
if (keyboard_check(vk_right)) || (keyboard_check(ord('D'))) {
    x += TILE_SIZE;
}
if (keyboard_check(vk_down)) || (keyboard_check(ord('S'))) {
    y += TILE_SIZE;
}

// go to alarm 1
alarm[1] = CAMERA_ALARM_FAST;
