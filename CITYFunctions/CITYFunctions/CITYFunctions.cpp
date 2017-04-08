// CITYFunctions.cpp : Defines the exported functions for the DLL application.
#pragma once
#include "CITYFunctions.h"

// (for DEBUGGING):
#include <iostream>

// GLOBAL VARIABLES AND POINTERS
gameData curGameData;
tile newMap[MAP_DIMENSION][MAP_DIMENSION];
tile* mapStartAddress = &newMap[0][0];
std::vector<building*> v_buildings; // cleaned up in mapEnd function

int mode;

tile* map(int x, int y) {

  tile* iter = mapStartAddress;
  iter += (y*MAP_DIMENSION) + (x);
  return iter;
}



//-----------------------------------------------------------------
// -----------------------INTERNAL FUNCTIONS ----------------------
//-----------------------------------------------------------------

// initiation -------------------
void _randomize() {
  unsigned seed;
  seed = std::time(0);
  srand(seed);
}

void _initGameData() {
  curGameData.year = 1990;
  curGameData.month = M_SEP;
  curGameData.season = S_FALL;
  curGameData.gameSpeed = SP_NORMAL;

  curGameData.mode = MD_NORMAL;

  curGameData.money = 8000;

  curGameData.population = 1;
  curGameData.cityType = CT_RURAL;
}








// GAME DATA functions:
void _setCityType(int type) {
  curGameData.cityType = type;
}

int _checkNewCityType() {

  int population = getPopulation();
  int curCityType = getCityType();

  switch (curCityType) {
    case CT_RURAL: {
      if (population >= (CT_DWELLING)) {
        _setCityType(CT_DWELLING);
        return 1;
      }
      break;
    }

    case CT_DWELLING: {
      if (population >= (CT_HAMLET)) {
        _setCityType(CT_HAMLET);
        return 1;
      }
      break;
    }

    case CT_HAMLET: {
      if (population >= (CT_TOWN)) {
        _setCityType(CT_TOWN);
        return 1;
      }
      break;
    }

    case CT_TOWN: {
      if (population >= (CT_LARGETOWN)) {
        _setCityType(CT_LARGETOWN);
        return 1;
      }
      break;
    }

    case CT_LARGETOWN: {
      if (population >= (CT_CITY)) {
        _setCityType(CT_CITY);
        return 1;
      }
      break;
    }

    case CT_CITY: {
      if (population >= (CT_LARGECITY)) {
        _setCityType(CT_LARGECITY);
        return 1;
      }
      break;
    }

    case CT_LARGECITY: {
      if (population >= (CT_METROPOLIS)) {
        _setCityType(CT_METROPOLIS);
        return 1;
      }
      break;
    }

    case CT_METROPOLIS: {
      if (population >= (CT_MEGALOPOLIS)) {
        _setCityType(CT_MEGALOPOLIS);
        return 1;
      }
      break;
    }

    case CT_MEGALOPOLIS: {
      // do nothing
      return 0;
      break;
    }

    default: {
      // do nothing
      return 0;
      break;
    }
  } // end switch

  // not a new type:
  return 0;
}
























// Tile Functions ---------------
void _setTileType(int xCoord, int yCoord, int type) {
    map(xCoord,yCoord)->tileType = type;
}

std::string _tileTypeToString() {
  std::string typeData;

  tile* iter = map(0, 0);
  for (int r = 0; r < MAP_DIMENSION; r++) {
    for (int c = 0; c < MAP_DIMENSION; c++) {

      switch (iter->tileType) {
        case TT_GRASS: 
          typeData += CHAR_GRASS;
          break;

        case TT_TREE:
          typeData += CHAR_TREE;
          break;

        case TT_BUILDING:
          typeData += CHAR_BUILDING;
          break;

        case TT_WATER:
          typeData += CHAR_WATER;
          break;

        default:
          typeData += CHAR_ERROR;
      } // end switch
     iter++;
    }
  }


  return typeData;
}















