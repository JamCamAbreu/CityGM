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
#include <algorithm> // used for vector 'find' & 'remove' functions
#include <list>
#include <queue>

// DEBUG:
#include <iostream>



// CONSTANTS -------------------------------
const int MAP_DIMENSION = 60;
const int MAX_STRING = MAP_DIMENSION * 3;

const char CHAR_GRASS = '.';
const char CHAR_TREE = 'T';
const char CHAR_BUILDING = '+';
const char CHAR_WATER = '~';
const char CHAR_ERROR = '!';
const char CHAR_RZONE = 'r';
const char CHAR_CZONE = 'c';
const char CHAR_IZONE = 'i';

const int TILE_SECTION_DEFAULT = -1;

const int MAX_ZONE_LEVEL = 8;

const double SATISFIED_POWER = 0.6;

const int ZONE_START_REQUIRED_POWER = 3;

const int MAX_ZONE_VARIATIONS = 5;


// ENUMS -----------------------------------
enum {
  DIR_N = 0,
  DIR_E,
  DIR_S,
  DIR_W
}cardinalDirection;

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
  TT_WATER4,

  TT_ZR,
  TT_ZC,
  TT_ZI,

  TT_PLINE,
  TT_ROAD
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
  BT_AIRPORT,
  BT_POWERROAD
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
  MD_MENU,        // add other modes too, like dataGen mode etc...
  MD_TAX,
  MD_GRAPHS,
  MD_MAPS,
  MD_FILE,
  MD_NOTIFICATIONS,
  MD_MULTIPLACESTART,
  MD_MULTIPLACEEND
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

enum {
  TDT_ALL,
  TDT_POLLUTION,
  TDT_LANDVALUE,
  TDT_FIREDANGER,

  TDT_PLINETYPE,
  TDT_ROADTYPE
}tileDataType;

enum {
  TS_ERR = 0,
  TS_HOR,
  TS_VER,
  TS_ULCOR,
  TS_URCOR,
  TS_DLCOR,
  TS_DRCOR,
  TS_RT,
  TS_DT,
  TS_LT,
  TS_UT,
  TS_INT
}tileSectionType;

enum {
  BDT_TYPE = 0,
  BDT_SIZE,
  BDT_CURPOWER,
  BDT_REQPOWER,
  BDT_POLLUTION,
  BDT_LANDVALUEBOOST
}buildingDataType;

// Multiplier rate for zone type
enum {
  REV_RES = 2,
  REV_IND = 4,
  REV_COM = 7
}revenueZones;

enum {
  TAX_RES = 0,
  TAX_COM,
  TAX_IND
}taxType;

// STRUCT DEFINITIONS ----------------------

// forward definitions
// (real definitions below)
struct zone;
struct building;

// GAME DATA
typedef struct gameData {
  int year;
  int month; // M_JAN, etc..
  int season; // S_FALL, etc..
  int gameSpeed; // SP_NORMAL, etc..

  int mode; // M_NORMAL, etc...

  int money;

  int population;
  int cityType;

  int totalPowerAvailable;
  int totalPowerUsed;

  int taxRes;
  int taxCom;
  int taxInd;
  int revenueRates[MAX_ZONE_LEVEL + 1];

}gameData;

// TILE
typedef struct tile {
  int x;
  int y;
  int trueIndex;
  int tileType;
  int pollution;
  int landValue;
  int fireDanger;

  int pLineType;  // -1 for none (default)
  int roadType;   // -1 for none (default)
  building* buildingOnTop;
}tile;

// BUILDING
typedef struct building {

  // tiles covered by this building
  std::vector<tile*> tiles;

  // Get all neighbors around the building
  std::vector<building*> neighbors;

  // type uses an enum:
  int type;

  // top left x and y
  int xOrigin;
  int yOrigin;

  // dimensions using tiles as unit:
  int buildingDimension;

  // other attributes:
  int currentPower;
  int requiredPower;

  // tile data modifiers
  int pollution;
  int landValueBoost;

  // if zone type, pointer to the zone
  zone* relatedZone;

}building;







// ZONE DEFINITIONS ----------------


enum {
  TL = 0, // 0 - 2
  TM,
  TR,
  ML, // 3 - 5
  MM,
  MR,
  BL, // 6 - 8
  BM,
  BR

} squarePosition;

enum {
  TYPE_A = 0,
  TYPE_B,
  TYPE_C
} typeVariation;

enum {
  RL0 = 0,
  RL1 = 35,
  RL2 = 90,
  RL3 = 180,
  RL4 = 350,
  RL5 = 850,
  RL6 = 1650,
  RL7 = 3750,
  RL8 = 8500
} RlevelPopMin;

enum {

