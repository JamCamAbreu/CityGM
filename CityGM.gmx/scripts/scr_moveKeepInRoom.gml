// TODO: fix boarder restrictions by passing in the size of the object currently
// being placed. 

if (x < TILE_SIZE*1)
    x = TILE_SIZE*1;
if (x > (room_width - TILE_SIZE*1))
    x = room_width - TILE_SIZE*1;
if (y < TILE_SIZE*1)
    y = TILE_SIZE*1;
if (y > room_height - TILE_SIZE*1)
    y = room_height - TILE_SIZE*1;
