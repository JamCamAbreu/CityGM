// TestCITYFunctions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" // do I really need this...microsoft? Thanks.
#include <iostream>
#include <stdlib.h>
#include "../CITYFunctions/CITYFunctions.h"



int main() {
  std::cout << "[PROGRAM_DEBUG BEGIN]" << std::endl;
  std::cout << std::endl;

  // start clock (DEBUG)
  double time1 = getClock();

  // init
  initDLL();
  initMap();

  seedMap(TT_WATER, 3);
  growSeeds(TT_WATER, 5);

  seedMap(TT_TREE, 4);
  growSeeds(TT_TREE, 3);


  /*
  //test width of screen
  for (int i = 0; i < MAP_DIMENSION; i++) {
    if (i < 10)
      std::cout << i << " ";
    else
      std::cout << i;
  }
  */

  int x;
  int y;

  // Check top left corner
  x = 0;
  y = 0;
  addBuilding(BT_ROAD, x, y);
  removeBuilding(x, y);

  // check top right corner
  x = MAP_DIMENSION - 1;
  y = 0;
  addBuilding(BT_ROAD, x, y);
  removeBuilding(x, y);

  // check bottom left corner
  x = 0;
  y = MAP_DIMENSION - 1;
  addBuilding(BT_ROAD, x, y);
  removeBuilding(x, y);

  // check bottom right corner
  x = MAP_DIMENSION - 1;
  y = MAP_DIMENSION - 1;
  addBuilding(BT_ROAD, x, y);
  removeBuilding(x, y);


  // check diagnal from 0,0 to down right
  x = 0;
  y = 0;
  int times = 8;
  for (times; times > 0; times--) {
    x++;
    y++;
    addBuilding(BT_ROAD, x, y);
    removeBuilding(x, y);
  }

  // check bigger building
  x = 4;
  y = 4;
  addBuilding(BT_NUCLEAR, x, y);
  removeBuilding(x, y);


  // check removing from tile RELATED to building but not origin
  x = 4;
  y = 4;
  addBuilding(BT_NUCLEAR, x, y);
  removeBuilding(x + 1, y + 1);



  // Draw screen:
  _printMapTypes();




  x++;





  // TEST COMPLETE:
  mapEnd();

  // stop clock (DEBUG)
  double time2 = getClock();

  double totalTime = getTime(time1, time2);
  std::cout << "\nTotal time execution in seconds: " << totalTime << std::endl;
  std::cout << std::endl;
  std::cout << "[PROGRAM_DEBUG END]" << std::endl;
    return 0;
}

