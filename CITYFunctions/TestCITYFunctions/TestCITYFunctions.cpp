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

  // test width of screen
  for (int i = 0; i < MAP_DIMENSION; i++) {
    if (i < 10)
      std::cout << i << " ";
    else
      std::cout << i;
  }


  //seedMap(TT_WATER, 3);
  //growSeeds(TT_WATER, 5);

  //seedMap(TT_TREE, 4);
  //growSeeds(TT_TREE, 3);


  //addBuilding(BT_COAL, 10, 8);
  //addBuilding(BT_SCHOOL, 50, 40);
  //addBuilding(BT_AIRPORT, 0, 10);

  addBuilding(BT_POLICE, 27, 27);
  addBuilding(BT_POLICE, 27, 30);
  addBuilding(BT_POLICE, 27, 33);
  addBuilding(BT_POLICE, 30, 27);
  addBuilding(BT_POLICE, 30, 30);
  addBuilding(BT_POLICE, 30, 33);
  addBuilding(BT_POLICE, 33, 27);
  addBuilding(BT_POLICE, 33, 30);
  addBuilding(BT_POLICE, 33, 33);

  _printMapTypes();
  std::cout << std::endl;
  std::cout << std::endl;

  _testBuildingNeighbors();
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "DELETING MIDDLE BUILDING NOW" << std::endl;

  removeBuilding(30, 30);
  _printMapTypes();
  std::cout << std::endl;
  std::cout << std::endl;
  _testBuildingNeighbors();


  //setAllTileDataValue(TDT_LANDVALUE, 50);
  //addWaterTileValue(TDT_LANDVALUE, 8, 1);
















  mapEnd();


  // stop clock (DEBUG)
  double time2 = getClock();

  double totalTime = getTime(time1, time2);
  std::cout << "\nTotal time execution in seconds: " << totalTime << std::endl;

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "[PROGRAM_DEBUG END]" << std::endl;
    return 0;
}

