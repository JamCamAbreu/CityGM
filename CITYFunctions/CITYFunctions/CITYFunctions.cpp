// CITYFunctions.cpp : Defines the exported functions for the DLL application.
#pragma once
#include "CITYFunctions.h"

// TODO : The strings that I am passing to game maker (all of the char*
// strings I mean: Are they a memory leak? If I need to, I can pass all
// of those pointers to a vector of char* (just before sending it to GM)
// Every once and a while, I can perform a 'clean' by iterating
// through the vector of char* and deleting them.

// GLOBAL VARIABLES AND POINTERS
gameData curGameData;
tile newMap[MAP_DIMENSION][MAP_DIMENSION];
tile* mapStartAddress = &newMap[0][0];

int mode;

// containers (that stay persistant throughout the life of the DLL)
std::vector<building*> v_buildings; // cleaned up in mapEnd function
std::vector<building*> v_roads;

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

  // need to make this a value passed in by game maker:
  curGameData.money = 99999;

  curGameData.population = 1;
  curGameData.cityType = CT_RURAL;

  curGameData.totalPowerUsed = 0;
  curGameData.totalPowerAvailable = 0;

  curGameData.taxRes = 7;
  curGameData.taxCom = 7;
  curGameData.taxInd = 7;

  // set the revenue rates:
  int prev = 0;
  int newAmount = 0;
  for (int i = 0; i < MAX_ZONE_LEVEL + 1; i++) {
    newAmount = (prev + (i + 1)*2);
    curGameData.revenueRates[i] = newAmount;
    prev = newAmount;
  }
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

void _setTotalPowerUsed(int amount) {
  curGameData.totalPowerUsed = amount;
}