// Building Functions------------
int _getBuildingDimension(int type) {

  // use a switch and enum to return width:
  switch (type) {
    case BT_TREE: {
      return 1;
      break;
      }

    case BT_ROAD: {
      return 1;
      break;
      }

    case BT_PLINE: {
      return 1;
      break;
      }

    case BT_RZONE: {
      return 3;
      break;
      }

    case BT_CZONE: {
      return 3;
      break;
      }

    case BT_IZONE: {
      return 3;
      break;
      }

    case BT_POLICE: {
      return 3;
      break;
      }

    case BT_FIRE: {
      return 3;
      break;
      }

    case BT_SCHOOL: {
      return 3;
      break;
      }

    case BT_HOSPITAL: {
      return 4;
      break;
      }

    case BT_COAL: {
      return 4;
      break;
      }

    case BT_NUCLEAR: {
      return 4;
      break;
      }

    case BT_WATERTOWER: {
      return 2;
      break;
      }

    case BT_ARCADE: {
      return 2;
      break;
      }

    case BT_AIRPORT: {
      return 5;
      break;
      }

    default: {
      return -1;
      break;
    }
  } // end switch
  return -1; // <------fixme
}

void _setBuildingTiles(building* buildingID, int x, int y, int dimension) {

  // push all tiles underneath the building starting from top 
  // left corner:
  tile* containedTile;
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      containedTile = map(x + i, y + j);
      containedTile->tileType = TT_BUILDING;
      buildingID->tiles.push_back(containedTile);
    }
  }
}

building* _newBuilding(int type, int x, int y) {

  building* newBuilding = new building;

  // attribute defaults:
  newBuilding->type = type;
  newBuilding->xOrigin = x;
  newBuilding->yOrigin = y;
  newBuilding->buildingDimension = _getBuildingDimension(type);
  newBuilding->isPowered = false;
  newBuilding->pollution = 0; // write getPollution(type) function
  
  // get size in tiles:
  int dim = _getBuildingDimension(type);

  // set tiles associated with building
  _setBuildingTiles(newBuilding, x, y, dim);

  return newBuilding;
}

// checks the given x and y coord and sees is building is possible
// with the given building type
int _checkPlacement(int type, int x, int y) {

  int dimension = _getBuildingDimension(type);
  // check and see if ANY of those tiles have a building already
  tile* containedTile;
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      containedTile = map(x + i, y + j);
      if (containedTile->tileType == TT_BUILDING)
        return false;
      if (containedTile->tileType == TT_WATER)
        return false;
    } // inner for loop
  } // outer for loop

  // none were buildings:
  return true;
}

int _getBuildingVectorSize() {

  return v_buildings.size();
}

std::string _buildingInfoToString() {

  /*  EXAMPLE STRING AFTER COMPLETION:
  Psuedo:
    myBuildingString = "x,y,type;x,y,type; ... etc"

  Actual:
    myBuildingString = "3,15,2;22,9,3; ... etc"
  */

  std::string buildingInfo = "";
  std::string buffer = "";
  char dataDivider = ',';
  char elementDivider = ';';

  int size = _getBuildingVectorSize();
  std::vector<building*>::iterator iter = v_buildings.begin();
  std::string data = "";
  // iterate through each building in the list:
  for (int i = 0; i < size; i++) {
    
    // add x to string:
    data = std::to_string((*iter)->xOrigin);
    buildingInfo += data;
    buildingInfo += dataDivider;

    // add y to string:
    data = std::to_string((*iter)->yOrigin);
    buildingInfo += data;
    buildingInfo += dataDivider;

    // add type to string:
    data = std::to_string((*iter)->type);
    buildingInfo += data;
    buildingInfo += elementDivider;

    // iterate:
    if (i < size - 1)
      iter++;
  }

  return buildingInfo;
}

int _checkMoney(int amount) {

  int money = getGameMoney();

  if (amount <= money)
    return 1;
  else
    return 0;
}















// MODE functions ---------------


