  CL0 = 0,
  CL1 = 5,
  CL2 = 12,
  CL3 = 24,
  CL4 = 50,
  CL5 = 120,
  CL6 = 250,
  CL7 = 500,
  CL8 = 1000
} ClevelPopMin;

enum {

  IL0 = 0,
  IL1 = 10,
  IL2 = 30,
  IL3 = 60,
  IL4 = 120,
  IL5 = 200,
  IL6 = 250,
  IL7 = 350,
  IL8 = 550
} IlevelPopMin;


// NO LONGER USED!!!
typedef struct zoneBuilding {
  // general info
  int squarePos; // uses squarePosition enum
  int level;  // starts at 0
  int zoneType; // R, C, I
  int typeVariation; // uses typeVariation enum

  // identity
  tile* tileUnder;

  // data:
  int popCur;
  int popCap;
  int pollution;

  zone* parentZone;

  ~zoneBuilding();
};

typedef struct zone {

  int xOrigin;
  int yOrigin;

  int zoneType;

  // TODO
  int zoneLevel;
  int typeVariation;

  int totalPopCur; // current people residing in
  int totalPopCap; // capacity for people

  int totalPollution; // TODO need to update

  building* relatedZoneBuilding;

  // there are always 9 zone tiles inside:
  //std::vector<zoneBuilding*> zoneBuildings; // OLD

}zone;
































// used to access static data struct:
tile* map(int x, int y);


// initiation -------------------
void _randomize();

void _initGameData();







// GAME DATA functions:
void _setCityType(int type);
int _checkNewCityType();
int _updatePopulation();


void _setTotalPowerUsed(int amount);
void _setTotalPowerAvailable(int amount);







// TILE FUNCTIONS --------------------------
int _getTileData(int x, int y, int dataType);

void _zeroTileData(int dataType);

void _setAllTileDataValue(int dataType, int value);

void _setTileType(int xCoord, int yCoord, int type);

void _setTileData(int xCoord, int yCoord, int dataType, int amount);

void _addTileData(int xCoord, int yCoord, int dataType, int amount);

void _addDataCircle(int xOrigin, int yOrigin, int radius, int dataType, int amount);

int _getDataRadius(int data);

void _addAllBuildingData(int dataType);

std::string _tileTypeToString();

void _setTileCircle(int xOrigin, int yOrigin, int radius, int tileType);

std::string _tileDataToString(int dataType);

void _addTileDataRadius(int tileType, int dataType, int radius, int amount);

void _subtractLandValuePollution();

void _setTilesSectionData(int xCoord, int yCoord, int tileDataType);

int _getTileSectionType(tile* tileToGet, int type);

void _updateNeighborSectionTypes(int xCoord, int yCoord, int tileDataType);

void _setBuildingTileData(int tileDataType);




// BUILDING FUNCTIONS ----------------------

building* _getBuildingWithCoord(int x, int y);

int _getBuildingSize(building* curBuilding);
int _getBuildingCurPower(building* curBuilding);
int _getBuildingRequiredPower(building* curBuilding);
int _getBuildingPollution(building* curBuilding);
int _getBuildingValueBoost(building* curBuilding);


int _getBuildingDimension(int type);

int _getBuildingPollution(int type);
int _getBuildingLandValues(int bType);
int _getBuildingFireDangers(int bType);

int _getBuildingData(building* buildingID, int dataType);

void _setBuildingTiles(building* buildingID, int x, int y, int dimension);

building* _newBuilding(int type, int x, int y);

int _checkPlacement(int type, int x, int y);

int _getBuildingVectorSize();

std::string _buildingInfoToString();

int _checkMoney(int amount);

void _setBuildingNeighbors(building* buildingID);

int _getBuildingPowerRequirements(int buildingType);

void _removeMyselfFromNeighbors(building* buildingID);

int _getRequiredPowerAllTypes(building* buildingID);

void _buildingResetTilesUnderneath(building* deleteBuilding, int tileType);







// Roads:
std::string _roadsToString();

int _getRoadsVectorSize();











// Zone Functions
int _zoneEnumToTileTypeEnum(int zoneType);
int _BtypeToZtype(int bType);

int _getZoneBuildingX(int squarePos);
int _getZoneBuildingY(int squarePos);
int _getZoneBuildingPopMin(int zoneType, int level);

int _initZoneBuildings(zone* zoneID);
zone* _newZone(int xCoord, int yCoord, int zoneType);

void _zoneResetTilesUnderneath(zone* deleteZone, int tileType);

void _cleanUpAllZones();
void _clearOneZone(zone* deleteZone);

std::string _zoneBuildingToString(int zoneType); // OLD
std::string _zonesToString(int zoneType); // NEW

void _growZones(int zoneType);
int _calcPopGrowth(zoneBuilding* curZ);

int _getPopulation(int zoneType);

void _updateZoneBuildingLevel(zoneBuilding* curZB);