void _setTotalPowerAvailable(int amount) {
  curGameData.totalPowerAvailable = amount;
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

    case TDT_PLINETYPE: {
      return curTile->pLineType;
      break;
    }

    case TDT_ROADTYPE: {
      return curTile->roadType;
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

      // DON'T SET DEFAULTS FOR TILE SECTION TYPE!
      // (because this is used by pollution and land value
      //  reseting, which is done often. );
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

void _addTileDataRadius(int tileType, int dataType, int radius, int amount) {

  // iterate through all tiles, adding data in a largish
  // radius if the tile type is of water type.
  tile* curTile;

  for (int r = 0; r < MAP_DIMENSION; r++) {
    for (int c = 0; c < MAP_DIMENSION; c++) {
      curTile = map(c, r);
      if (curTile->tileType == tileType)
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

// set road/powerline tile data:
/*
  * bit setting pattern:
                                     |3|
                                  |4| X |1|
                                     |2|
  * tile codes:
          ** ZERO PIECES ADJACENT **
      0000            0       Horizontal Lane (default)

          ** ONE PIECE ADJACENT **
      0001            1       Horizontal Lane
      0010            2       Vertical Lane
      0100            4       Vertical Lane
      1000            8       Horizontal Lane

          ** TWO PIECES ADJACENT **
      0110            6       Vertical Lane
      1001            9       Horizontal Lane

      1100            12      upLeft Corner
      0101            5       upRight Corner
      0011            3       downRight Corner
      1010            10      downLeft Corner

          ** THREE PIECES ADJACENT **
      0111            7       rightT
      1011            11      downT
      1110            14      leftT
      1101            13      upT

          ** FOUR PIECES ADJACENT **
      1111            15      Intersection

*/

void _setTilesSectionData(int xCoord, int yCoord, int tileDataType) {
/*       |3|
      |4| X |1|
         |2|
*/
  int emptyCode = TILE_SECTION_DEFAULT;
  // Start with 0:
  int type = 0;

  // USE BIT MASKING FOR ASSIGNING NEIGHBORS
  // above:
  if ( (yCoord > 0) &&
    (_getTileData(xCoord, yCoord - 1, tileDataType) != emptyCode)) { // if anything but 0:
    type |= 0b0100;
  }

  // right:
  if ( (xCoord < MAP_DIMENSION) &&
    (_getTileData(xCoord + 1, yCoord, tileDataType) != emptyCode)) { // if anything but 0:
    type |= 0b0001;
  }

  // below:
  if ( (yCoord < MAP_DIMENSION) &&
    (_getTileData(xCoord, yCoord + 1, tileDataType) != emptyCode)) { // if anything but 0:
    type |= 0b0010;
  }

  // left:
  if ( (xCoord > 0) &&
    (_getTileData(xCoord - 1, yCoord, tileDataType) != emptyCode)) { // if anything but 0:
    type |= 0b1000;
  }

  // store information in tile:
  tile* curTile = map(xCoord, yCoord);
  if (tileDataType == TDT_ROADTYPE)
    curTile->roadType = type;
  else if (tileDataType == TDT_PLINETYPE)
    curTile->pLineType = type;
}

// The TYPE of POWERLINE or ROAD tile to draw!
int _getTileSectionType(tile* tileToGet, int type) {

  int data;
  if (type == TDT_ROADTYPE)
    data = tileToGet->roadType;
  else data = tileToGet->pLineType;

  switch (data) {
    case 0: { return TS_HOR; break; }
    case 1: { return TS_HOR; break; }
    case 2: { return TS_VER; break; }
    case 3: { return TS_DRCOR; break; }
    case 4: { return TS_VER; break; }
    case 5: { return TS_URCOR; break; }
    case 6: { return TS_VER; break; }
    case 7: { return TS_RT; break; }
    case 8: { return TS_HOR; break; }
    case 9: { return TS_HOR; break; }
    case 10: { return TS_DLCOR; break; }
    case 11: { return TS_DT; break; }
    case 12: { return TS_ULCOR; break; }
    case 13: { return TS_UT; break; }
    case 14: { return TS_LT; break; }
    case 15: { return TS_INT; break; }
    default: { return TS_ERR; }
  } // end switch

  return TS_ERR;
}

int _getTileSectionData(tile* tileToGet, int type) {
  if (type == TDT_ROADTYPE)
    return tileToGet->roadType;

  else if (type == TDT_PLINETYPE)
    return tileToGet->pLineType;

  else return -5; // error code
}

void _updateNeighborSectionTypes(int xCoord, int yCoord, int tileDataType) {

  tile* curTile;
  int emptyCode = TILE_SECTION_DEFAULT;

  // set tile above:
  if (yCoord > 0) {
    curTile = map(xCoord, yCoord - 1);
    if (_getTileSectionData(curTile, tileDataType) != emptyCode)
      _setTilesSectionData(xCoord, yCoord - 1, tileDataType);
  }

  // set right:
  if (xCoord < (MAP_DIMENSION - 1)) {
    curTile = map(xCoord + 1, yCoord);
    if (_getTileSectionData(curTile, tileDataType) != emptyCode)
      _setTilesSectionData(xCoord + 1, yCoord, tileDataType);
  }

  // set below:
  if (yCoord < (MAP_DIMENSION + 1)) {
    curTile = map(xCoord, yCoord + 1);
    if (_getTileSectionData(curTile, tileDataType) != emptyCode)
      _setTilesSectionData(xCoord, yCoord + 1, tileDataType);
  }

  // set left:
  if (xCoord > 0) {
    curTile = map(xCoord - 1, yCoord);
    if (_getTileSectionData(curTile, tileDataType) != emptyCode)
      _setTilesSectionData(xCoord - 1, yCoord, tileDataType);
  }

}

void _setBuildingTileData(int tileDataType) {


  // Each Building in V_buildings:
  int bType;
  int amount;
  int radius;
  int bX;
  int bY;
  int dim;
  for (auto it : v_buildings) {
    bType = it->type;
    bX = it->xOrigin;
    bY = it->yOrigin;
    dim = it->buildingDimension;

    if (tileDataType == TDT_LANDVALUE)
      amount = _getBuildingLandValues(bType);
    else if (tileDataType == TDT_FIREDANGER)
      amount = _getBuildingFireDangers(bType);
    else
      amount = 0;

    radius = amount;
    if (radius > 12)
      radius = 12;
    else if (radius <= 0)
      radius = 1;

    // for each tile in building:
    int R;
    int C;
    for (R = 0; R < dim; R++) {
      for (C = 0; C < dim; C++) {
        _addDataCircle(bX + C, bY + R, radius, tileDataType, amount);
      }
    }
  } // end iterate all buildings
}















// Building Functions------------
building* _getBuildingWithCoord(int x, int y) {
  tile* curTile = map(x, y);
  return curTile->buildingOnTop;
}

std::string _getBuildingTypeName(int BT) {
  std::string returnString;
  switch (BT) {
    case BT_TREE: { returnString += "Forest"; break; }
    case BT_ROAD: { returnString += "Road"; break; }
    case BT_PLINE: { returnString += "Power Line"; break; }
    case BT_RZONE: { returnString += "Residential Zone"; break; }
    case BT_CZONE: { returnString += "Commercial Zone"; break; }
    case BT_IZONE: { returnString += "Industrial Zone"; break; }
    case BT_POLICE: { returnString += "Police Station"; break; }
    case BT_FIRE: { returnString += "Fire Station"; break; }
    case BT_SCHOOL: { returnString += "School"; break; }
    case BT_HOSPITAL: { returnString += "Hospital"; break; }
    case BT_COAL: { returnString += "Coal Power Plant"; break; }
    case BT_NUCLEAR: { returnString += "Nuclear Power Plant"; break; }
    case BT_WATERTOWER: { returnString += "Water Tower"; break; }
    case BT_ARCADE: { returnString += "Arcade"; break; }
    case BT_AIRPORT: { returnString += "Airport"; break; }
    case BT_POWERROAD: { returnString += "Powered Road"; break; }
    default: { returnString += "typeError"; break; }
  }
  return returnString;
}
int _getBuildingSize(building* curBuilding) { return (curBuilding->buildingDimension); }
int _getBuildingCurPower(building* curBuilding) { return curBuilding->currentPower; }
int _getBuildingRequiredPower(building* curBuilding) { return curBuilding->requiredPower; }
int _getBuildingPollution(building* curBuilding) { return curBuilding->pollution; }
int _getBuildingValueBoost(building* curBuilding) { return curBuilding->landValueBoost; }

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

    case BT_POWERROAD: {
      return 1;
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

  case BT_ROAD: {
    return 3;
    break;
  }

  case BT_PLINE: {
    return 1;
    break;
  }

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

    case BT_POWERROAD: {
      return 3;
      break;
    }

    default: {
      return -1; // error code
      break;
    }
  } // end switch
  return -1; // error code

}

int _getBuildingLandValues(int bType) {

  // use a switch and enum to return width:
  switch (bType) {

  case BT_ROAD: {
    return 1;
    break;
  }

  case BT_PLINE: {
    return 0;
    break;
  }

    case BT_POLICE: {
      return 3;
      break;
      }

    case BT_FIRE: {
      return 2;
      break;
      }

    case BT_SCHOOL: {
      return 7;
      break;
      }

    case BT_HOSPITAL: {
      return 5;
      break;
      }

    case BT_COAL: {
      return -3;
      break;
      }

    case BT_NUCLEAR: {
      return -4;
      break;
      }

    case BT_WATERTOWER: {
      return -2;
      break;
      }

    case BT_ARCADE: {
      return 8;
      break;
      }

    case BT_AIRPORT: {
      return -5;
      break;
      }

    case BT_POWERROAD: {
      return 1;
      break;
    }

    default: {
      return 0; // error code
      break;
    }
  } // end switch

  return 0; // error code
}

int _getBuildingFireDangers(int bType) {

  // use a switch and enum to return width:
  switch (bType) {

  case BT_ROAD: {
    return 0;
    break;
  }

  case BT_PLINE: {
    return 1;
    break;
  }

    case BT_POLICE: {
      return 3;
      break;
      }

    case BT_FIRE: {
      return -20;
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
      return 7;
      break;
      }

    case BT_NUCLEAR: {
      return 5;
      break;
      }

    case BT_WATERTOWER: {
      return -4;
      break;
      }

    case BT_ARCADE: {
      return 5;
      break;
      }

    case BT_AIRPORT: {
      return 7;
      break;
      }

    case BT_POWERROAD: {
      return 1;
      break;
    }

    default: {
      return 0; // error code
      break;
    }
  } // end switch

  return 0; // error code
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
      return 1;
      break;
      }

    case BT_RZONE: {
      return -2; // special code
      break;
      }

    case BT_CZONE: {
      return -2; // special code
      break;
      }

    case BT_IZONE: {
      return -2; // special code
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

    case BT_POWERROAD: {
      return 1;
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

// CREATE A NEW BUILDING
building* _newBuilding(int type, int x, int y) {

  building* newBuilding = new building;

  // attribute defaults:
  newBuilding->type = type;
  newBuilding->xOrigin = x;
  newBuilding->yOrigin = y;
  newBuilding->buildingDimension = _getBuildingDimension(type);
  newBuilding->currentPower = 0;
  int reqPower = _getBuildingPowerRequirements(type);
  if (reqPower == -2)
    reqPower = ZONE_START_REQUIRED_POWER; // three for initial zones:
  newBuilding->requiredPower = reqPower;
  newBuilding->pollution = _getBuildingPollution(type);
  newBuilding->landValueBoost = 0;

  // get size in tiles:
  int dim = _getBuildingDimension(type);

  // set tiles associated with building
  _setBuildingTiles(newBuilding, x, y, dim);

  // Get all of the pointers to buildings around this building:
  _setBuildingNeighbors(newBuilding);

  // set correct type for road or power line:
  if (type == BT_ROAD || type == BT_POWERROAD) {
    _setTilesSectionData(x, y, TDT_ROADTYPE);
    _updateNeighborSectionTypes(x, y, TDT_ROADTYPE);
  }

  if (type == BT_PLINE || type == BT_POWERROAD) {
    _setTilesSectionData(x, y, TDT_PLINETYPE);
    _updateNeighborSectionTypes(x, y, TDT_PLINETYPE);
  }

  // For buildings, update powerline data:
  // Note: fixes when you place ONE powerline between two buildings,
  // previously, the wrong powerline would be drawn
  if ((type != BT_ROAD) && (type != BT_PLINE) && type != BT_POWERROAD) {
    int dimensions = newBuilding->buildingDimension;
    int width;
    int height;
    for (width = 0; width < dimensions; width++) {
      for (height = 0; height < dimensions; height++) {
        _setTilesSectionData(x + width, y + height, TDT_PLINETYPE);
        _updateNeighborSectionTypes(x + width, y + height, TDT_PLINETYPE);
      }
    }
  }


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

      else if (containedTile->tileType == TT_ZC ||
        containedTile->tileType == TT_ZI ||
        containedTile->tileType == TT_ZR)
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


  std::string buildingInfo = "";
  std::string buffer = "";
  char dataDivider = ',';
  char elementDivider = ';';

  std::string data = "";

  tile* curTile;
  for (auto it : v_buildings) {

    // TODO: Rework the game maker parsing input to being more
    // like the new road one. Use a special character just before
    // the data needed:

    // add x to string:
    buildingInfo += 'X';
    buildingInfo += std::to_string(it->xOrigin);

    // add y to string:
    buildingInfo += 'Y';
    buildingInfo += std::to_string(it->yOrigin);

    // add electricity info to string:
    buildingInfo += 'E';
    if (it->type == BT_PLINE)
      buildingInfo += '*'; // char representing power
    else if (it->type == BT_ROAD)
      buildingInfo += '*';
    else if (it->type == BT_POWERROAD)
      buildingInfo += '*';
    else if (it->currentPower >= (it->requiredPower*SATISFIED_POWER))
      buildingInfo += '*';
    else
      buildingInfo += '-'; // char representing needs power

    // add pLine info:
    buildingInfo += 'P';
    if (it->type == BT_PLINE || it->type == BT_POWERROAD) {
      curTile = map(it->xOrigin, it->yOrigin);
      int type = _getTileSectionType(curTile, TDT_PLINETYPE);
      buildingInfo += std::to_string(type);
    }
    else {
      buildingInfo += std::to_string(-1); // not PL code
    }

    // add type to string:
    buildingInfo += 'T';
    buildingInfo += std::to_string(it->type);

    // end of data:
    buildingInfo += elementDivider;
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

void _removeMyselfFromNeighbors(building* buildingID) {

  // Update all neighbors to remove me from their neighbor list:
  for (auto it : buildingID->neighbors) {
    it->neighbors.erase(std::remove(
      it->neighbors.begin(), it->neighbors.end(), buildingID), it->neighbors.end());
  }
}







// Roads:
std::string _roadsToString() {

  char dataSeperator = ',';
  char elementSeperator = ';';
  std::string returnString = "";
  tile* curTile;

  for (auto it : v_roads) {

    // X coord:
    returnString += 'X';
    returnString += std::to_string(it->xOrigin);

    // y coord:
    returnString += 'Y';
    returnString += std::to_string(it->yOrigin);

    // road section type:
    returnString += 'T';
    curTile = map(it->xOrigin, it->yOrigin);
    int type = _getTileSectionType(curTile, TDT_ROADTYPE);
    returnString += std::to_string(type);
    returnString += elementSeperator;
  }

  return returnString;
}

int _getRoadsVectorSize() { return v_roads.size(); }







// Zone functions:

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
    newZone->relatedZoneBuilding = NULL;
    break; }

  case Z_COM: {
    newZone->xOrigin = xCoord;
    newZone->yOrigin = yCoord;
    newZone->zoneType = Z_COM;
    newZone->totalPopCap = CL1;
    newZone->totalPopCur = 0;
    newZone->totalPollution = 0;
    _initZoneBuildings(newZone);
    newZone->relatedZoneBuilding = NULL;
    break; }

  case Z_IND: {
    newZone->xOrigin = xCoord;
    newZone->yOrigin = yCoord;
    newZone->zoneType = Z_IND;
    newZone->totalPopCap = IL1;
    newZone->totalPopCur = 0;
    newZone->totalPollution = 0;
    _initZoneBuildings(newZone);
    newZone->relatedZoneBuilding = NULL;
    break; }

  default: {
    newZone->xOrigin = xCoord;
    newZone->yOrigin = yCoord;
    newZone->zoneType = -1; // error type
    newZone->totalPopCap = 0;
    newZone->totalPopCur = 0;
    newZone->totalPollution = 0;
    _initZoneBuildings(newZone);
    newZone->relatedZoneBuilding = NULL;

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

// String: OLD
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

// NEW VERSION:
std::string _zonesToString(int zoneType) {


  // NEW VERSION NOTES:
  // We no longer care about the small zone 1X1 buildings. Now we
  // only care about the 3X3 building

  // FINISHED STRING WILL HAVE THE FOLLOWING SYNTAX:
  // xCoord,yCoord,ZoneType,level,typeVar.etc...

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


  while (iter != endZoneList) {

    int CURxCordinate = (*iter)->xOrigin;
    int CURyCordinate = (*iter)->yOrigin;
    int CURZoneType = (*iter)->zoneType;
    int CURlevel = (*iter)->zoneLevel;
    int CURtypeVar = (*iter)->typeVariation;

    // ADD TO STRING:
    std::string data = "";
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

    zoneBuildingInfo += data;

    // add divider between buildings:
    zoneBuildingInfo += elementDivider;

    iter++;
  } // end while iter

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
      int highestChance = 6;
      if (chance <= highestChance) {

        // access zoneBuildings in zone:
        for (auto it : (*iter)->zoneBuildings) {
          int chanceB = _getIntRange(1, 10);
          int highestChanceB = 2;
          if (chanceB <= highestChanceB) {

            // HERE IS THE ALGORITHM FOR POPULATION GROWTH:
            int growth = _calcPopGrowth(it);
            it->popCur += growth;

            // Bound on zero:
            if (it->popCur < 0)
              it->popCur = 0;

            // update level:
            _updateZoneBuildingLevel(it);

          } // end if chance (buildings within zone)
        } // end auto : it

        // update required power AFTER processing the zone:
        zone* curZone = (*iter);
        int newReqPower = _zoneGetTotalRequiredPower(curZone);
        curZone->relatedZoneBuilding->requiredPower = newReqPower;

      iter++;
      } // end if chance (zones)
    } // end while
  } // end if ready

  // Finally, update the population:
  updatePopulationZones();
}

int _calcPopGrowth(zoneBuilding* curZ) {

  int level = curZ->level + 1; // make at least 1
  int landValue = curZ->tileUnder->landValue;
  bool isPowered = false; // false until proven true

  double popGrowth = 0;

  // check for power, (lack of power haults/negates growth):
  building* curZone = curZ->parentZone->relatedZoneBuilding;
  if (curZone != NULL) {
    if (curZone->requiredPower > 0) {
      // just make sure the whole zone is powered:
      if (curZone->currentPower >= (curZone->requiredPower*SATISFIED_POWER))
        isPowered = true;
    }
  }

  if (isPowered) {
    // pop growth based on level, some randomness
    popGrowth = 8*(level) + ((level)*(_getIntRange(-(level + 2), level + 2)));

    // Some land value impact:
    int lv = 100 - landValue;
    double lvImpact = (double)lv / 50.0;
    if (lvImpact <= 0)
      lvImpact = 1;
    popGrowth = popGrowth / lvImpact;

    // punish for low land value, reward for high:
    double lvLuck = (landValue - 50) / 20;
    double luck = _getIntRange(lvLuck - 1, lvLuck + 1);
    if (luck == 0) // don't multiply by zero
      luck = 1;
    popGrowth = popGrowth*luck;

    // Population can get crazy with high land values, so cap it:
    //double popGrowthMax = (level + 1)*((level + 2) / 2) * 30;
    double popGrowthMax = (int)(_getZoneBuildingPopMin(curZ->zoneType, level)/10);
    if (popGrowth > popGrowthMax)
      popGrowth = popGrowthMax;
  }

  else {
    popGrowth = (double)_getIntRange(-((level + 1) * 5), level*2);
  }

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

int _zoneGetTotalRequiredPower(zone* zoneID) {

  int sumPowerConsumption = 2;
  for (int i = 0; i < 9; i++) {
    sumPowerConsumption += _zoneBuildingGetRequiredPower(zoneID->zoneBuildings[i]);
  }

  return sumPowerConsumption;
}

int _zoneBuildingGetRequiredPower(zoneBuilding* curZB) {
    int level = curZB->level;
    return (level + 1) * 1; // TODO: change if needed
}

// Return the amount of revenue to be added for a certain zone type:
int _getTaxRevenue(int zoneType) {


  int revenue = 0;
  int taxRate = 0;
  int zoneRate = 0;

  int ready = false;
  std::list<zone*>::iterator iter;
  std::list<zone*>::iterator endZoneList;
  // first iterate through all zones in given data type:
  if (zoneType == Z_RES) {
    iter = Rzones.begin();
    endZoneList = Rzones.end();
    taxRate = curGameData.taxRes;
    zoneRate = REV_RES;
    ready = true;
  }
  else if (zoneType == Z_COM) {
    iter = Czones.begin();
    endZoneList = Czones.end();
    taxRate = curGameData.taxCom;
    zoneRate = REV_COM;
    ready = true;
  }
  else if (zoneType == Z_IND) {
    iter = Izones.begin();
    endZoneList = Izones.end();
    taxRate = curGameData.taxInd;
    zoneRate = REV_IND;
    ready = true;
  }


  if (ready) {

    // Each ZONE of given type:
    while (iter != endZoneList) {

      std::vector<zoneBuilding*>::iterator bIter = (*iter)->zoneBuildings.begin();
      std::vector<zoneBuilding*>::iterator bIterEnd = (*iter)->zoneBuildings.end();

      // each zone BUILDING inside zone:
      int curPop;
      int revRate;
      for (bIter; bIter != bIterEnd; bIter++) {
        curPop = (*bIter)->popCur;
        revRate = curGameData.revenueRates[(*bIter)->level];

        // HERE is the current forumla:
        revenue += (curPop * zoneRate * revRate * taxRate);

      } // end inner for (each building in zone)
    iter++; // iterate to next zone building
    } // end while
  } // end if ready

  return revenue;
}













// POWER / ELECTRICITY Functions:

int _getRequiredPowerAllTypes(building* buildingID) {
  int powerNeeded;
  // Check for zone type (-2 code), find the required power needed:
  if (buildingID->requiredPower == -2 ) {
    // get required power from the related zone:
    if (buildingID->relatedZone != NULL)
      powerNeeded = _zoneGetTotalRequiredPower(buildingID->relatedZone) - buildingID->currentPower;
  }
  else { // NON ZONE TYPE:
    powerNeeded = (buildingID->requiredPower - buildingID->currentPower);
  }

  return powerNeeded;
}

double _getPowerUsageRatio(int capacity, int used) {

  // at least a 1 in denominator:
  if (capacity <= 0)
    capacity = 1;

  // Don't know why, but I need to store it first:
  double returnVal = (double)used / capacity;
  return returnVal;
}

int _getPowerPlantPower(int type) {

  switch (type) {
    case BT_NUCLEAR: {
      return 645;
      break; }

    case BT_COAL: {
      return 270;
      break; }

    default: {
      return -1; // error code
      break; }
    } // end switch

  return -1; // error code
}

void _sendElectricity() {

  int totalPowerAvailable = 0;
  int totalPowerUsed = 0;

  // START WITH ALL BUILDINGS LOSING THEIR CURRENT POWER:
  for (auto it : v_buildings) {
    it->currentPower = 0;
  }

  // Build an array of power plants:
  std::vector<building*> powerPlants;
  for (auto it : v_buildings) {
    if (it->type == BT_NUCLEAR ||
        it->type == BT_COAL) {
      powerPlants.push_back(it);
    }
  } // end for iteration


  /* Iterate through the power plants, surging power to
     all of the connected buildings using their 'neighbors'
     and building a fifo queue */
  std::queue<building*> processList;
  // For each power plant:
  for (auto iter : powerPlants) {

    int electricSurge = _getPowerPlantPower(iter->type);
    totalPowerAvailable += electricSurge; // used for power ratio

    // STARTING CASE: Start with the neighbors of the power plant:
    // For each neighbor in each power plant:
    for (auto it : iter->neighbors) {
      // Only pass electricity on to certain types of buildings:
      if (it->type != BT_NUCLEAR ||
        it->type != BT_COAL ||
        it->type != BT_ROAD ||
        it->type != BT_TREE) {

        // the POWER PLANTS neighbors:
        // Push neighbors to the list if they require power:
        if (_getRequiredPowerAllTypes(it) > 0)
          processList.push(it);
      } // end if certain building type
    } // end for each neighbor


    /* NEIGHBORS CASE: Process each of the items in the queue, adding
       new items if more neighbors also need power */
    building* curItem;
    int powerNeeded;
    while (!processList.empty() && electricSurge > 0) {
      curItem = processList.front();
      // remove item from list:
      processList.pop();

      // How much power will we need?
      powerNeeded = _getRequiredPowerAllTypes(curItem);

      // only use what's needed:
      if (electricSurge >= powerNeeded) {
        curItem->currentPower += powerNeeded;
        electricSurge -= powerNeeded;
      } else { // OR use up the rest of the juice:
        curItem->currentPower += electricSurge;
        electricSurge = 0;
      }
      totalPowerUsed += curItem->currentPower;

      // Get the current item's neighbors:
      for (auto neighbor : curItem->neighbors) {
        // Only pass electricity on to certain types of buildings:
        if (neighbor->type != BT_NUCLEAR ||
          neighbor->type != BT_COAL ||
          neighbor->type != BT_ROAD ||
          neighbor->type != BT_TREE) {

          // Push neighbors to the list if they require power:
          if (_getRequiredPowerAllTypes(neighbor) > 0)
            processList.push(neighbor);
        } // end if certain building type
      } // end for each neighbor
    } // END PROCESS LIST
  } // end for each power plant


  // Update the game data for data used/capacity:

  curGameData.totalPowerAvailable = totalPowerAvailable;
  curGameData.totalPowerUsed = totalPowerUsed;
}

void _consumeElectricity() {

  const double USAGE_RATE = 0.1;

  for (auto it : v_buildings) {
    int consumptionAmount = _getRequiredPowerAllTypes(it)*USAGE_RATE;

    // at least take 1:
    if (consumptionAmount < 1)
      consumptionAmount = 1;

    // Consume the power here, with floor of zero:
    it->currentPower -= consumptionAmount;
    if (it->currentPower < 0)
      it->currentPower = 0;

    } // END FOR ITERATION for all buildings
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
      iter->roadType = TILE_SECTION_DEFAULT;
      iter->pLineType = TILE_SECTION_DEFAULT;

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

double getTaxRate(double type) {

  int taxType = (int)type;
  double returnVal = -1;

  switch (taxType) {
    case TAX_RES: {
      returnVal = curGameData.taxRes;
      break;
    }

    case TAX_COM: {
      returnVal = curGameData.taxCom;
      break;
    }

    case TAX_IND: {
      returnVal = curGameData.taxInd;
      break;
    }
    default: {
      returnVal = -2;
      break;
    }
  }

  return returnVal;
}

double setTaxRate(double type, double val) {
  int taxType = (int)type;
  double setVal = (int)val;

  if (setVal < 0)
    setVal = 0;
  else if (setVal > 99)
    setVal = 99;

  switch (taxType) {
    case TAX_RES: {
      curGameData.taxRes = setVal;
      break;
    }

    case TAX_COM: {
      curGameData.taxCom = setVal;
      break;
    }

    case TAX_IND: {
      curGameData.taxInd = setVal;
      break;
    }
    default: {
      return -1; // error
      break;
    }
  }

  return 0;
}

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

double addFunds(double amount) {
  int amountInt = (int)amount;
  curGameData.money += amountInt;
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
  }

  return 0;
}

double growSeeds(double type, double amount) {

  int typeInt = (int)type;
  int amountInt = (int)amount;

  for (int i = 0; i < amountInt; i++) {
    _growSeeds(typeInt);

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

  _addTileDataRadius(TT_WATER, typeInt, radiusInt, amountInt);
  return 0;
}

double addTreeTileValue(double dataType, double radius, double amount) {
  int typeInt = (int)dataType;
  int radiusInt = (int)radius;
  int amountInt = (int)amount;

  _addTileDataRadius(TT_TREE, typeInt, radiusInt, amountInt);
  return 0;
}

// pollution causes land value to decrease:
double subtractLandValuePollution() {
  _subtractLandValuePollution();
  return 0;
}

// for roads and powerlines:
double getTileSectionType(double x, double y, int tileDataType) {
  // convert to int first
  int xCoord = (int)x;
  int yCoord = (int)y;

  tile* tileToGet = map(xCoord, yCoord);

  return (_getTileSectionType(tileToGet, tileDataType));
}

// For Land Value and Fire Danger caused by buildings:
double setBuildingTileData(double tileDataType) {
  int dataType = (int)tileDataType;
  _setBuildingTileData(tileDataType);
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

// NEW UDPDATED version of 'zoneBuildingsToString
char* zonesToString(double dataType) {
  int dataTypeInt = (int)dataType;
  std::string getString = _zonesToString(dataTypeInt);

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

double collectTax(double zoneType) {
  int type = (int)zoneType;

  int amount = _getTaxRevenue(type);
  addFunds(amount);

  return amount;
}





// BUILDING FUNCTIONS ------------------

char* getBuildingInfo(double infoType, double x, double y) {

  std::string returnString = "";
  int type = (int)infoType;
  int xCoord = (int)x;
  int yCoord = (int)y;

  building* curBuilding = _getBuildingWithCoord(xCoord, yCoord);
  if (curBuilding != NULL) {

    switch (type) {
      case BDT_TYPE: {
        returnString += _getBuildingTypeName(curBuilding->type);
        break;
      }

      case BDT_SIZE: {
        returnString += std::to_string(curBuilding->buildingDimension);
        break;
      }

      case BDT_CURPOWER: {
        returnString += std::to_string(curBuilding->currentPower);
        break;
      }

      case BDT_REQPOWER: {
        returnString += std::to_string(curBuilding->requiredPower);
        break;
      }

      case BDT_POLLUTION: {
        returnString += std::to_string(curBuilding->pollution);
        break;
      }

      case BDT_LANDVALUEBOOST: {
        returnString += std::to_string(curBuilding->landValueBoost);
        break;
      }

      default: {
        returnString += "noTypeSpecifiedError";
        break;
      }
    } // end switch
  }
  else {
    returnString += "";
  }

  // convert to cstring and return to game maker:
  char* cstr = new char[returnString.length() + 1];

  // push string to string cleanup vector?

  std::strcpy(cstr, returnString.c_str());
  return cstr;
}

double addBuilding(double type, double x, double y) {

  // convert doubles to ints:
  int typeInt = (int)type;
  int xInt = (int)x;
  int yInt = (int)y;
  int price = (int)getBuildingPrice(typeInt);
  int putInBuildingVector = true; // true till proven false

  // check if position is okay to build:
  int canBuild = _checkPlacement(typeInt, xInt, yInt);

  // also check if we have enough money:
  int hasMoney = _checkMoney(price);

  // logic for building powered roads (roads with a power line)
  if (type == BT_PLINE) {
    tile* curTile = map(xInt, yInt);

    if (curTile->buildingOnTop != NULL &&
        curTile->buildingOnTop->type == BT_ROAD &&
        hasMoney) {
      canBuild = false; // don't follow normal build procedures

      // change type to powered road building:
      removeBuilding(x, y);
      curTile->tileType = TT_GRASS;

      // reminder: road is still in road vector
      building* newBuilding = _newBuilding(BT_POWERROAD, xInt, yInt);
      newBuilding->relatedZone = NULL;
      v_buildings.push_back(newBuilding);
      deductFunds(price);
      return 1;
    } // end if

  } // end if PLINE

  if (canBuild && hasMoney) {

    // NO MATTER WHAT TYPE, make a building in it's location:
    // create a new building:
    building* newBuilding = _newBuilding(typeInt, xInt, yInt);

    // Build Road:
    if (type == BT_ROAD) {
      putInBuildingVector = false;
      v_roads.push_back(newBuilding);
    }

    // Build ZONE:
    if (type == BT_RZONE || type == BT_CZONE || type == BT_IZONE) {

      int zoneType = _BtypeToZtype(type); // convert enum
      zone* newZone = _newZone(xInt, yInt, zoneType);

      // ADD ZONE TO BUILDING THAT WAS ALSO CREATED:
      newBuilding->relatedZone = newZone;

      // connect the zone to the building also:
      newZone->relatedZoneBuilding = newBuilding;

      if (type == BT_RZONE) {
        Rzones.push_front(newZone);
      }

      else if (type == BT_CZONE) {
        Czones.push_front(newZone);
      }

      else if (type == BT_IZONE) {
        Izones.push_front(newZone);
      }

      else {
        _clearOneZone(newZone); // invalid type
      }
    } // end if zone type

    // WAS NOT ZONE TYPE:
    else {
      newBuilding->relatedZone = NULL;
    }


    // add building to vector
      // (if not, we already put it in something else
    if (putInBuildingVector)
      v_buildings.push_back(newBuilding);

    // subtract money:
    deductFunds(price);

    return 1;
  } // end (if canBuild)

  else
    return 0;

  return 0;
}

// TODO TODO: buildings of type BT_POWERROAD need to be removed from the
// buildings vector BUT ALSO the road vector!
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
  _removeMyselfFromNeighbors(buildingToDelete);

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

    case BT_POWERROAD: {
      return BP_PLINE;
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



// ROADS:
char* roadsToString() {
  std::string getString = _roadsToString();

  char* cstr = new char[getString.length() + 1];
  std::strcpy(cstr, getString.c_str());

  return cstr;
}

double getRoadsVectorSize() {
  return _getRoadsVectorSize();
}




// UTILITY FUNCTIONS -------------------
double getRandomRange(double min, double max) {
  int minInt = (int)min;
  int maxInt = (int)max;

  return _getIntRange(minInt, maxInt);
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




// POWER & ELECTRICITY FUNCTIONS ----------------
double sendElectricity() {
  _sendElectricity();
  return 0;
}

double consumeElectricityAll() {
  _consumeElectricity();
  return 0;
}

double getPowerUsageRatio() {
  double returnVal = _getPowerUsageRatio(curGameData.totalPowerAvailable, curGameData.totalPowerUsed);
  return returnVal;
}





// TESTING/DEBUGGING FUNCTIONS ------------------------------------

/* Prints the TYPES OF TILES of the map, including trees,
   buildings, zones, etc... */
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

/* Test the output of tile type strings to the DLL importer */
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

/* Test the details of buildings in the v_buildings global vector */
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

/* Tests the global game data, such as seasons, money, etc..*/
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

/* Tests printing out the game data to a string */
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

/* Test printing the zone string information */
void _testPrintZoneString(int zoneType) {

  _zoneBuildingToString(zoneType);

}

/* See the impact of the zone growth over time */
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

/* Test to see if the neighbors are attached/detached correctly */
double _testBuildingNeighbors() {

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

  return 0;
}

/* Test to see if sending power from power plants to connected
neighbors works */
double _testPowerSurge() {

  /*
  // Big square:
  addBuilding(BT_POLICE, 27, 27);
  addBuilding(BT_POLICE, 27, 30);
  addBuilding(BT_POLICE, 27, 33);
  addBuilding(BT_POLICE, 30, 27);
  addBuilding(BT_POLICE, 30, 30);
  addBuilding(BT_POLICE, 30, 33);
  addBuilding(BT_POLICE, 33, 27);
  addBuilding(BT_POLICE, 33, 30);
  addBuilding(BT_POLICE, 33, 33);

  addBuilding(BT_POLICE, 36, 33);
  addBuilding(BT_POLICE, 39, 33);
  addBuilding(BT_NUCLEAR, 42, 33);
  */


  // test zone transfer of electricity:
  addBuilding(BT_COAL, 1, 1);
  addBuilding(BT_POLICE, 5, 2);
  addBuilding(BT_POLICE, 8, 2);
  addBuilding(BT_RZONE, 11, 2);
  addBuilding(BT_RZONE, 14, 2);
  addBuilding(BT_POLICE, 17, 2);
  addBuilding(BT_POLICE, 20, 2);
  for (int j = 0; j < 10; j++) {
    addBuilding(BT_PLINE, 20 + j, 3);
  }
  addBuilding(BT_POLICE, 30, 2);

  for (int g = 0; g < 10; g++) {
    addBuilding(BT_HOSPITAL, 30, 5 + (4 * g));
  }

  _printMapTypes();
  std::cout << std::endl;
  std::cout << std::endl;

  //_testBuildingNeighbors();
  //std::cout << std::endl;
  //std::cout << std::endl;

  // show power of all buildings:
  std::cout << "Buildings and their power:" << std::endl;
  for (auto it : v_buildings) {
    std::cout << "\t" << "x=" << it->xOrigin << ", y=" << it->yOrigin;
    std::cout << ", required: " << it->requiredPower;
    std::cout << ", current: " << it->currentPower;
    std::cout << std::endl;
  }

  // surge:
  std::cout << "-----------------------------";
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Sending surge from all power plants now...";
  _sendElectricity();
  std::cout << "done" << std::endl;
  std::cout << std::endl;

std::cout << "Buildings and their power:" << std::endl;
  for (auto it : v_buildings) {
    std::cout << "\t" << "x=" << it->xOrigin << ", y=" << it->yOrigin;
    std::cout << ", required: " << it->requiredPower;
    std::cout << ", current: " << it->currentPower;
    std::cout << std::endl;
  }

  // CONSUME power:
  std::cout << std::endl;
  int times = 3;
  std::cout << "consuming power " << times << " times...";
  for (int p = 0; p < times; p++)
    _consumeElectricity();

  std::cout << "done" << std::endl;
  std::cout << std::endl;

std::cout << "Buildings and their power:" << std::endl;
  for (auto it : v_buildings) {
    std::cout << "\t" << "x=" << it->xOrigin << ", y=" << it->yOrigin;
    std::cout << ", required: " << it->requiredPower;
    std::cout << ", current: " << it->currentPower;
    std::cout << std::endl;
  }


  // grow zones:
  std::cout << "growing residential zones!" << std::endl;
  std::cout << std::endl;
  for (int j = 0; j < 10; j++) {
    _growZones(Z_RES);
  }
  std::cout << "sending electricity again." << std::endl;
  _sendElectricity();

std::cout << "Buildings and their power:" << std::endl;
  for (auto it : v_buildings) {
    std::cout << "\t" << "x=" << it->xOrigin << ", y=" << it->yOrigin;
    std::cout << ", required: " << it->requiredPower;
    std::cout << ", current: " << it->currentPower;
    std::cout << std::endl;
  }





  return 0;
}

std::string _testDisplayRoadType(int type) {

  switch (type) {

  case TS_ERR: { return "error"; break; }

  case TS_HOR: { return "horizontal"; break; }
  case TS_VER: { return "vertical"; break; }

  case TS_ULCOR: { return "Up-Left Corner"; break; }
  case TS_URCOR: { return "Up-Right Corner"; break; }
  case TS_DLCOR: { return "Down-Left Corner"; break; }
  case TS_DRCOR: { return "Down-Right Corner"; break; }

  case TS_RT: { return "Right T"; break; }
  case TS_DT: { return "Down T"; break; }
  case TS_LT: { return "Left T"; break; }
  case TS_UT: { return "Up T"; break; }

  case TS_INT: { return "Intersection"; break; }

  default: {
    return "default";
    break;
  }

  }

  return "error";
}

double _testRoadTypes() {

  std::cout << std::endl;

  // add roads:
  addBuilding(BT_ROAD, 5, 5);
  addBuilding(BT_ROAD, 6, 5);
  addBuilding(BT_ROAD, 6, 4);

  tile* curTile;
  for (int j = 2; j < 7; j++) {
    for (int p = 2; p < 7; p++) {
      curTile = map(j, p);
      std::cout << "x=" << curTile->x;
      std::cout << ", y=" << curTile->y;
      std::cout << "\tCode: ";
      std::cout << curTile->roadType;
      std::cout << ",\t" << _testDisplayRoadType(_getTileSectionType(curTile, TDT_ROADTYPE));
      std::cout << std::endl;
    }
  }

  /*
  // Check it's code:
  tile* curTile;
  for (auto it : v_roads) {
    std::cout << "x=" << it->xOrigin;
    std::cout << ", y=" << it->yOrigin;
    std::cout << "\tCode: ";

    curTile = map(it->xOrigin, it->yOrigin);
    std::cout << curTile->roadType;

    std::cout << std::endl;
  }

    std::cout << std::endl;
    std::cout << std::endl;
    */

  return 0;
}

double _testRoadPrintString() {

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "empty, " << std::endl;
  std::cout << "string: ";
  std::cout << roadsToString();
  std::cout << std::endl;
  std::cout << std::endl;

  addBuilding(BT_ROAD, 4, 5);
  std::cout << "one road, " << std::endl;
  std::cout << "string: ";
  std::cout << roadsToString();
  std::cout << std::endl;
  std::cout << std::endl;

  addBuilding(BT_ROAD, 5, 5);
  addBuilding(BT_ROAD, 5, 6);
  std::cout << "three roads, " << std::endl;
  std::cout << "string: ";
  std::cout << roadsToString();
  std::cout << std::endl;
  std::cout << std::endl;



  return 0;
}

double _testPLINETypes() {

  std::cout << std::endl;

  // add power lines:
  addBuilding(BT_PLINE, 4, 5);
  addBuilding(BT_PLINE, 5, 5);
  addBuilding(BT_PLINE, 6, 5);

  addBuilding(BT_PLINE, 5, 4);
  addBuilding(BT_PLINE, 5, 6);

  tile* curTile;
  for (int j = 2; j < 7; j++) {
    for (int p = 2; p < 7; p++) {
      curTile = map(j, p);
      std::cout << "x=" << curTile->x;
      std::cout << ", y=" << curTile->y;
      std::cout << "\tCode: ";
      std::cout << curTile->pLineType;
      std::cout << std::endl;
    }
  }

  return 0;
}

double _testPowerRoad() {

  std::cout << std::endl;
  std::cout << std::endl;

  // add vertical road first:
  std::cout << std::to_string(addBuilding(BT_ROAD, 5, 4));
  std::cout << std::endl;
  std::cout << std::to_string(addBuilding(BT_ROAD, 5, 5));
  std::cout << std::endl;
  std::cout << std::to_string(addBuilding(BT_ROAD, 5, 6));
  std::cout << std::endl;

  // add power lines ACROSS that road:
  std::cout << std::to_string(addBuilding(BT_PLINE, 4, 5));
  std::cout << std::endl;
  std::cout << std::to_string(addBuilding(BT_PLINE, 5, 5));
  std::cout << std::endl;
  std::cout << std::to_string(addBuilding(BT_PLINE, 6, 5));
  std::cout << std::endl;
  std::cout << std::endl;

  tile* curTile;
  for (int j = 2; j < 7; j++) {
    for (int p = 2; p < 7; p++) {
      curTile = map(j, p);
      std::cout << "x=" << curTile->x;
      std::cout << ", y=" << curTile->y;
      std::cout << "\tCode: ";
      std::cout << curTile->pLineType;
      std::cout << std::endl;
    }
  }

  return 0;

}


void _HELPER_printZoneInfo() {

  int index = 1;
  for (auto it : v_buildings) {

    std::cout << "Rzone " << index << std::endl;
    if (it->relatedZone != NULL) {
      std::cout << "\tcurPower=";
      if (it->relatedZone->relatedZoneBuilding != NULL) {
        building* curBuilding = it->relatedZone->relatedZoneBuilding;
        std::cout << curBuilding->currentPower;
        std::cout << ", requiredPower=";
        std::cout << curBuilding->requiredPower;
        std::cout << ", zRP=";
        std::cout << _zoneGetTotalRequiredPower(it->relatedZone);
      }
      else {
        std::cout << "NULL";
      }

      for (auto it2 : it->relatedZone->zoneBuildings) {
        std::cout << std::endl;
        std::cout << "\t\tzLevel=";
        std::cout << it2->level;
      }


    }

    index++;
    std::cout << std::endl;
    std::cout << std::endl;
  }

  std::cout << "---------------------------" << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

}

double _testZoneGrowthPowerless() {

  std::cout << std::endl;
  addBuilding(BT_RZONE, 5, 5);
  addBuilding(BT_RZONE, 10, 10);

  _HELPER_printZoneInfo();


  _growZones(Z_RES);

  _HELPER_printZoneInfo();

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  return 0;
}

double _testPrintZoneLevels(int zoneType) {

  int ready = false;
  std::list<zone*>::iterator iter;
  std::list<zone*>::iterator endZoneList;

  std::string typeString;

  if (zoneType == Z_RES) {
    typeString = "Rzone";
    iter = Rzones.begin();
    endZoneList = Rzones.end();
    ready = true;
  }
  else if (zoneType == Z_COM) {
    typeString = "Czone";
    iter = Czones.begin();
    endZoneList = Czones.end();
    ready = true;
  }
  else if (zoneType == Z_IND) {
    typeString = "Izone";
    iter = Izones.begin();
    endZoneList = Izones.end();
    ready = true;
  }

  else
    std::cout << "_testPrintZoneLevels: Invalid Zone Type" << std::endl;

  if (ready) {

    int counter = 0;
    // Each ZONE of given type:
    while (iter != endZoneList) {

      std::vector<zoneBuilding*>::iterator bIter = (*iter)->zoneBuildings.begin();
      std::vector<zoneBuilding*>::iterator bIterEnd = (*iter)->zoneBuildings.end();

      std::cout << "\t" << typeString << " " << counter << ": ";

      // each zone BUILDING inside zone:
      for (bIter; bIter != bIterEnd; bIter++) {

        std::cout << (*bIter)->level << " ";

      } // end inner for (each building in zone)

      std::cout << std::endl;

    iter++; // iterate to next zone building
    } // end while
  } // end if ready

  return 0;
}

double _testCollectRevenue() {

  int moneyBefore = getGameMoney();

  std::cout << "Residential tax collected: ";
  std::cout << collectTax(Z_RES) << std::endl;;
  _testPrintZoneLevels(Z_RES);
  std::cout << std::endl;

  std::cout << "Commercial tax collected: ";
  std::cout << collectTax(Z_COM) << std::endl;;
  _testPrintZoneLevels(Z_COM);
  std::cout << std::endl;

  std::cout << "Industrial tax collected: ";
  std::cout << collectTax(Z_IND) << std::endl;;
  _testPrintZoneLevels(Z_IND);
  std::cout << std::endl;

  int moneyAfter = getGameMoney();
  std::cout << "MONEY COLLECTED: " << moneyAfter - moneyBefore << std::endl;
  std::cout << std::endl;

  return 0;
}


double _deepDebugPopGrowth() {

  // Rzones NO power:
  //addBuilding(BT_RZONE, 2, 5);
  //addBuilding(BT_RZONE, 5, 5);
  //addBuilding(BT_RZONE, 8, 5);

  // Rzones WITH power:
  //addBuilding(BT_RZONE, 10, 10);
  addBuilding(BT_RZONE, 13, 10);
  addBuilding(BT_RZONE, 16, 10);
  addBuilding(BT_NUCLEAR, 19, 10);

  _printMapTypes();


  int times;
  for (times = 0; times < 20; times++) {
    sendElectricity();
    std::cout << times << ". Population: " << getPopulation() << std::endl;
    growZone(Z_RES);
  }




  return 0;
}








