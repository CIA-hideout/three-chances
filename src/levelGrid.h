#ifndef _LEVELGRID_H
#define _LEVELGRID_H

#include <iostream>
#include <string>
#include <vector>
#include "constants.h"
#include "levelConstants.h"

class LevelGrid {
private:
	std::vector<std::vector<int>> layout;	// 2D array representing stage layout
	Coordinates startTile;					// Coordinates of start tile
	Coordinates endTile;					// Coordinates of end tile
	Coordinates currentTile;				// Coordinates of current tile
	int stageNo;							// Stage number

public:
	// Constructor
	LevelGrid();

	// Destructor
	virtual ~LevelGrid();

	bool initialize(int stageNo);

	// Getters
	std::vector<std::vector<int>> getLayout() { return layout; }
	Coordinates getStartTile() { return startTile; }
	Coordinates getEndTile() { return endTile; }
	Coordinates getCurrentTile() { return currentTile; }
	int getStageNo() { return stageNo; }

	// Setters
	void setLayout(std::vector<std::vector<int>> l) { layout = l; }
	void setStartTile(Coordinates st) { startTile = st; }
	void setEndTile(Coordinates et) { endTile = et; }
	void setCurrentTile(Coordinates ct) { currentTile = ct; }
	void setStageNo(int sn) { stageNo = sn; }

	// Logging
	void logLayout();
	void logTile(float x, float y);

	// Getting tile value
	int getTileValueAtCoordinates(Coordinates coordinates);
	int getCurrentTileValue();
	int getNextTileValue(int direction);
	Coordinates convertXYToCoord(float x, float y);

	std::string getCurrentTileType();

	void moveCurrentTile(int direction);
};

#endif
