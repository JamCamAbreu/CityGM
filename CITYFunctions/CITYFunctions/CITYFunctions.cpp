// CITYFunctions.cpp : Defines the exported functions for the DLL application.
#pragma once
#include "CITYFunctions.h"

// (for DEBUGGING):
#include <iostream>

// GLOBAL VARIABLES AND POINTERS
gameData curGameData;
tile newMap[MAP_DIMENSION][MAP_DIMENSION];
tile* mapStartAddress = &newMap[0][0];

int mode;

// containers (that stay persistant throughout the life of the DLL)
std::vector<building*> v_buildings; // cleaned up in mapEnd function

std::list<zone*> Rzones;            // cleaned up in mapEnd function
std::list<zone*> Czones;
std::list<zone*> Izones;


tile* map(int x, int y) {

  // TODO: Make sure this doesn't break anything
  // Bounds Checking:
  if (x < 0 || x > MAP_DIMENSION)
    return NULL;
  if (y < 0 || y > MAP_DIMENSION)
    return NULL;

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

  curGameData.money = 16000;

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

int _updatePopulation() {

  // loop through each zone type and add up all of the population.
  int population = 0;

  // R Zones:
  population += _getPopulation(Z_RES);

  // C Zones:
  population += _getPopulation(Z_COM);

  // I Zones:
  population += _getPopulation(Z_IND);

  if (population < 1)
    population = 1;

  return population;
}




















// Tile Functions ---------------
void _setTileType(int xCoord, int yCoord, int type) {
    map(xCoord,yCoord)->tileType = type;
}

std::string _tileTypeToString() {
  std::string typeData = "";

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

        case TT_ZR:
          typeData += CHAR_RZONE;
          break;

        case TT_ZC:
          typeData += CHAR_CZONE;
          break;

        case TT_ZI:
          typeData += CHAR_IZONE;
          break;

        default:
          typeData += CHAR_ERROR;
      } // end switch
     iter++;
    }
  }


  return typeData;
}

void _setTileCircle(int xOrigin, int yOrigin, int radius, int tileType) {

  int x, y;

  for (y = -radius; y <= radius; y++) {
    for (x = -radius; x <= radius; x++) {
      if ((x * x) + (y * y) <= (radius * radius)) {

        // bounds checking:
        if ((xOrigin + x > 0) && (xOrigin + x < MAP_DIMENSION - 1) &&
          (yOrigin + y > 0) && (yOrigin + y < MAP_DIMENSION - 1))
          _setTileType(xOrigin + x, yOrigin + y, tileType);

      } // end if
    } // inner for loop
  } // outer for loop

}








// Tile Data Functions -----------

// Get:
int _getTileData(int x, int y, int dataType) {
  
  tile* curTile = map(x, y);
  
  switch (dataType) {
    
    case TDT_ALL: { 
      return -1; // error code
      break;
    }

    case TDT_POLLUTION: { 
      return curTile->pollution;
      break;
    }

    case TDT_LANDVALUE: {
      return curTile->landValue;
      break;
    }

    case TDT_FIREDANGER: {
      return curTile->fireDanger;
      break;
    }

    default: {
      return -2; // error code
      break;
    }

  }
  
  return -3; // error code
}

int _getDataRadius(int data) {
  return ((data / 5) + 1);
}

// Set:
void _zeroTileData(int dataType) {
  tile* curTile;

  for (int r = 0; r < MAP_DIMENSION; r++) {
    for (int c = 0; c < MAP_DIMENSION; c++) {
      curTile = map(c, r);
      if (curTile->tileType == TT_WATER)
        _setTileData(c, r, dataType, -1); // water code
      else
        _setTileData(c, r, dataType, 0);
    }
  }

}

void _setAllTileDataValue(int dataType, int value) {
  tile* curTile;

  for (int r = 0; r < MAP_DIMENSION; r++) {
    for (int c = 0; c < MAP_DIMENSION; c++) {
      curTile = map(c, r);
      if (curTile->tileType == TT_WATER)
        _setTileData(c, r, dataType, -1); // water code
      else
        _setTileData(c, r, dataType, value);
    }
  }
}

void _setTileData(int xCoord, int yCoord, int dataType, int amount) {

  tile* curTile = map(xCoord, yCoord);

  switch (dataType) {

    case TDT_ALL: { 
      curTile->pollution = amount;
      curTile->landValue = amount;
      curTile->fireDanger = amount;
      break;
    }

    case TDT_POLLUTION: { 
      curTile->pollution = amount;
      break;
    }

    case TDT_LANDVALUE: {
      curTile->landValue = amount;
      break;
    }

    case TDT_FIREDANGER: {
      curTile->fireDanger = amount;
      break;
    }

    default: {
      break;
    }

  } // end switch

}