// Map Generation Functions------
void _fillSeedHoles(int type) {

  tile* iter = map(0, 0);
  tile* above = map(0, 0);
  tile* below = map(0, 0);
  tile* right = map(0, 0);
  tile* left = map(0, 0);
  for (int r = 1; r < MAP_DIMENSION - 1; r++) {
    for (int c = 1; c < MAP_DIMENSION - 1; c++) {

      iter = map(c, r);

      // set above:
      if (r > 1)
        above = map(c, r - 1);
      else
        above = map(c, r);

      // set below
      if (r < MAP_DIMENSION - 1)
        below = map(c, r + 1);
      else
        below = map(c, r);

      // set left
      if (c > 1)
        left = map(c - 1, r);
      else
        left = map(c, r);

      // set right:
      if (c < MAP_DIMENSION - 1)
        right = map(c + 1, r);
      else
        right = map(c, r);


      if (
        (above->tileType == type) &&
        (below->tileType == type) &&
        (right->tileType == type) &&
        (left->tileType == type)
        ) {
        // set hole also equal:
        iter->tileType = type;
      }


    } // end inner for loop
  } // end outter for loop

}

void _grow(int type, int r, int c) {
  tile* iter = map(c, r);
  int seed = 0;
  int dir = 0;

  if (iter->tileType == type) {// CHANGE BUILDING TO 'TYPE LATER' <<-----FIXME
    seed = _getIntRange(0, 3);
  }
  else
    seed = 0;

  if (seed) {
    dir = _getIntRange(0, 3); // don't grow each direction, only 1 direction
      //std::cout << "map(" << r << ", " << c << "), dir = " << dir << std::endl;

      // check left:
      if (dir == 0) {
        if (c > 0)
          _setTileType(c - 1, r, type);
      }

      // check right:
      else if (dir == 1) {
        if (c < MAP_DIMENSION - 1)
          _setTileType(c + 1, r, type);
      }

      // check above:
      else if (dir == 2) {
        if (r < MAP_DIMENSION - 1)
          _setTileType(c, r + 1, type);
      }

      // check below:
      else if (dir == 3) {
        if (r > 0)
          _setTileType(c, r - 1, type);
      }
    } // end if !seed
}

void _growSeeds(int type) {

  int roll;
  // start by growing topleft to bottomright:
  roll = _getIntRange(0, 3);
  if (roll == 0) {
  for (int r = 1; r < MAP_DIMENSION - 1; r++) {
    for (int c = 1; c < MAP_DIMENSION - 1; c++) {
        _grow(type, c, r);
      } // end inner for loop
    } // end outter for loop
  }


    // next grow bottom right to top left:
  else if (roll == 1) {
    for (int r = MAP_DIMENSION - 1; r >= 0; r--) {
      for (int c = MAP_DIMENSION - 1; c >= 0; c--) {
        _grow(type, c, r);
      } // end inner for loop
    } // end outter for loop
  }



    // next grow bottom left to top right:
  else if (roll == 2) {
    for (int r = MAP_DIMENSION - 1; r >= 0; r--) {
      for (int c = 1; c < MAP_DIMENSION - 1; c++) {
        _grow(type, c, r);
      } // end inner for loop
    } // end outter for loop
  }



    // next grow top right to bottom left:
  else if (roll == 3) {
    for (int r = 1; r < MAP_DIMENSION - 1; r++) {
      for (int c = MAP_DIMENSION - 1; c >= 0; c--) {
        _grow(type, c, r);
      } // end inner for loop
    } // end outter for loop
  }


}






















// Utility and Other--------------
int _getIntRange(int min, int max) {

  // find a random number using that seed:
  int roll = (std::rand() % (max - min + 1)) + min;
  return roll;
}
























//-----------------------------------------------------------------
// ----------------INTERFACE (EXPORTED FUNCTIONS)------------------
//-----------------------------------------------------------------

// INITIALIZATION -----------------------
// used to initialize the DLL. RUN THIS BEFORE ANY OTHER FUNCTIONS!
double initDLL() {
  _randomize();
  return 0;
}

// sets up data structure for use.
double initMap() {

  tile* iter = map(0,0);

  int accumulator = 0;
  for (int r = 0; r < MAP_DIMENSION; r++) {
    for (int c = 0; c < MAP_DIMENSION; c++) {
      iter->x = c;
      iter->y = r;
      iter->trueIndex = accumulator;
      iter->tileType = TT_GRASS;

    accumulator++;
    iter++; // increments sizeof(tile)
    }
  }

  _initGameData();
  return 0;
}

