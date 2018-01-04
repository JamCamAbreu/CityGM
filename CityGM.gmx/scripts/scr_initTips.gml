// argument0 = id holding the tips stack data structure

// NOTE: These are the tips at the BEGINNING OF THE GAME,
// If I want to add more tips, I just need to do a ds_list_add to the 
// tips data structure any time in the main object. I could do this 
// for instance after unlocking a new feature. 


// controls
ds_list_add(argument0.tips, "Tip: Press 'q' to close any menu");
ds_list_add(argument0.tips, "Tip: Press 'c' to toggle drawing menus");
ds_list_add(argument0.tips, "Tip: Press 'i' to inspect any building");
ds_list_add(argument0.tips, "Tip: Press 'm' to toggle the minimap");
ds_list_add(argument0.tips, "Tip: Press 'f' to enter the menu");
ds_list_add(argument0.tips, "Tip: Press 'x' to destroy a building");

// tile data
ds_list_add(argument0.tips, "Tip: Residents like living by water...");
ds_list_add(argument0.tips, "Tip: Residents like trees...");
ds_list_add(argument0.tips, "Tip: Citizens do not like living by smogg.");


// Zones
ds_list_add(argument0.tips, "Tip: Create residential zones for residents to move in!");
ds_list_add(argument0.tips, "Tip: Commercial Zones give residents places to build jobs.");
ds_list_add(argument0.tips, "Tip: Businesses need goods for their shops, from industrial zones!");


// financial
ds_list_add(argument0.tips, "Tip: Every year you can modify city taxes in December!");



