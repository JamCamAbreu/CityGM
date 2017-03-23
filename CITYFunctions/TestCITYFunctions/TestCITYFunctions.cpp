// TestCITYFunctions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" // do I really need this...microsoft? Thanks.
#include <iostream>
#include <stdlib.h>

#include "CITYFunctions.h"


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

  std::cout << std::endl;


  initMap();

  seedMap(TT_TREE, 5);
  growSeeds(TT_TREE, 10);
  _printMapTypes();

  seedMap(TT_WATER, 2);
  growSeeds(TT_WATER, 15);
  _printMapTypes();


  std::cout << "[PROGRAM_DEBUG END]" << std::endl;
    return 0;
}

