#ifndef _STAGE_H
#define _STAGE_H
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <string>
#include <vector>
#include "constants.h"
#include "stageLayouts.h"

class Stage {
private:
	std::vector<std::vector<int>> layout;	// 2D array representing stage layout
	Coordinates startTile;					// Coordinates of start tile
	Coordinates endTile;					// Coordinates of end tile
	Coordinates currentTile;				// Coordinates of current tile
	int stageNo;							// Stage number

public:
	// Constructor
	Stage();

	// Destructor
	virtual ~Stage();

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

	void logLayout();

	int getTileValueAtCoordinates(Coordinates coordinates);

	int getCurrentTileValue();

	std::string getCurrentTileType();

	bool moveCurrentTile(int direction);
};

#endif
