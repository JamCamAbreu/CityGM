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

  //seedMap(TT_WATER, 3);
  //growSeeds(TT_WATER, 5);

  //seedMap(TT_TREE, 4);
  //growSeeds(TT_TREE, 3);






  // test width of screen
  for (int i = 0; i < MAP_DIMENSION; i++) {
    if (i < 10)
      std::cout << i << " ";
    else
      std::cout << i;
  }



  // RUN TEST HERE:
  std::cout << std::endl;

  addBuilding(BT_HOSPITAL, 30, 30);

  addBuilding(BT_RZONE, 10, 10);
  addBuilding(BT_CZONE, 13, 10);
  addBuilding(BT_IZONE, 16, 10);
  addBuilding(BT_NUCLEAR, 19, 10);
  sendElectricity();


  /*
  std::cout << "Building info for 30, 30: " << std::endl;
  std::cout << "\t" << getBuildingInfo(BDT_TYPE, 30, 30) << std::endl;
  std::cout << "\t" << getBuildingInfo(BDT_SIZE, 30, 30) << std::endl;
  std::cout << "\t" << getBuildingInfo(BDT_CURPOWER, 30, 30) << std::endl;
  std::cout << "\t" << getBuildingInfo(BDT_REQPOWER, 30, 30) << std::endl;
  std::cout << "\t" << getBuildingInfo(BDT_POLLUTION, 30, 30) << std::endl;
  std::cout << "\t" << getBuildingInfo(BDT_LANDVALUEBOOST, 30, 30) << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "Building info for 40, 40: " << std::endl;
  std::cout << "\t" << getBuildingInfo(BDT_TYPE, 40, 40) << std::endl;
  std::cout << "\t" << getBuildingInfo(BDT_SIZE, 40, 40) << std::endl;
  std::cout << "\t" << getBuildingInfo(BDT_CURPOWER, 40, 40) << std::endl;
  std::cout << "\t" << getBuildingInfo(BDT_REQPOWER, 40, 40) << std::endl;
  std::cout << "\t" << getBuildingInfo(BDT_POLLUTION, 40, 40) << std::endl;
  std::cout << "\t" << getBuildingInfo(BDT_LANDVALUEBOOST, 40, 40) << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  */

  _printMapTypes();

  std::cout << std::endl;
  std::cout << "Funds: " << getGameMoney() << std::endl;

  for (int i = 0; i < 7; i++) {
    std::cout << "[Zones Growth: " << i << "]" << std::endl;
    growZone(Z_RES);
    growZone(Z_COM);
    growZone(Z_IND);
    _testCollectRevenue();
  }

  std::cout << "Funds: " << getGameMoney() << std::endl;

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

