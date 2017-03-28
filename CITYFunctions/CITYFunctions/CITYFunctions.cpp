// CITYFunctions.cpp : Defines the exported functions for the DLL application.
#pragma once
#include "CITYFunctions.h"

// (for DEBUGGING):
#include <iostream>


// GLOBAL VARIABLES AND POINTERS (because GM doesn't allow direct access)----
// main map 2d array of pointers pointer

tile newMap[MAP_DIMENSION][MAP_DIMENSION];
tile* mapStartAddress = &newMap[0][0];

std::vector<building*> v_buildings;

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
    case BT_POLICE: {
      return 2;
      break;
      }
    case BT_FIRE: {
      return 2;
      break;
      }
    case BT_SCHOOL: {
      return 3;
      break;
      }
    case BT_HOSPITAL: {
      return 3;
      break;
      }
    case BT_NUCLEAR: {
      return 3;
      break;
      }
    case BT_AIRPORT: {
      return 3;
      break;
      }
    case BT_WATERTOWER: {
      return 1;
      break;
      }
    case BT_ARCADE: {
      return 1;
      break;
      }
    case BT_GYM: {
      return 2;
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
  tile* iter = map(r, c);
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
        _setTileType(c - 1, r, type);
      }

      // check right:
      else if (dir == 1) {
        _setTileType(c + 1, r, type);
      }

      // check above:
      else if (dir == 2) {
        _setTileType(c, r + 1, type);
      }

      // check below:
      else if (dir == 2) {
        _setTileType(c, r - 1, type);
      }

    //iter++;
    } // end if !seed



}

void _growSeeds(int type) {

  int roll;


  // start by growing topleft to bottomright:
  roll = _getIntRange(0, 2);
  if (roll) {
  for (int r = 1; r < MAP_DIMENSION - 1; r++) {
    for (int c = 1; c < MAP_DIMENSION - 1; c++) {
        _grow(type, r, c);
      } // end inner for loop
    } // end outter for loop
  }


    // next grow bottom right to top left:
  roll = _getIntRange(0, 2);
  if (roll) {
    for (int r = MAP_DIMENSION - 1; r >= 0; r--) {
      for (int c = MAP_DIMENSION - 1; c >= 0; c--) {
        _grow(type, r, c);
      } // end inner for loop
    } // end outter for loop
  }



    // next grow bottom left to top right:
  roll = _getIntRange(0, 2);
  if (roll) {
    for (int r = MAP_DIMENSION - 1; r >= 0; r--) {
      for (int c = 1; c < MAP_DIMENSION - 1; c++) {
        _grow(type, r, c);
      } // end inner for loop
    } // end outter for loop
  }



    // next grow top right to bottom left:
  roll = _getIntRange(0, 2);
  if (roll) {
    for (int r = 1; r < MAP_DIMENSION - 1; r++) {
      for (int c = MAP_DIMENSION - 1; c >= 0; c--) {
        _grow(type, r, c);
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

return 0;
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
  }

  return 0;
}

double growSeeds(double type, double amount) {

  int typeInt = (int)type;
  int amountInt = (int)amount;

  for (int i = 0; i < amountInt; i++) {
    _growSeeds(typeInt);
  }

  // attempt to fill holes: (multiply times needed?)
  _fillSeedHoles(typeInt);

  return 0;
}








// TILE FUNCTIONS ----------------------
// set tile's type (use ENUM in .h file!) 
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

  std::string getString = _tileTypeToString();            // <--------START HERE! I might use an internal function to 

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

  // check if position is okay to build:
  int canBuild = _checkPlacement(typeInt, xInt, yInt);

  if (canBuild) {
    // create a new building:
    building* newBuilding = _newBuilding(typeInt, xInt, yInt);

    // add building to vector
    v_buildings.push_back(newBuilding);

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

      iter++; // next element
    } // end inner for-loop

    std::cout << std::endl;

  } // end outer for-loop
  std::cout << std::endl << std::endl;

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