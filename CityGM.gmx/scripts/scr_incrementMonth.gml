// argument0 = id holding the data

DLL_incrementGameMonth();

argument0.gameYear = DLL_getGameYear();
argument0.gameMonth = DLL_getGameMonth();
argument0.gameSeason = DLL_getGameSeason();
argument0.gameTimeString = scr_setTimeString(argument0.gameSeason, argument0.gameYear);


