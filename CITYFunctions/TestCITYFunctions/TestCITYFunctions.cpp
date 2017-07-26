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
std::cout << std::endl;
std::cout << std::endl;


/*
for (int d = 0; d < 1; d++) {

  setPopulation(1);

  // Add random R zones:
  int ranX;
  int ranY;
  for (int j = 0; j < 5; j++) {

    ranX = getRandomRange(5, MAP_DIMENSION - 5);
    ranY = getRandomRange(5, MAP_DIMENSION - 5);

    addBuilding(BT_RZONE, ranX, ranY);
  }




  std::cout << "Population before = " << getPopulation();
  std::cout << "\t";

  growZone(Z_RES);
  growZone(Z_RES);
  growZone(Z_RES);

  updatePopulationZones();
  std::cout << "Population after = " << getPopulation();
  std::cout << std::endl;

  cleanUpAllZones();
}

*/





// TEST growth algorithm:
std::cout << "Testing zone Growth:" << std::endl;
std::cout << std::endl;
int randLevel;
int randLV;
int popGrowth;
for (int i = 0; i < 80; i++) {

  randLevel = (i / 5);
  randLV = ((i % 10) * 10);

  popGrowth = (int)_testZoneGrowthAlgorithm(randLevel, randLV);

  std::cout << "lvl=" << randLevel;
  std::cout << ", LandValue=" << randLV << ", \t Growth = ";
  std::cout << popGrowth << std::endl;
  if (i % 10 == 9)
    std::cout << std::endl;
}



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

