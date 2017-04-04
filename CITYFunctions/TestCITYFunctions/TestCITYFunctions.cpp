// TestCITYFunctions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" // do I really need this...microsoft? Thanks.
#include <iostream>
#include <stdlib.h>
#include "../CITYFunctions/CITYFunctions.h"



int main() {
  std::cout << "[PROGRAM_DEBUG BEGIN]" << std::endl;
  initDLL();

  std::cout << std::endl;


  initMap();

  seedMap(TT_TREE, 9);
  //_printMapTypes();

  growSeeds(TT_TREE, 20);
  //_printMapTypes();

  seedMap(TT_WATER, 5);
  //_printMapTypes();

  growSeeds(TT_WATER, 8);
  //_printMapTypes();

  /*
  //_testString();

  //addBuilding(BT_FIRE, 4, 10);
  //addBuilding(BT_WATERTOWER, 2, 8);
  addBuilding(BT_AIRPORT, 0, 0);
  //addBuilding(BT_ARCADE, 1, 1);
  //_testPrintBuildingList();
  //_printMapTypes();

  //removeBuilding(22, 22);

  _testPrintBuildingList();
  std::cout << std::endl;
  _printMapTypes();

  _testString();

  */
  _printMapTypes();

  mapEnd();
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "[PROGRAM_DEBUG END]" << std::endl;
    return 0;
}