double mapEnd() {

  // clean up all tiles in each building:
  for (int i = 0; i < v_buildings.size(); i++) {
    std::vector<building*>::iterator building = v_buildings.begin() + i;
    (*building)->tiles.clear();

    //(*adjacentPowerLines)->tiles.clear();
    //(*adjacentRoads)->tiles.clear();
  }

  // clear buildings vector:
  v_buildings.clear();

  return 0;
}














// GAME DATA FUNCTIONS ----------
double getGameYear() { return curGameData.year; }
double getGameMonth() { return curGameData.month; }
double getGameSeason() { return curGameData.season; }
double getGameMode() { return curGameData.mode; }
double getGameSpeed() { return curGameData.gameSpeed; }
double getGameMoney() { return curGameData.money; }
double getPopulation() { return curGameData.population; }
double getCityType() { return curGameData.cityType; }

// todo: add taxes in december
double incrementGameMonth() {
  // update season from Winter to Spring
  if (curGameData.month == M_FEB) {
    curGameData.season = S_SPRING;
    curGameData.month++;
  }

  // update season from Spring to Summer
  else if (curGameData.month == M_MAY) {
    curGameData.season = S_SUMMER;
    curGameData.month++;
  }

  // update season from Summer to Fall
  else if (curGameData.month == M_AUG) {
    curGameData.season = S_FALL;
    curGameData.month++;
  }

  // update season from Fall to Winter
  else if (curGameData.month == M_NOV) {
    curGameData.season = S_WINTER;
    curGameData.month++;
  }

  // update year, and rotate months:
  else if (curGameData.month >= M_DEC) {

                                            // TODO - taxes
    curGameData.year++;
    curGameData.month = M_JAN;
  }
  else 
    curGameData.month++;

  return 0;
}

double setGameMode(double mode) {
  int modeInt = (int)mode;
  curGameData.mode = modeInt;
  return 0;
}

double setGameSpeed(double speed) {
  int speedInt = (int)speed;
  curGameData.gameSpeed = speedInt;
  return 0;
}

double checkCanSpend(double cost) {
  int costInt = (int)cost;

  if (costInt >= curGameData.money)
    return 1;
  else
    return 0;
}

double deductFunds(double amount) {
  int amountInt = (int)amount;
  curGameData.money -= amountInt;
  return 0;
}

double setPopulation(double pop) {
  int population = (int)pop;
  int newCityType = 0; // false until proven true

  // update population
  curGameData.population = population;

  // sets new type, and returns 1 if new type achieved
  newCityType = _checkNewCityType();

  // returns true if REACHED a new city type level!
  // can check the NEW level with "getCityType"
  return newCityType;
}









// MAP GENERATION -----------------------
// set some initial seeds LATER UPDATE TO INCLUDE TYPE ---------------FIXME
double seedMap(double type, double seedAmount) {

  int typeInt = (int)type;
  int seedAmountInt = (int)seedAmount;

  int randomX;
  int randomY;
  for (int i = 0; i < seedAmountInt; i++) {
    randomX = _getIntRange(0, MAP_DIMENSION);
    randomY = _getIntRange(0, MAP_DIMENSION);

    setTileType(randomX, randomY, typeInt);

    // DEBUG
    //getchar();
    //_printMapTypes();
  }

  return 0;
}

double growSeeds(double type, double amount) {

  int typeInt = (int)type;
  int amountInt = (int)amount;

  for (int i = 0; i < amountInt; i++) {
    _growSeeds(typeInt);

    // DEBUG
    //getchar();
    //_printMapTypes();
  }

  // attempt to fill holes: (multiply times needed?)
  _fillSeedHoles(typeInt);

  return 0;
}








// TILE FUNCTIONS ----------------------
// set tile's type
double setTileType(double xCoord, double yCoord, double type) {
  // convert to int (game maker only passes and receives doubles)
  int x = (int)xCoord;
  int y = (int)yCoord;
  int val = (int)type;

  _setTileType(xCoord, yCoord, type);
  return 0;
}

