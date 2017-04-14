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
  TT_WATER,

  // extra tree and water types:
  TT_TREE2,
  TT_TREE3,
  TT_TREE4,
  TT_WATER2,
  TT_WATER3,
  TT_WATER4
}tileTypes;

enum {
  BT_TREE = 0,
  BT_ROAD,
  BT_PLINE,
  BT_RZONE, // 3
  BT_CZONE,
  BT_IZONE,
  BT_POLICE , // 6
  BT_FIRE, 
  BT_SCHOOL,
  BT_HOSPITAL, // 9
  BT_COAL,
  BT_NUCLEAR, 
  BT_WATERTOWER, // 12
  BT_ARCADE,
  BT_AIRPORT
}buildingTypes;

enum {
  BP_TREE = 20, 
  BP_ROAD = 50,
  BP_PLINE = 50, 
  BP_RZONE = 250,
  BP_CZONE = 350,
  BP_IZONE = 300,
  BP_POLICE = 500,
  BP_FIRE = 500,
  BP_SCHOOL = 1000,
  BP_HOSPITAL = 2000,
  BP_COAL = 1500,
  BP_NUCLEAR = 5000,
  BP_WATERTOWER = 800,
  BP_ARCADE = 700,
  BP_AIRPORT = 7000
}BuildingPrices;


enum {
  Z_RES = 0,
  Z_COM,
  Z_IND
  // Z_FAR farms maybe?
}zoneTypes;

enum {
  MD_NORMAL = 0, // default
  MD_SELECT,
  MD_PLACE,
  MD_MENU        // add other modes too, like dataGen mode etc...
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

enum {
  CT_RURAL = 0, // 0 to 49 
  CT_DWELLING = 50, // 50 to 99
  CT_HAMLET = 100, // 100 to 299 
  CT_TOWN = 300, // 300 to 999
  CT_LARGETOWN = 1000, // 1000 to 9999
  CT_CITY = 10000, // 10000 to 24999
  CT_LARGECITY = 25000, // 25000 to 99999
  CT_METROPOLIS = 100000, // 100000 to 299999
  CT_MEGALOPOLIS = 300000 // 300000 and above

}cityType;



// STRUCT DEFINITIONS ----------------------

typedef struct gameData {
  int year;
  int month; // M_JAN, etc..
  int season; // S_FALL, etc..
  int gameSpeed; // SP_NORMAL, etc..

  int mode; // M_NORMAL, etc...

  int money;

  int population;
  int cityType;
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







// GAME DATA functions:
void _setCityType(int type);
int _checkNewCityType();

void _setDataCircle(int xOrigin, int yOrigin, int radius, int dataType, int amount);












// TILE FUNCTIONS --------------------------

std::string _tileTypeToString();

void _setTileType(int xCoord, int yCoord, int type);


void _setTileCircle(int xOrigin, int yOrigin, int radius, int tileType);

















// BUILDING FUNCTIONS ----------------------
int _getBuildingDimension(int type);

void _setBuildingTiles(building* buildingID, int x, int y, int dimension);

building* _newBuilding(int type, int x, int y);

int _checkPlacement(int type, int x, int y);

int _getBuildingVectorSize();

std::string _buildingInfoToString();

int _checkMoney(int amount);












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
GMEXPORT double getPopulation();
GMEXPORT double getCityType();

GMEXPORT double incrementGameMonth();
GMEXPORT double setGameMode(double mode);
GMEXPORT double setGameSpeed(double speed);
GMEXPORT double getGameMoney();
GMEXPORT double checkCanSpend(double cost);
GMEXPORT double deductFunds(double cost);
GMEXPORT double setPopulation(double pop);



GMEXPORT double seedMap(double type, double seedAmount);
GMEXPORT double growSeeds(double type, double amount);

GMEXPORT double setTileType(double xCoord, double yCoord, double type);

GMEXPORT char* tileTypeToString();

GMEXPORT double addBuilding(double type, double x, double y);
GMEXPORT double removeBuilding(double xOrigin, double yOrigin);
GMEXPORT double getBuildingVectorSize();
GMEXPORT double getBuildingPrice(double buildingType);

GMEXPORT char* buildingsToString();

GMEXPORT double getRandomRange(double min, double max);

// TESTING/DEBUGGING FUNCTIONS-----------------------------
GMEXPORT void _printMapTypes();
GMEXPORT void _testStringOutput();


GMEXPORT void _testPrintBuildingList();
GMEXPORT void _testString();
GMEXPORT void _testGameData(int months);

#endif