// Add:
void _addTileData(int xCoord, int yCoord, int dataType, int amount) {

  tile* curTile = map(xCoord, yCoord);

  switch (dataType) {

    case TDT_POLLUTION: { 
      curTile->pollution += amount;
      break;
    }

    case TDT_LANDVALUE: {
      curTile->landValue += amount;
      break;
    }

    case TDT_FIREDANGER: {
      curTile->fireDanger += amount;
      break;
    }

    default: {
      break;
    }

  } // end switch

}

void _addDataCircle(int xOrigin, int yOrigin, int radius, int dataType, int amount) {

  int x, y, distance;

  for (y = -radius; y <= radius; y++) {
    for (x = -radius; x <= radius; x++) {
      if ((x * x) + (y * y) <= (radius * radius)) {

        // bounds checking:
        if ((xOrigin + x > 0) && (xOrigin + x < MAP_DIMENSION - 1) &&
          (yOrigin + y > 0) && (yOrigin + y < MAP_DIMENSION - 1)) {

          // calculate the distance from radius:
          distance = (int)std::sqrt((double)((y*y) + (x*x)));
          if (distance == 0)
            distance = 1;


          // set data
          _addTileData(xOrigin + x, yOrigin + y, dataType, (amount/distance));
        }

      } // end if
    } // inner for loop
  } // outer for loop

}

void _addAllBuildingData(int dataType) {
  int size = _getBuildingVectorSize();
  building* curBuilding;
  int dataRadius;
  int dataValue;

  // loop through buildings in vector and add their pollution to the tiles around 
  // them in a radius. 
  for (int i = 0; i < size; i++) {
    curBuilding = (v_buildings[i]);
    dataValue = _getBuildingData(curBuilding, dataType);

    if (dataValue > 0) { // (0 has no effect)
      // calculate radius used based on value:
      dataRadius = _getDataRadius(dataValue);

      // set data in circle around building:
      _addDataCircle(curBuilding->xOrigin, curBuilding->yOrigin,
       dataRadius, dataType, dataValue);
    }
  } // end for
  

}

void _addWaterTileValue(int dataType, int radius, int amount) {

  // iterate through all tiles, adding data in a largish 
  // radius if the tile type is of water type.
  tile* curTile;

  for (int r = 0; r < MAP_DIMENSION; r++) {
    for (int c = 0; c < MAP_DIMENSION; c++) {
      curTile = map(c, r);
      if (curTile->tileType == TT_WATER)
        _addDataCircle(c, r, radius, dataType, amount);
    }
  }


  // iterate through tiles again, reseting the water tiles
  // themselves to having a -1 value for map printing. 
  for (int r = 0; r < MAP_DIMENSION; r++) {
    for (int c = 0; c < MAP_DIMENSION; c++) {
      curTile = map(c, r);
      if (curTile->tileType == TT_WATER)
        _setTileData(c, r, dataType, -1); // water code
    }
  }



}

// Subtract:
void _subtractLandValuePollution() {
  tile* curTile;

  for (int r = 0; r < MAP_DIMENSION; r++) {
    for (int c = 0; c < MAP_DIMENSION; c++) {
      curTile = map(c, r);
      if (curTile->tileType != TT_WATER) {

        int pol = ((curTile->pollution)/2); // -50 is worst penalty
        _addTileData(c, r, TDT_LANDVALUE, (-pol));

      } // end if != TT_WATER
    
    } // outer
  } // inner


}

// String:
std::string _tileDataToString(int dataType) {
  
  std::string dataString = "";
  tile* iter;
  int value;
  for (int r = 0; r < MAP_DIMENSION; r++) {
    for (int c = 0; c < MAP_DIMENSION; c++) {

      value = _getTileData(c, r, dataType);
      if (value > 0)
        dataString += std::to_string(value);
      else if (value == -1)
        dataString += 'W'; // water code
      dataString += ',';
    }
  }

  return dataString;
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
  return -1; // error code
}

int _getBuildingPollution(int type) {

  // use a switch and enum to return width:
  switch (type) {
    case BT_POLICE: {
      return 20;
      break;
      }

    case BT_FIRE: {
      return 25;
      break;
      }

    case BT_SCHOOL: {
      return 20;
      break;
      }

    case BT_HOSPITAL: {
      return 25;
      break;
      }

    case BT_COAL: {
      return 50;
      break;
      }

    case BT_NUCLEAR: {
      return 20;
      break;
      }

    case BT_WATERTOWER: {
      return 22;
      break;
      }

    case BT_ARCADE: {
      return 15;
      break;
      }

    case BT_AIRPORT: {
      return 55;
      break;
      }

    default: {
      return -1; // error code
      break;
    }
  } // end switch
  return -1; // error code

}

int _getBuildingData(building* buildingID, int dataType) {

  switch (dataType) {

    case TDT_POLLUTION: {
      return buildingID->pollution;
      break;
      }

    case TDT_LANDVALUE: {
      return buildingID->landValueBoost;
      break;
      }

    default: {
      return -1; // error code
      break;
    }

  } // end switch
   return -1; // error code
}

