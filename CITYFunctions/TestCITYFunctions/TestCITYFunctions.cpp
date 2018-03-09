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

  seedMap(TT_TREE, 6);
  growSeeds(TT_TREE, 5);


  /*
  //test width of screen
  for (int i = 0; i < MAP_DIMENSION; i++) {
    if (i < 10)
      std::cout << i << " ";
    else
      std::cout << i;
  }
  */


  _getGameDataStuff();

  // add R zone:
  addBuilding(BT_NUCLEAR, 0, 0);
  addBuilding(BT_RZONE, 4, 0);
  sendElectricity();
  _printMapTypes();

  _getGameDataStuff();

  // grow zone:
  for (int j = 0; j < 6; j++) {
    growZone(Z_RES);
    _getGameDataStuff();
  }

  growZone(Z_RES);
  _getGameDataStuff();


  growZone(Z_RES);
  _getGameDataStuff();


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

