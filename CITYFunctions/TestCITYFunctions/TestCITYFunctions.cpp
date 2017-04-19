// TestCITYFunctions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" // do I really need this...microsoft? Thanks.
#include <iostream>
#include <stdlib.h>
#include "../CITYFunctions/CITYFunctions.h"



int main() {
  std::cout << "[PROGRAM_DEBUG BEGIN]" << std::endl;
  std::cout << std::endl;

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


  seedMap(TT_WATER, 3);
  growSeeds(TT_WATER, 5);

  seedMap(TT_TREE, 4);
  growSeeds(TT_TREE, 3);

  //addBuilding(BT_POLICE, 2, 4);
  //addBuilding(BT_FIRE, 8, 4);
  addBuilding(BT_COAL, 10, 8);
  addBuilding(BT_SCHOOL, 50, 40);
  addBuilding(BT_AIRPORT, 0, 10);
  _printMapTypes();

  setAllTileDataValue(TDT_LANDVALUE, 50);
  _testPrintTileData(TDT_LANDVALUE);

  addWaterTileValue(TDT_LANDVALUE, 8, 1);
  _testPrintTileData(TDT_LANDVALUE);

  mapEnd();
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "[PROGRAM_DEBUG END]" << std::endl;
    return 0;
}

