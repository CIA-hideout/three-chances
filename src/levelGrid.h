#ifndef _LEVELGRID_H
#define _LEVELGRID_H

#include <iostream>
#include <string>
#include <vector>
#include "constants.h"
#include "levelConstants.h"

class LevelGrid {
private:
	std::vector<std::vector<int>> grid;		// 2D array representing stage layout
	Coordinates startTile;					// Coordinates of start tile
	Coordinates endTile;					// Coordinates of end tile
	int stageNo;							// Stage number

public:
	LevelGrid();
	~LevelGrid();

	bool initialize(int stageNo);

	// Getters
	std::vector<std::vector<int>> getGrid() { return grid; }
	Coordinates getStartTile() { return startTile; }
	Coordinates getEndTile() { return endTile; }
	int getStageNo() { return stageNo; }

	// Setters
	void setGrid(std::vector<std::vector<int>> g) { grid = g; }
	void setStartTile(Coordinates st) { startTile = st; }
	void setEndTile(Coordinates et) { endTile = et; }
	void setStageNo(int sn) { stageNo = sn; }

	// Logging
	void logGrid();
	void logTile(Coordinates coordinates, float x, float y);
	std::string getTileType(Coordinates coordinates);

	int getTileValueAtCoordinates(Coordinates coordinates);

	Coordinates getNextTileCoordinates(Coordinates currCoord, int direction);
	int getNextTileValue(Coordinates coordinates, int direction);

	void removeBlockage() { grid = STAGE_1_LAYOUT_CLEAR; };
};

#endif
