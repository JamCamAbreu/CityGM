// TestCITYFunctions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" // do I really need this...microsoft? Thanks.
#include <iostream>
#include <stdlib.h>

#include "../CITYFunctions/CITYFunctions.h"


int getInt() {

  std::cout << "Please choose an integer: ";
  int number;
  std::cin >> number;

  return number;
}

void testGetSetFunctions() {

  // TEST my get and set functions:
  int userX;
  int userY;
  int userVal;

  do {
    std::cout << "Enter x: ";
    std::cin >> userX;

    std::cout << "Enter y: ";
    std::cin >> userY;

    std::cout << "Enter value to be stored at " << userX << ", " << userY << ": ";
    std::cin >> userVal;

    setTileVal(userX, userY, userVal);

    std::cout << "Testing, Value at " << userX << ", " << userY << " = " << getTileVal(userX, userY) << std::endl;
  } while (userVal != -1);
}


// WHOOO build success!

int main() {
  std::cout << "[PROGRAM_DEBUG BEGIN]" << std::endl;
  initDLL();

  std::cout << std::endl;


  initMap();

  seedMap(TT_TREE, 5);
  _printMapTypes();

  growSeeds(TT_TREE, 7);
  _printMapTypes();

  seedMap(TT_WATER, 5);
  _printMapTypes();

  growSeeds(TT_WATER, 8);
  _printMapTypes();



  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  addBuilding(BT_FIRE, 4, 10);
  addBuilding(BT_WATERTOWER, 2, 8);
  addBuilding(BT_AIRPORT, 20, 20);
  addBuilding(BT_ARCADE, 1, 1);
  _testPrintBuildingList();
  _printMapTypes();

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "REMOVING building at 22, 22..." << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  removeBuilding(22, 22);

  _testPrintBuildingList();
  std::cout << std::endl;

  std::cout << std::endl;
  _printMapTypes();

  std::cout << std::endl;
  std::cout << "[PROGRAM_DEBUG END]" << std::endl;
    return 0;
}

