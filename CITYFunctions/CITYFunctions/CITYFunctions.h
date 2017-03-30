#pragma once
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

// Include files ------------------------------------------
#include <string> // used to convert tiles to strings for GM
#include <stdlib.h>
#include <ctime>
#include <vector>



// CONSTANTS -------------------------------
const int MAP_DIMENSION = 60;
const int MAX_STRING = MAP_DIMENSION * 3;

const char CHAR_GRASS = '.';
const char CHAR_TREE = 'T';
const char CHAR_BUILDING = '+';
const char CHAR_WATER = '~';
const char CHAR_ERROR = '!';






// ENUMS -----------------------------------
enum {
  TT_GRASS = 0, // default
  TT_TREE,
  TT_BUILDING, 
  TT_WATER
}tileTypes;

enum {
  BT_POLICE = 0,
  BT_FIRE, 
  BT_SCHOOL,
  BT_HOSPITAL,
  BT_NUCLEAR, 
  BT_AIRPORT,
  BT_WATERTOWER,
  BT_ARCADE,
  BT_GYM,
  BT_ZRES, // zones hold special data
  BT_ZCOM,
  BT_ZIND
}buildingTypes;

enum {
  Z_RES = 0,
  Z_COM,
  Z_IND
  // Z_FAR farms maybe?
}zoneTypes;

enum {
  M_NORMAL = 0, // default
  M_SELECT,
  M_PLACE
}modeTypes;

enum {
  S_FALL = 0,
  S_WINTER,
  S_SPRING,
  S_SUMMER
}seasonTypes;

enum {
  M_JAN = 1,
  M_FEB,
  M_MAR,
  M_APR,
  M_MAY,
  M_JUN,
  M_JUL,
  M_AUG,
  M_SEP,
  M_OCT,
  M_NOV,
  M_DEC // 12
}monthTypes;

enum {
  SP_PAUSE = 0,
  SP_SLOW,
  SP_NORMAL,
  SP_FAST
}speedTypes;



// STRUCT DEFINITIONS ----------------------

typedef struct gameData {
  int year;
  int month; // M_JAN, etc..
  int season; // S_FALL, etc..
  int gameSpeed; // SP_NORMAL, etc..

  int mode; // M_NORMAL, etc...

  int money;


}gameData;


typedef struct tile {
  int x;
  int y;
  int trueIndex;
  int tileType;
}tile;

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
  //std::vector<powerLine*> adjacentPowerLines;
  //std::vector<road*> adjacentRoads;
}building;

// TODO
typedef struct zone {

  int popCur; // current people residing in
  int popCap; // capacity for people

}zone;

//typedef struct powerLine {
//};

//typedef struct road {
//};





// used to access static data struct:
tile* map(int x, int y);


// initiation -------------------
void _randomize();

void _initGameData();






// TILE FUNCTIONS --------------------------

std::string _tileTypeToString();

void _setTileType(int xCoord, int yCoord, int type);




















// BUILDING FUNCTIONS ----------------------
int _getBuildingDimension(int type);

void _setBuildingTiles(building* buildingID, int x, int y, int dimension);

building* _newBuilding(int type, int x, int y);

int _checkPlacement(int type, int x, int y);

int _getBuildingVectorSize();

std::string _buildingInfoToString();














// MAP GENERATION FUNCTIONS ----------------
void _growSeeds(int type);

void _grow(int type, int r, int c);

void _fillSeedHoles(int type);






















// UTILITY FUNCTIONS------------------------

int _getIntRange(int min, int max);

















// INTERFACE ----------------------------------------------
GMEXPORT double initDLL();
GMEXPORT double initMap();
GMEXPORT double mapEnd();

GMEXPORT double getGameYear();
GMEXPORT double getGameMonth();
GMEXPORT double getGameSeason();
GMEXPORT double getGameMode();
GMEXPORT double getGameSpeed();

GMEXPORT double incrementGameMonth();
GMEXPORT double setGameMode(double mode);
GMEXPORT double setGameSpeed(double speed);

GMEXPORT double getGameMoney();
GMEXPORT double checkCanSpend(double cost);
GMEXPORT double deductFunds(double cost);



GMEXPORT double seedMap(double type, double seedAmount);
GMEXPORT double growSeeds(double type, double amount);

GMEXPORT double setTileType(double xCoord, double yCoord, double type);

GMEXPORT char* tileTypeToString();

GMEXPORT double addBuilding(double type, double x, double y);
GMEXPORT double removeBuilding(double xOrigin, double yOrigin);
GMEXPORT double getBuildingVectorSize();

GMEXPORT char* buildingsToString();

GMEXPORT double getRandomRange(double min, double max);

// TESTING/DEBUGGING FUNCTIONS-----------------------------
GMEXPORT void _printMapTypes();
GMEXPORT void _testPrintBuildingList();
GMEXPORT void _testString();
GMEXPORT void _testGameData(int months);

#endif

