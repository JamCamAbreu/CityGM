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
#include <string> // used to convert tiles to strings for GM
#include <vector> // used for building struct

// ENUMS---------------------------------------------------

enum {
  TT_GRASS = 0, // default
  TT_TREE,
  TT_BUILDING, 
  TT_WATER
}tileType;


enum {
  BT_POLICE = 0,
  BT_FIRE, 
  BT_SCHOOL,
  BT_HOSPITAL,
  BT_NUCLEAR, 
  BT_AIRPORT,
  BT_WATERTOWER,
  BT_ARCADE,
  BT_GYM
};


// CONSTANTS ----------------------------------------------
const int MAP_DIMENSION = 60;
const int MAX_STRING = MAP_DIMENSION * 3;

const char CHAR_GRASS = '.';
const char CHAR_TREE = 'T';
const char CHAR_BUILDING = '+';
const char CHAR_WATER = '~';
const char CHAR_ERROR = '!';

// DATA STRUCTURE DEFINITIONS------------------------------
typedef struct tile {
  int x;
  int y;
  int trueIndex;
  int tileType;
  int val;
}tile;
 
typedef struct powerLine {

};

typedef struct road {

};

typedef struct building {

  // tiles covered by this building
  std::vector<tile*> tiles;
  
  // type uses an enum:
  int type;

  // top left x and y
  int xOrigin;
  int yOrigin;

  // dimensions using tiles as unit:
  int buildingDimension;

  // other attributes:
  bool isPowered;
  int pollution;

  // connected power lines or roads
  std::vector<powerLine*> adjacentPowerLines;
  std::vector<road*> adjacentRoads;
};


// FUNCTION PROTOTYPES ------------------------------------

// INTERNAL FUNCTIONS -------------------------------------
tile* map(int x, int y); // to access map (2d array of tile pointers)
void _randomize();
int _getIntRange(int min, int max);
void _growSeeds(int type);
void _grow(int type, int r, int c);
void _fillSeedHoles(int type);

std::string _tileTypeToString();

int _getBuildingDimension(int type);
void _setBuildingTiles(building* buildingID, int x, int y, int dimension);
building* _newBuilding(int type, int x, int y);

void _removeBuilding(building* buildingPtr);

// INTERFACE ----------------------------------------------
GMEXPORT double initDLL();

GMEXPORT double initMap();

GMEXPORT double seedMap(double type, double seedAmount);
GMEXPORT double growSeeds(double type, double amount);


GMEXPORT double getTileVal(double xCoord, double yCoord);

GMEXPORT double setTileVal(double xCoord, double yCoord, double value);
GMEXPORT double setTileType(double xCoord, double yCoord, double type);

GMEXPORT char* tileTypeToString();

GMEXPORT double addBuilding(double type, double x, double y);
GMEXPORT double removeBuilding(double xOrigin, double yOrigin);

// TESTING/DEBUGGING FUNCTIONS-----------------------------
GMEXPORT void _printMapTypes();

GMEXPORT void _testPrintBuildingList();

#endif
