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

  _printMapTypes();


  _testPrintTileData(1);

  addDataCircle(10, 10, 4, 1, 3);
  addDataCircle(30, 35, 9, 1, 9);
  addDataCircle(17, 10, 6, 1, 4);


  _testPrintTileData(1);

  mapEnd();
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "[PROGRAM_DEBUG END]" << std::endl;
    return 0;
}

