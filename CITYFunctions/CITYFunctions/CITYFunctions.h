/********************************************************************
  * Author: James Cameron Abreu
  * Date: 03/07/2017
  * Description: Contains the prototypes for all the functions related 
  *  to the CITYFunctions.dll file. Individual function descriptions 
  *  will be provided inline. 
  ********************************************************************/
#ifndef CITYFUNCTIONS_H
#define CITYFUNCTIONS_H

#define GMEXPORT extern "C" __declspec(dllexport)

/*
#ifdef GMEXPORT
#define CITYFUNCTIONS_API __declspec(dllexport)
#else
#define CITYFUNCTIONS_API __declspec(dllimport)
#endif
*/

// Include files ------------------------------------------
#include <stdlib.h>
#include <ctime>

// ENUMS---------------------------------------------------

enum {
  TT_GRASS = 0, // default
  TT_TREE,
  TT_BUILDING, 
  TT_WATER
}tileType;




// CONSTANTS ----------------------------------------------
const int MAP_DIMENSION = 30;

// DATA STRUCTURE DEFINITIONS------------------------------
typedef struct tile {
  int x;
  int y;
  int trueIndex;
  int tileType;
  int val;
}tile;
 

// FUNCTION PROTOTYPES ------------------------------------

// INTERNAL FUNCTIONS -------------------------------------
tile* map(int x, int y); // to access map (2d array of tile pointers)
int _getIntRange(int min, int max, int forRandom);
void _growSeeds(int type, int forRandom);

// INTERFACE ----------------------------------------------
GMEXPORT void initMap();

GMEXPORT void seedMap(int type, int seedAmount);
GMEXPORT void growSeeds(int type, int amount);

GMEXPORT double getTileVal(double xCoord, double yCoord);

GMEXPORT double setTileVal(double xCoord, double yCoord, double value);
GMEXPORT double setTileType(double xCoord, double yCoord, double type);

// TESTING/DEBUGGING FUNCTIONS-----------------------------
GMEXPORT void _printMapTypes();


#endif