// export MAP tile types to string for Game Maker to process quickly:
char* tileTypeToString() {

  std::string getString = _tileTypeToString();  

  char* cstr = new char[getString.length() + 1];
  std::strcpy(cstr, getString.c_str());

  return cstr;
}








// BUILDING FUNCTIONS ------------------
double addBuilding(double type, double x, double y) {

  // convert doubles to ints:
  int typeInt = (int)type;
  int xInt = (int)x;
  int yInt = (int)y;
  int price = (int)getBuildingPrice(typeInt);

  // check if position is okay to build:
  int canBuild = _checkPlacement(typeInt, xInt, yInt);

  // also check if we have enough money:
  if (canBuild)
    canBuild = _checkMoney(price);

  if (canBuild) {
    // create a new building:
    building* newBuilding = _newBuilding(typeInt, xInt, yInt);

    // add building to vector
    v_buildings.push_back(newBuilding);

    // subtract money:
    deductFunds(price);

    return 1;
  }
  else
    return 0;

  return 0;
}

double removeBuilding(double xOrigin, double yOrigin) {
  // DESCRIPTION: searches for and removes a building from the 
  // building vector, but also resets tiles underneath as appropriate
  
  int found = 0;
  int location;

  // does the tile at x, y point to a building?
  tile* deleteTile = map(xOrigin, yOrigin);
  int buildingExistsAtTile = 0;
  if (deleteTile->tileType == TT_BUILDING)
    buildingExistsAtTile = 1;

  // if so, which building?
  if (buildingExistsAtTile) {

    // loop through vector list, looking for coordinate:
    std::vector<building*>::iterator iter = v_buildings.begin();
    int vectorSize = v_buildings.size();

    // loop through each building
    for (location = 0; ((location < vectorSize) && !found); location++) {
      int numberOfTilesUnderBuilding = (*iter)->tiles.size();
      int curTile;

      // loop through each tile UNDER building:
      std::vector<tile*>::iterator tileIter = (*iter)->tiles.begin();
      for (tileIter; tileIter != (*iter)->tiles.end(); tileIter++) {
        // search each tile underneath for a match:
        if ((*tileIter)->x == xOrigin && (*tileIter)->y == yOrigin)
          found = 1;
      } // end tile iterator for loop
      

      if (!found)
        iter++;
      } // end BUILDING iterator for loop

    } // end if building even exists at given tile



  // find building if exists:
  // if found, remove building:
  if (found) {
   location--; // last iteration went 1 too far

   // update each tile underneath to having type "grass"
      // loop through each tile UNDER building:
   std::vector<building*>::iterator iter = v_buildings.begin()+location;
   std::vector<tile*>::iterator tileIter = (*iter)->tiles.begin();
   for (tileIter; tileIter != (*iter)->tiles.end(); tileIter++) {
     (*tileIter)->tileType = TT_GRASS;
   } // end tile iterator for loop

   v_buildings.erase(iter);
  }

  return 0;
}

double getBuildingVectorSize() {

  return (_getBuildingVectorSize());
}

// export building info string for Game Maker to process quickly:
char* buildingsToString() {

  std::string getString = _buildingInfoToString();

  char* cstr = new char[getString.length() + 1];
  std::strcpy(cstr, getString.c_str());

  return cstr;
}

double getBuildingPrice(double buildingType) {
  int typeInt = (int)buildingType;

  switch (typeInt) {
    case BT_TREE: {
      return BP_TREE;
      break;
      }

    case BT_ROAD: {
      return BP_ROAD;
      break;
      }

    case BT_PLINE: {
      return BP_PLINE;
      break;
      }

    case BT_RZONE: {
      return BP_RZONE;
      break;
      }

    case BT_CZONE: {
      return BP_CZONE;
      break;
      }

    case BT_IZONE: {
      return BP_IZONE;
      break;
      }

    case BT_POLICE: {
      return BP_POLICE;
      break;
      }

    case BT_FIRE: {
      return BP_FIRE;
      break;
      }

    case BT_SCHOOL: {
      return BP_SCHOOL;
      break;
      }

    case BT_HOSPITAL: {
      return BP_HOSPITAL;
      break;
      }

    case BT_COAL: {
      return BP_COAL;
      break;
      }

    case BT_NUCLEAR: {
      return BP_NUCLEAR;
      break;
      }

    case BT_WATERTOWER: {
      return BP_WATERTOWER;
      break;
      }

    case BT_ARCADE: {
      return BP_ARCADE;
      break;
      }

    case BT_AIRPORT: {
      return BP_AIRPORT;
      break;
      }

    // error
    default: {
      return -1;
      break;
    }

  }

  // error
  return -1;
}