void _setBuildingTiles(building* buildingID, int x, int y, int dimension) {

  // push all tiles underneath the building starting from top 
  // left corner:
  tile* containedTile;
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      containedTile = map(x + i, y + j);
      containedTile->tileType = TT_BUILDING;
      containedTile->buildingOnTop = buildingID;
      buildingID->tiles.push_back(containedTile);
    }
  }
}

int _getBuildingPowerRequirements(int buildingType) {

  // use a switch and enum to return width:
  switch (buildingType) {
    case BT_TREE: {
      return 0;
      break;
      }

    case BT_ROAD: {
      return 0;
      break;
      }

    case BT_PLINE: {
      return 2;
      break;
      }

    case BT_RZONE: {
      return -2;
      break;
      }

    case BT_CZONE: {
      return -2;
      break;
      }

    case BT_IZONE: {
      return -2;
      break;
      }

    case BT_POLICE: {
      return 14;
      break;
      }

    case BT_FIRE: {
      return 10;
      break;
      }

    case BT_SCHOOL: {
      return 20;
      break;
      }

    case BT_HOSPITAL: {
      return 25;
      break;
      }

    case BT_COAL: {
      return 0;
      break;
      }

    case BT_NUCLEAR: {
      return 0;
      break;
      }

    case BT_WATERTOWER: {
      return 25;
      break;
      }

    case BT_ARCADE: {
      return 18;
      break;
      }

    case BT_AIRPORT: {
      return 50;
      break;
      }

    default: {
      return -1;
      break;
    }
  } // end switch
  return -1; // error code

  // -2 is the code for zones

}

