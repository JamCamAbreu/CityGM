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

  addBuilding(BT_COAL, 10, 8);
  addBuilding(BT_SCHOOL, 50, 40);
  addBuilding(BT_AIRPORT, 0, 10);

  setAllTileDataValue(TDT_LANDVALUE, 50);
  addWaterTileValue(TDT_LANDVALUE, 8, 1);


  // test zones:

  std::cout << std::endl;
  std::cout << "[R ZONE TEST]" << std::endl;
  _testPrintZoneString(Z_RES);
  std::cout << "[C ZONE TEST]" << std::endl;
  _testPrintZoneString(Z_COM);
  std::cout << "[I ZONE TEST]" << std::endl;
  _testPrintZoneString(Z_IND);
  std::cout << std::endl << "[END ZONE TEST]" << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  


  int ranX;
  int ranY;
  int zoneType;
  for (int p = 0; p < 12; p++) {

    ranX = getRandomRange(5, (MAP_DIMENSION - 5));
    ranY = getRandomRange(5, (MAP_DIMENSION - 5));
    zoneType = getRandomRange(Z_RES, Z_IND);

    std::cout << "Adding zone type: " << zoneType << std::endl;


    addZone(ranX, ranY, zoneType);
  }


  std::cout << std::endl;
  std::cout << std::endl;
  char* someString = tileTypeToString();
  int loc;
  for (int c = 0; c < MAP_DIMENSION; c++) {
    for (int r = 0; r < MAP_DIMENSION; r++) {
      loc = (r*MAP_DIMENSION) + (c);
      std::cout << someString[loc];
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  std::cout << std::endl;


  std::cout << std::endl;
  std::cout << "[R ZONE TEST]" << std::endl;
  _testPrintZoneString(Z_RES);
  std::cout << "[C ZONE TEST]" << std::endl;
  _testPrintZoneString(Z_COM);
  std::cout << "[I ZONE TEST]" << std::endl;
  _testPrintZoneString(Z_IND);
  std::cout << std::endl << "[END ZONE TEST]" << std::endl;
  std::cout << std::endl;

  // end test zones ---


  mapEnd();
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "[PROGRAM_DEBUG END]" << std::endl;
    return 0;
}

