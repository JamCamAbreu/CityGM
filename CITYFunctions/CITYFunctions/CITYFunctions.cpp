// CITYFunctions.cpp : Defines the exported functions for the DLL application.
#pragma once
#include "CITYFunctions.h"

// (for DEBUGGING):
#include <iostream>

// GLOBAL VARIABLES AND POINTERS (because GM doesn't allow direct access)----
// main map 2d array of pointers pointer

tile newMap[MAP_DIMENSION][MAP_DIMENSION];
tile* mapStartAddress = &newMap[0][0];


// INTERNAL FUNCTIONS ---------------------------------------------
tile* map(int x, int y) {

  tile* iter = mapStartAddress;
  iter += (y*MAP_DIMENSION) + (x);
  return iter;
}

int _getIntRange(int min, int max, int forRandom) {

  // use time function to get seed value for srand:
  unsigned seed;
  seed = std::time(0) + forRandom;
  srand(seed);

  // find a random number using that seed:
  int roll = (std::rand() % (max - min + 1)) + min;
  return roll;
}

void _growSeeds(int type, int forRandom) {

  tile* iter;

  int dir;
  int seed = 0;

  for (int r = 1; r < MAP_DIMENSION - 1; r++) {
    for (int c = 1; c < MAP_DIMENSION - 1; c++) {
      iter = map(r, c);
      if (iter->tileType == type) {// CHANGE BUILDING TO 'TYPE LATER' <<-----FIXME
        seed = _getIntRange(0, 2, forRandom + r);
      }
      else
        seed = 0;

      if (seed) {
        dir = _getIntRange(0, 3, c*forRandom); // don't grow each direction, only 1 direction
        //std::cout << "map(" << r << ", " << c << "), dir = " << dir << std::endl;

        // check left:
        if (dir == 0) {
          setTileType(c - 1, r, type);
        }

        // check right:
        else if (dir == 1) {
          setTileType(c + 1, r, type);
        }

        // check above:
        else if (dir == 2) {
          setTileType(c, r + 1, type);
        }

        // check below:
        else if (dir == 2) {
          setTileType(c, r - 1, type);
        }

      } // end if !seed
    } // end inner for loop
  } // end outter for loop

}


// INTERFACE (EXPORTED FUNCTIONS)----------------------------------

// sets up data structure for use. MUST BE EXECUTED FIRST!
void initMap() {

  tile* iter = map(0,0);

  int accumulator = 0;
  for (int r = 0; r < MAP_DIMENSION; r++) {
    for (int c = 0; c < MAP_DIMENSION; c++) {
      iter->x = c;
      iter->y = r;
      iter->trueIndex = accumulator;
      iter->tileType = TT_GRASS;
      iter->val = 1;

      accumulator++;
      iter++; // increments sizeof(tile)
    }
  }

}


// Returns a tile object's (value?) into game maker for access
double getTileVal(double xCoord, double yCoord) {
  // convert to int (game maker only passes and receives doubles)
  int x = (int)xCoord;
  int y = (int)yCoord;

  double val = (double)map(x,y)->val;
  return val;
}

// set tile's (value?):
double setTileVal(double xCoord, double yCoord, double value) {
  // convert to int (game maker only passes and receives doubles)
  int x = (int)xCoord;
  int y = (int)yCoord;
  int val = (int)value;

  map(x,y)->val = val;
  return 0;
}

// set tile's type (use ENUM in .h file!) 
double setTileType(double xCoord, double yCoord, double type) {
  // convert to int (game maker only passes and receives doubles)
  int x = (int)xCoord;
  int y = (int)yCoord;
  int val = (int)type;

  map(x,y)->tileType = val;
  return 0;
}


// set some initial seeds LATER UPDATE TO INCLUDE TYPE ---------------FIXME
void seedMap(int type, int seedAmount) {

  int randomX;
  int randomY;
  for (int i = 0; i < seedAmount; i++) {
    randomX = _getIntRange(0, MAP_DIMENSION, i);
    randomY = _getIntRange(0, MAP_DIMENSION, i*i);

    setTileType(randomX, randomY, type);
  }

}

void growSeeds(int type, int amount) {

  for (int i = 0; i < amount; i++) {
    _growSeeds(type, i);
  }

}


// TESTING/DEBUGGING FUNCTIONS ------------------------------------

void _printMapTypes() {

  tile* iter = map(0,0);

  std::cout << std::endl << std::endl;

  for (int r = 0; r < MAP_DIMENSION; r++) {
    for (int c = 0; c < MAP_DIMENSION; c++) {
      
      switch (iter->tileType) {

        case TT_GRASS: 
          std::cout << ".";
          break;

        case TT_TREE:
          std::cout << "T";
          break;

        case TT_BUILDING:
          std::cout << "+";
          break;

        case TT_WATER:
          std::cout << "~";
          break;

        default:
          std::cout << "!";
      } // end switch

      iter++; // next element
    } // end inner for-loop

    std::cout << std::endl;

  } // end outer for-loop
  std::cout << std::endl << std::endl;

}