// UTILITY FUNCTIONS -------------------
double getRandomRange(double min, double max) {
  int minInt = (int)min;
  int maxInt = (int)max;

  return _getIntRange(minInt, maxInt);
}




// TESTING/DEBUGGING FUNCTIONS ------------------------------------
void _printMapTypes() {

  tile* iter = map(0,0);

  std::cout << std::endl << std::endl;

  for (int r = 0; r < MAP_DIMENSION; r++) {
    for (int c = 0; c < MAP_DIMENSION; c++) {
      
      switch (iter->tileType) {

        case TT_GRASS: 
          std::cout << CHAR_GRASS;
          break;

        case TT_TREE:
          std::cout << CHAR_TREE;
          break;

        case TT_BUILDING:
          std::cout << CHAR_BUILDING;
          break;

        case TT_WATER:
          std::cout << CHAR_WATER;
          break;

        default:
          std::cout << CHAR_ERROR;
      } // end switch

      //std::cout << " ";

      iter++; // next element
    } // end inner for-loop

    std::cout << std::endl;

  } // end outer for-loop
  std::cout << std::endl << std::endl;

}

void _testStringOutput() {

  char* printString = tileTypeToString();

  std::cout << std::endl;
  std::cout << "Testing String:" << std::endl;
  tile* iter;
  int loc;
  for (int r = 0; r < MAP_DIMENSION; r++) {
    for (int c = 0; c < MAP_DIMENSION; c++) {
      loc = r*MAP_DIMENSION + c;
      std::cout << printString[loc];

    }
    std::cout << std::endl;
  }


}


void _testPrintBuildingList() {
  
  std::cout << std::endl;
  std::cout << "BUILDING LIST --------------------------" << std::endl;

  std::vector<building*>::iterator iter = v_buildings.begin();
  for (int i = 0; i < v_buildings.size(); i++) {
    std::cout << std::endl;
    std::cout << i << ". ";
    std::cout << "TYPE = " << (*iter)->type << ", ";
    std::cout << " at coordinates (" << (*iter)->xOrigin << ", ";
    std::cout << (*iter)->yOrigin << ")" << std::endl;

    std::cout << "\t" << "Dimensions: " << (*iter)->buildingDimension;
    std::cout << " by " << (*iter)->buildingDimension << std::endl;

    std::cout << "\t" << "Has power: ";
    if ((*iter)->isPowered == false)
      std::cout << "false" << std::endl;
    else
      std::cout << "true" << std::endl;

    std::cout << "\t" << "Total pollution: " << (*iter)->pollution;

    std::cout << std::endl;
      iter++;
  }


}


void _testString() {
  std::string testString;

  testString = _buildingInfoToString();
  std::cout << std::endl;
  std::cout << "testString = " << testString << std::endl;

}


void _testGameData(int months) {

  std::cout << std::endl;
  std::cout << "-----GAME DATA-----" << std::endl;

  for (int i = 0; i < months; i++) {

    if (curGameData.season == S_WINTER)
      std::cout << "Winter, \t";
    else if (curGameData.season == S_SPRING)
      std::cout << "Spring, \t";
    else if (curGameData.season == S_FALL)
      std::cout << "Fall,   \t";
    else 
      std::cout << "Summer, \t";

    std::cout << curGameData.month << ", \t";
    std::cout << curGameData.year;
    std::cout << std::endl;

    incrementGameMonth();
  }
  std::cout << std::endl << std::endl;
}