building* _newBuilding(int type, int x, int y) {

  building* newBuilding = new building;

  // attribute defaults:
  newBuilding->type = type;
  newBuilding->xOrigin = x;
  newBuilding->yOrigin = y;
  newBuilding->buildingDimension = _getBuildingDimension(type);
  newBuilding->currentPower = 0;
  newBuilding->requiredPower = _getBuildingPowerRequirements(type);
  newBuilding->pollution = _getBuildingPollution(type);

  // get size in tiles:
  int dim = _getBuildingDimension(type);

  // set tiles associated with building
  _setBuildingTiles(newBuilding, x, y, dim);

  // Get all of the pointers to buildings around this building:
  _setBuildingNeighbors(newBuilding);

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

void _setBuildingNeighbors(building* buildingID) {
  int tilesPerEdge = buildingID->buildingDimension;
  int i;
  tile* curTile;

  // North:
  for (i = 0; i < tilesPerEdge; i++) {
    curTile = map(buildingID->xOrigin + i, buildingID->yOrigin - 1);
    if (curTile != NULL && curTile->buildingOnTop != NULL) {
      if (std::find(buildingID->neighbors.begin(), buildingID->neighbors.end(), curTile->buildingOnTop) == buildingID->neighbors.end())
        buildingID->neighbors.push_back(curTile->buildingOnTop);
    }
  }

  // East:
  for (i = 0; i < tilesPerEdge; i++) {
    curTile = map(buildingID->xOrigin + buildingID->buildingDimension + 1, buildingID->yOrigin + i);
    if (curTile != NULL && curTile->buildingOnTop != NULL) {
      if (std::find(buildingID->neighbors.begin(), buildingID->neighbors.end(), curTile->buildingOnTop) == buildingID->neighbors.end())
        buildingID->neighbors.push_back(curTile->buildingOnTop);
    }
  }

  // South:
  for (i = 0; i < tilesPerEdge; i++) {
    curTile = map(buildingID->xOrigin + i, buildingID->yOrigin + buildingID->buildingDimension + 1);
    if (curTile != NULL && curTile->buildingOnTop != NULL) {
      if (std::find(buildingID->neighbors.begin(), buildingID->neighbors.end(), curTile->buildingOnTop) == buildingID->neighbors.end())
        buildingID->neighbors.push_back(curTile->buildingOnTop);
    }
  }

  // West:
  for (i = 0; i < tilesPerEdge; i++) {
    curTile = map(buildingID->xOrigin - 1, buildingID->yOrigin + i);
    if (curTile != NULL && curTile->buildingOnTop != NULL) {
      if (std::find(buildingID->neighbors.begin(), buildingID->neighbors.end(), curTile->buildingOnTop) == buildingID->neighbors.end())
        buildingID->neighbors.push_back(curTile->buildingOnTop);
    }
  }


  // now change THOSE neighbors to having ME as a neighbor:
  for (auto it : buildingID->neighbors) {
      if (std::find(it->neighbors.begin(), it->neighbors.end(), buildingID) == it->neighbors.end())
        it->neighbors.push_back(buildingID);
  }

}


void removeMyselfFromNeighbors(building* buildingID) {

  // Update all neighbors to remove me from their neighbor list:
  for (auto it : buildingID->neighbors) {
    it->neighbors.erase(std::remove(
      it->neighbors.begin(), it->neighbors.end(), buildingID), it->neighbors.end());
  }
}









// Zone functions:

// TODO: Make a building (which is the size of the zone) that acts like 
// a large building to other objects that want to interact with the zone
// note: is this the best solution?


// General:
int _zoneEnumToTileTypeEnum(int zoneType) {

  if (zoneType == Z_RES)
    return TT_ZR;
  else if (zoneType == Z_COM)
    return TT_ZC;
  else if (zoneType == Z_IND)
    return TT_ZI;

  else
    return -1; // error code
}

int _BtypeToZtype(int bType) {
  if (bType == BT_RZONE)
    return Z_RES;
  else if (bType == BT_CZONE)
    return Z_COM;
  else if (bType == BT_IZONE)
    return Z_IND;
  else
    return -1; // error code
}

// Get:
int _getZoneBuildingX(int squarePos) {
  if (squarePos == 0 || squarePos == 3 || squarePos == 6)
    return 0;
  else if (squarePos == 1 || squarePos == 4 || squarePos == 7)
    return 1;
  else
    return 2;
}
int _getZoneBuildingY(int squarePos) {
  if (squarePos == 0 || squarePos == 1 || squarePos == 2)
    return 0;
  else if (squarePos == 3 || squarePos == 4 || squarePos == 5)
    return 1;
  else
    return 2;
}
int _getZoneBuildingPopMin(int zoneType, int level) {

  switch (zoneType) {

  case Z_RES: {
    switch (level) {
    case 0:  {
      return RL0;
      break; }

    case 1:  {
      return RL1;
      break; }

    case 2:  {
      return RL2;
      break; }

    case 3:  {
      return RL3;
      break; }

    case 4:  {
      return RL4;
      break; }

    case 5:  {
      return RL5;
      break; }

    case 6:  {
      return RL6;
      break; }

    case 7:  {
      return RL7;
      break; }

    case 8:  {
      return RL8;
      break; }

    default: {
      return -2; // error code
      break; }
    } // end inner switch
    break; }

  case Z_COM: {
    switch (level) {
    case 0:  {
      return CL0;
      break; }

    case 1:  {
      return CL1;
      break; }

    case 2:  {
      return CL2;
      break; }

    case 3:  {
      return CL3;
      break; }

    case 4:  {
      return CL4;
      break; }

    case 5:  {
      return CL5;
      break; }

    case 6:  {
      return CL6;
      break; }

    case 7:  {
      return CL7;
      break; }

    case 8:  {
      return CL8;
      break; }

    default: {
      return -2; // error code
      break; }
    } // end inner switch
    break; }

  case Z_IND: {
    switch (level) {
    case 0:  {
      return IL0;
      break; }

    case 1:  {
      return IL1;
      break; }

    case 2:  {
      return IL2;
      break; }

    case 3:  {
      return IL3;
      break; }

    case 4:  {
      return IL4;
      break; }

    case 5:  {
      return IL5;
      break; }

    case 6:  {
      return IL6;
      break; }

    case 7:  {
      return IL7;
      break; }

    case 8:  {
      return IL8;
      break; }

    default: {
      return -2; // error code
      break; }
    } // end inner switch
    break; }

  default: {
    return -1; // error code
    break; }

  } // end outer switch

  return -1; // error code
}

// Init:
int _initZoneBuildings(zone* zoneID) {

  zoneID->zoneBuildings.resize(9); // always 9 zone buildings

  for (int i = 0; i < 9; i++) {

    zoneBuilding* curZB = new zoneBuilding;
    curZB->squarePos = i;
    curZB->level = 0;
    curZB->zoneType = zoneID->zoneType;
    curZB->typeVariation = _getIntRange(TYPE_A, TYPE_C);

    int xPos = zoneID->xOrigin + (_getZoneBuildingX(i));
    int yPos = zoneID->yOrigin + (_getZoneBuildingY(i));
    curZB->tileUnder = map(xPos, yPos);

    curZB->popCur = 1;
    curZB->popCap = _getZoneBuildingPopMin(zoneID->zoneType, 1);
    curZB->pollution = 0;

    // set tile underneath to have correct tile type:
    curZB->tileUnder->tileType = _zoneEnumToTileTypeEnum(zoneID->zoneType);

    // set correct parent zone pointer:
    curZB->parentZone = zoneID;

    // LAST: update zoneBuildings[i]
    zoneID->zoneBuildings[i] = curZB;
  }

  return 0;
}

zone* _newZone(int xCoord, int yCoord, int zoneType) {

  zone* newZone = new zone;

  switch (zoneType) {

  case Z_RES: {
    newZone->xOrigin = xCoord;
    newZone->yOrigin = yCoord;
    newZone->zoneType = Z_RES;
    newZone->totalPopCap = RL1;
    newZone->totalPopCur = 0;
    newZone->totalPollution = 0;
    _initZoneBuildings(newZone);
    break; }

  case Z_COM: {
    newZone->xOrigin = xCoord;
    newZone->yOrigin = yCoord;
    newZone->zoneType = Z_COM;
    newZone->totalPopCap = CL1;
    newZone->totalPopCur = 0;
    newZone->totalPollution = 0;
    _initZoneBuildings(newZone);
    break; }

  case Z_IND: {
    newZone->xOrigin = xCoord;
    newZone->yOrigin = yCoord;
    newZone->zoneType = Z_IND;
    newZone->totalPopCap = IL1;
    newZone->totalPopCur = 0;
    newZone->totalPollution = 0;
    _initZoneBuildings(newZone);
    break; }

  default: {
    newZone->xOrigin = xCoord;
    newZone->yOrigin = yCoord;
    newZone->zoneType = -1; // error type
    newZone->totalPopCap = 0;
    newZone->totalPopCur = 0;
    newZone->totalPollution = 0;
    _initZoneBuildings(newZone);

    break; }
  } // end switch

  return newZone;
}


// Destroy (free from memory)
void _cleanUpAllZones() {

  // NEED TO UPDATE TILES UNDERNEATH! 


  // Residential:
  // Cleanup all zoneBuildings in linked list:
  for (std::list<zone*>::iterator it = Rzones.begin(); it != Rzones.end(); it++)
    (*it)->zoneBuildings.clear();
  // cleanup zone itself:
  Rzones.clear();

  // Commercial:
  // Cleanup all zoneBuildings in linked list:
  for (std::list<zone*>::iterator itC = Czones.begin(); itC != Czones.end(); itC++)
    (*itC)->zoneBuildings.clear();
  // cleanup zone itself:
  Czones.clear();

  // Industrial:
  // Cleanup all zoneBuildings in linked list:
  for (std::list<zone*>::iterator itI = Izones.begin(); itI != Izones.end(); itI++)
    (*itI)->zoneBuildings.clear();
  // cleanup zone itself:
  Izones.clear();
}

void _clearOneZone(zone* deleteZone) {

  // look up zone in any of the lists:
  if (deleteZone != NULL)
    Rzones.remove(deleteZone);
  if (deleteZone != NULL)
    Czones.remove(deleteZone);
  if (deleteZone != NULL)
    Izones.remove(deleteZone);

  if (deleteZone != NULL) {
    deleteZone->zoneBuildings.clear();
    delete deleteZone;
  }
}

// destructor (clean up buildings by changing tiles underneath):
zoneBuilding::~zoneBuilding() {
  // reset tile underneath:
  this->tileUnder->tileType = TT_GRASS;
}

// String:
std::string _zoneBuildingToString(int zoneType) {


  // FINISHED STRING WILL HAVE THE FOLLOWING SYNTAX:
  // xCoord,yCoord,ZoneType,level,typeVar.etc...
  // note the dot after each building

  std::string zoneBuildingInfo = "";
  std::string buffer = "";
  char dataDivider = ',';
  char elementDivider = ';';

  bool debug = false;

  std::list<zone*>::iterator iter;
  std::list<zone*>::iterator endZoneList;
  // first iterate through all zones in given data type:
  if (zoneType == Z_RES) {
    iter = Rzones.begin();
    endZoneList = Rzones.end();
  }
  else if (zoneType == Z_COM) {
    iter = Czones.begin();
    endZoneList = Czones.end();
  }
  else if (zoneType == Z_IND) {
    iter = Izones.begin();
    endZoneList = Izones.end();
  }
  else {
    zoneBuildingInfo += "zoneType error: default case";
    return zoneBuildingInfo;
  }

  if (debug) {
  // debug:
  std::cout << std::endl;
  std::cout << "Zone list for type: " << zoneType;
  std::cout << std::endl;
  }


  while (iter != endZoneList) {

    if (debug) {
      // debug:
      std::cout << "Zone. X=" << (*iter)->xOrigin << ", Y=" << (*iter)->yOrigin;
      std::cout << ", Type=" << (*iter)->zoneType << "\nBuilding Info:\n";
    }

    // access zoneBuildings in zone:
    std::vector<zoneBuilding*>::iterator bIter = (*iter)->zoneBuildings.begin();
    std::vector<zoneBuilding*>::iterator bIterEnd = (*iter)->zoneBuildings.end();
    for (bIter; bIter != bIterEnd; bIter++) {

      int CURxCordinate = (*bIter)->tileUnder->x;
      int CURyCordinate = (*bIter)->tileUnder->y;
      int CURZoneType = (*bIter)->zoneType;
      int CURlevel = (*bIter)->level;
      int CURtypeVar = (*bIter)->typeVariation;
      int CURsquarePos = (*bIter)->squarePos;

      // ADD TO STRING:
      std::string data = "";
      char dataDivider = ',';
      char buildingDivider = '.';
      // add x to string:
      data = std::to_string(CURxCordinate);
      zoneBuildingInfo += data;
      zoneBuildingInfo += dataDivider;

      // add y to string:
      data = std::to_string(CURyCordinate);
      zoneBuildingInfo += data;
      zoneBuildingInfo += dataDivider;

      // add zoneType to string:
      data = std::to_string(CURZoneType);
      zoneBuildingInfo += data;
      zoneBuildingInfo += dataDivider;

      // add level to string:
      data = std::to_string(CURlevel);
      zoneBuildingInfo += data;
      zoneBuildingInfo += dataDivider;

      // add typeVar to string:
      data = std::to_string(CURtypeVar);
      zoneBuildingInfo += data;
      zoneBuildingInfo += dataDivider;

      // add square position to string:
      data = std::to_string(CURsquarePos);
      zoneBuildingInfo += data;

      // add divider between buildings:
      zoneBuildingInfo += buildingDivider;
      
      if (debug) {
        // debug: 
        std::cout << "ZB. X=" << CURxCordinate << ", Y=" << CURyCordinate;
        std::cout << ", ZT=" << CURZoneType << ", LVL=" << CURlevel;
        std::cout << ", Tvar=" << CURtypeVar << "\n";
      }

    } // end loop through zoneBuildings

    if (debug) {
      // debug:
      std::cout << std::endl;
    }

    iter++;
    } // end while (iteration through Llist)

  if (debug) {
    // debug:
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << zoneBuildingInfo;
    std::cout << std::endl;
    std::cout << std::endl;
  }


  return zoneBuildingInfo;
}


// Grow:
void _growZones(int zoneType) {

  int ready = false;
  std::list<zone*>::iterator iter;
  std::list<zone*>::iterator endZoneList;
  // first iterate through all zones in given data type:
  if (zoneType == Z_RES) {
    iter = Rzones.begin();
    endZoneList = Rzones.end();
    ready = true;
  }
  else if (zoneType == Z_COM) {
    iter = Czones.begin();
    endZoneList = Czones.end();
    ready = true;
  }
  else if (zoneType == Z_IND) {
    iter = Izones.begin();
    endZoneList = Izones.end();
    ready = true;
  }

  if (ready) {

    while (iter != endZoneList) {

      // not ALL zones are updated every time!
      int chance = _getIntRange(1, 10);
      int highestChance = 7;
      if (chance <= highestChance) {

        // access zoneBuildings in zone:
        std::vector<zoneBuilding*>::iterator bIter = (*iter)->zoneBuildings.begin();
        std::vector<zoneBuilding*>::iterator bIterEnd = (*iter)->zoneBuildings.end();
        for (bIter; bIter != bIterEnd; bIter++) {

          // not ALL buildings in zone are updated.
          int chanceB = _getIntRange(1, 10);
          int highestChanceB = 4;
          if (chanceB <= highestChanceB) {

            int growth = _calcPopGrowth((*bIter));
            (*bIter)->popCur += growth;
            if ((*bIter)->popCur < 0)
              (*bIter)->popCur = 0;
            // update level:
            _updateZoneBuildingLevel((*bIter));

          } // end if chance (buildings within zone)

        } // end inner for (each building in zone)

      iter++;

      } // end if chance (zones)
    } // end while
  } // end if ready


}

int _calcPopGrowth(zoneBuilding* curZ) {

  int level = curZ->level;
  int landValue = curZ->tileUnder->landValue;

  // pop growth based on level, some randomness
  double popGrowth = 10*(level + 1) + ((level + 1)*(_getIntRange(-(level + 4), level + 4)));

  // Some land value impact:
  int lv = 100 - landValue;
  double lvImpact = (double)lv / 50.0;
  if (lvImpact <= 0)
    lvImpact = 1;
  popGrowth = popGrowth / lvImpact;


  // punish for low land value, reward for high:
  double lvLuck = (landValue - 50) / 20;
  double luck = _getIntRange(lvLuck - 2, lvLuck + 2);
  if (luck == 0)
    luck = 1;
  popGrowth = popGrowth*luck;

  // Population can get crazy with high land values, so cap it:
  //double popGrowthMax = (level + 1)*((level + 2) / 2) * 30;
  double popGrowthMax = (int)(_getZoneBuildingPopMin(curZ->zoneType, level)/5);
  if (popGrowth > popGrowthMax)
    popGrowth = popGrowthMax;

  return (int)popGrowth;
}

int _getPopulation(int zoneType) {

  // Adds up the population of ALL zoneBuildings for a zone type. 
  int count = 0;

  int ready = false;
  std::list<zone*>::iterator iter;
  std::list<zone*>::iterator endZoneList;
  // first iterate through all zones in given data type:
  if (zoneType == Z_RES) {
    iter = Rzones.begin();
    endZoneList = Rzones.end();
    ready = true;
  }
  else if (zoneType == Z_COM) {
    iter = Czones.begin();
    endZoneList = Czones.end();
    ready = true;
  }
  else if (zoneType == Z_IND) {
    iter = Izones.begin();
    endZoneList = Izones.end();
    ready = true;
  }

  if (ready) {

    while (iter != endZoneList) {

      // access zoneBuildings in zone:
      std::vector<zoneBuilding*>::iterator bIter = (*iter)->zoneBuildings.begin();
      std::vector<zoneBuilding*>::iterator bIterEnd = (*iter)->zoneBuildings.end();
      for (bIter; bIter != bIterEnd; bIter++) {
        count += (*bIter)->popCur;
      } // end inner for (each building in zone)

    iter++;

    } // end while
  } // end if ready

  return count;
}


void _updateZoneBuildingLevel(zoneBuilding* curZB) {

  // make sure popCap is correct first:
  curZB->popCap = _getZoneBuildingPopMin(curZB->zoneType, curZB->level);

  // Goes up any levels?
  while (curZB->popCur > curZB->popCap) {
      curZB->level++;
      curZB->popCap = _getZoneBuildingPopMin(curZB->zoneType, curZB->level);
  }

  // Goes down any levels?
  int levelBelow = _getZoneBuildingPopMin(curZB->zoneType, (curZB->level - 1));
  while (curZB->popCur < levelBelow) {
    curZB->level--;
    if (curZB->level > 0)
      levelBelow = _getZoneBuildingPopMin(curZB->zoneType, (curZB->level - 1));
  }

}

int _calculateZonePowerConsumption(zoneBuilding* curZB) {

  zone* parentZone = curZB->parentZone;

  int sumPowerConsumption = 0;
  for (int i = 0; i < 9; i++) {

    int level = parentZone->zoneBuildings[i]->level;

    sumPowerConsumption = level * 10; // REDO

  }


  return sumPowerConsumption;
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

double getClock() {

  clock_t t = clock();
  int convert = (int)t;

  return convert;

}

double getTime(double clockBegin, double clockFinish) {

  double time = clockFinish - clockBegin;
  return (time / CLOCKS_PER_SEC);
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
      iter->pollution = 0;
      iter->landValue = 50;
      iter->fireDanger = 0;
      iter->buildingOnTop = NULL;

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

  // clean up all three zones, and their zone buildings:
  _cleanUpAllZones();



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

double updatePopulationZones() {
  int newCityType = 0;

  curGameData.population = _updatePopulation();

  // sets new type, and returns 1 if new type achieved
  newCityType = _checkNewCityType();

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







// TILE DATA FUNCTIONS --------
double zeroTileData(double dataType) {
  int dataTypeInt = (int)dataType;
  _zeroTileData(dataTypeInt);
  return 0;
}

double setAllTileDataValue(double dataType, double value) {
  int typeInt = (int)dataType;
  int valueInt = (int)value;

  _setAllTileDataValue(typeInt, valueInt);
  return 0;
}

double addDataCircle(double x, double y, double radius, double dataType, double amount) {

  int xInt = (int)x;
  int yInt = (int)y;
  int radiusInt = (int)radius;
  int dataTypeInt = (int)dataType;
  int amountInt = (int)amount;

  _addDataCircle(xInt, yInt, radiusInt, dataTypeInt, amountInt);

  return 0;
}

double addAllBuildingData(double dataType) {
  int typeInt = (int)dataType;
  // WARNING: make sure to clear first!
  _addAllBuildingData(typeInt);

  return 0;
}

char* tileDataToString(double dataType) {

  int dataInt = (int)dataType;
  std::string getString = _tileDataToString(dataInt);

  char* dataString = new char[getString.length() + 1];
  std::strcpy(dataString, getString.c_str());

  return dataString;
}

double addWaterTileValue(double dataType, double radius, double amount) {
  int typeInt = (int)dataType;
  int radiusInt = (int)radius;
  int amountInt = (int)amount;

  _addWaterTileValue(typeInt, radiusInt, amountInt);
  return 0;
}

double subtractLandValuePollution() {
  _subtractLandValuePollution();
  return 0;
}




// Zone Functions

double addZone(double xCoord, double yCoord, double zoneType) {

  int xInt = (int)xCoord;
  int yInt = (int)yCoord;
  int zTypeInt = (int)zoneType;

  _newZone(xInt, yInt, zTypeInt);

  return 0;
}

char* zoneBuildingsToString(double dataType) {
  int dataTypeInt = (int)dataType;
  std::string getString = _zoneBuildingToString(dataTypeInt);

  char* dataString = new char[getString.length() + 1];
  std::strcpy(dataString, getString.c_str());

  return dataString;
}

double growZone(double zoneType) {
  int typeInt = (int)zoneType;

  _growZones(typeInt);

  return 0;
}

double getPopulationZone(double zoneType) {

  int zoneTypeInt = (int)zoneType;
  double count = (double)_getPopulation(zoneTypeInt);

  return count;
}

double cleanUpAllZones() {
  _cleanUpAllZones();
  return 0;
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

    // Build Road:
    if (type == BT_ROAD) {
      // special code for roads
    }
    // Build Power Line:
    else if (type == BT_PLINE) {
      // special code for power lines
    }
    // Build ZONE:
    else if (type == BT_RZONE || type == BT_CZONE || type == BT_IZONE) {

      int zoneType = _BtypeToZtype(type); // convert enum
      zone* newZone = _newZone(xInt, yInt, zoneType);

      if (type == BT_RZONE)
        Rzones.push_front(newZone);
      else if (type == BT_CZONE)
        Czones.push_front(newZone);
      else if (type == BT_IZONE)
        Izones.push_front(newZone);
      else {
        _clearOneZone(newZone); // invalid type
      }

    }
    // Build Other (like Power Plant, or Police Station, etc...)
    else {
      // create a new building:
      building* newBuilding = _newBuilding(typeInt, xInt, yInt);

      // add building to vector
      v_buildings.push_back(newBuilding);
    }

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
  building* buildingToDelete = deleteTile->buildingOnTop;

  // update tiles underneath:
  for (auto it : buildingToDelete->tiles) {
    it->tileType = TT_GRASS;
    it->buildingOnTop = NULL;
    //it->fireDanger *= 1.5; // increase fire danger from destruction?
    //it->pollution = 0;
  }

  // update neighbors:
  removeMyselfFromNeighbors(buildingToDelete);

  // remove building from buildings list:
  v_buildings.erase(std::remove(v_buildings.begin(), v_buildings.end(), buildingToDelete), v_buildings.end());

  // delete buildingToDelete; // FOR SOME REASON THIS BREAKS EVERYTHING :'(

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

        case TT_ZR:
          std::cout << CHAR_RZONE;
          break;

        case TT_ZC:
          std::cout << CHAR_CZONE;
          break;

        case TT_ZI:
          std::cout << CHAR_IZONE;
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


void _testPrintTileData(int dataType) {

  // NOTE: this does nOT work very good...

  std::string getString = _tileDataToString(dataType);


  char* dataString = new char[getString.length() + 1];
  std::strcpy(dataString, getString.c_str());

  // first, print out the string:
  printf("%s\n\n", dataString);

  // print out using columns:
  int r, c;

  std::cout << std::endl;
  std::cout << "Map Data for dataType: " << dataType << std::endl;
  std::cout << std::endl;

  // convert to cString:
  char* dataStringC = strdup(dataString);

  // first token:
  char* token = strtok(dataStringC, ",");
  // print first string
  if (token != NULL) {
    if (token[0] != '0') {
      std::cout << token;
    }
  }

  for (r = 0; r < MAP_DIMENSION - 1; r++) {
    for (c = 0; c < MAP_DIMENSION - 1; c++) { // first already printed

      if (r != 0 && c != 0) { // skip first
        token = strtok(NULL, ",");
        if (token != NULL) {
          if (token[0] != '0')
            std::cout << token;
          else
            std::cout << "  ";
        }
      }
    } // end inner for
    std::cout << std::endl; // new line for rows
  }

  std::cout << std::endl;
  std::cout << std::endl;

}


void _testPrintZoneString(int zoneType) {

  _zoneBuildingToString(zoneType);

}



double _testZoneGrowthAlgorithm(double level, double landValue) {

  // pop growth based on level, some randomness
  double popGrowth = 10*(level + 1) + ((level + 1)*(_getIntRange(-(level + 4), level + 4)));

  // Some land value impact:
  int lv = 100 - landValue;
  double lvImpact = (double)lv / 50.0;
  if (lvImpact <= 0)
    lvImpact = 1;
  popGrowth = popGrowth / lvImpact;


  // punish for low land value, reward for high:
  double lvLuck = (landValue - 50) / 20;
  double luck = _getIntRange(lvLuck - 2, lvLuck + 2);
  if (luck == 0)
    luck = 1;
  popGrowth = popGrowth*luck;

  // Population can get crazy with high land values, so cap it:
  double popGrowthMax = (level + 1)*((level + 2) / 2) * 30;
  if (popGrowth > popGrowthMax)
    popGrowth = popGrowthMax;

  return (int)popGrowth;

}


double _testBuildingNeighbors() {

  //std::vector<building*> v_buildings; // cleaned up in mapEnd function

  // iterate through all buildings and display their neighbors, if any:


  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "-------startTest--------";
  std::cout << std::endl;

  for (auto it : v_buildings) {
    std::cout << "-building- x=" << it->xOrigin << ", y=" << it->yOrigin;
    std::cout << std::endl;

    std::cout << "How many neighbors?: " << it->neighbors.size();
    std::cout << std::endl;


    int counter = 0;
    for (auto it2 : it->neighbors) {
      if (it2 == NULL)
        std::cout << "\t" << "null" << std::endl;
      else
        std::cout << "\tx=" << it2->xOrigin << ", y=" << it2->yOrigin << std::endl;

      counter++;
    }
    if (counter < 1)
      std::cout << "\t" << "neighbors vector was empty :(" << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
  }




  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "-------endTest--------";
  std::cout << std::endl;

  return 0;
}