int _zoneBuildingGetRequiredPower(zoneBuilding* curZB);

int _zoneGetTotalRequiredPower(zone* zoneID);

int _getTaxRevenue(int zoneType);






// POWER / ELECTRICITY Functions:
double _getPowerUsageRatio(int capacity, int used);

int _getPowerPlantPower(int type);

void _sendElectricity();

void _consumeElectricity();















// MAP GENERATION FUNCTIONS ----------------
void _growSeeds(int type);

void _grow(int type, int r, int c);

void _fillSeedHoles(int type);






















// UTILITY FUNCTIONS------------------------

int _getIntRange(int min, int max);

















// INTERFACE ----------------------------------------------

// Init
GMEXPORT double initDLL();
GMEXPORT double initMap();
GMEXPORT double mapEnd();

// Game Data:
GMEXPORT double getGameYear();
GMEXPORT double getGameMonth();
GMEXPORT double getGameSeason();
GMEXPORT double getGameMode();
GMEXPORT double getGameSpeed();
GMEXPORT double getPopulation();
GMEXPORT double getCityType();

GMEXPORT double getTaxRate(double type);
GMEXPORT double setTaxRate(double type, double val);

GMEXPORT double incrementGameMonth();
GMEXPORT double setGameMode(double mode);
GMEXPORT double setGameSpeed(double speed);
GMEXPORT double getGameMoney();
GMEXPORT double checkCanSpend(double cost);
GMEXPORT double deductFunds(double cost);
GMEXPORT double addFunds(double cost);
GMEXPORT double setPopulation(double pop);

GMEXPORT double updatePopulationZones();


// Tile functions
GMEXPORT double seedMap(double type, double seedAmount);
GMEXPORT double growSeeds(double type, double amount);
GMEXPORT double setTileType(double xCoord, double yCoord, double type);
GMEXPORT char* tileTypeToString();


// Tile Data
GMEXPORT double zeroTileData(double dataType);
GMEXPORT double setAllTileDataValue(double dataType, double value);
GMEXPORT double addDataCircle(double x, double y, double radius, double dataType, double amount);
GMEXPORT double addAllBuildingData(double dataType);
GMEXPORT char* tileDataToString(double dataType);
GMEXPORT double addWaterTileValue(double dataType, double radius, double amount);
GMEXPORT double addTreeTileValue(double dataType, double radius, double amount);
GMEXPORT double subtractLandValuePollution();
GMEXPORT double getTileSectionType(double x, double y, int tileDataType);
GMEXPORT double setBuildingTileData(double tileDataType);


// Building Functions
GMEXPORT char* getBuildingInfo(double infoType, double x, double y);
GMEXPORT double addBuilding(double type, double x, double y);
GMEXPORT double removeBuilding(double xOrigin, double yOrigin);
GMEXPORT double getBuildingVectorSize();
GMEXPORT double getBuildingPrice(double buildingType);
GMEXPORT char* buildingsToString();


// Roads Functions:
GMEXPORT char* roadsToString();
GMEXPORT double getRoadsVectorSize();


// Zone Functions
GMEXPORT double addZone(double xCoord, double yCoord, double zoneType);
GMEXPORT char* zoneBuildingsToString(double dataType);
GMEXPORT char* zonesToString(double dataType); // NEW string function
GMEXPORT double growZone(double zoneType);
GMEXPORT double getPopulationZone(double zoneType);
GMEXPORT double cleanUpAllZones();
GMEXPORT double collectTax(double zoneType);


// POWER & ELECTRICITY FUNCTIONS ----------------
GMEXPORT double sendElectricity();
GMEXPORT double consumeElectricityAll();
GMEXPORT double getPowerUsageRatio();


// Utility functions
GMEXPORT double getRandomRange(double min, double max);
GMEXPORT double getClock();
GMEXPORT double getTime(double clockBegin, double clockFinish);


// TESTING/DEBUGGING FUNCTIONS-----------------------------
GMEXPORT void _printMapTypes();
GMEXPORT void _testStringOutput();
GMEXPORT void _testPrintBuildingList();
GMEXPORT void _testGameData(int months);
GMEXPORT void _testPrintTileData(int dataType);
GMEXPORT void _testPrintZoneString(int zoneType);
GMEXPORT double _testZoneGrowthAlgorithm(double level, double landValue);
GMEXPORT double _testBuildingNeighbors();
GMEXPORT double _testPowerSurge();
GMEXPORT double _testRoadTypes();
GMEXPORT double _testRoadPrintString();
GMEXPORT double _testPLINETypes();
GMEXPORT double _testPowerRoad();
GMEXPORT double _testZoneGrowthPowerless();
GMEXPORT double _testPrintZoneLevels(int zoneType);
GMEXPORT double _testCollectRevenue();
GMEXPORT double _deepDebugPopGrowth();
#endif

