#ifndef _STAGE_H
#define _STAGE_H
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <string>
#include <vector>
#include "constants.h"

class Stage {
private:
	std::vector<std::vector<int>> layout;	// 2D array representing stage layout
	std::vector<int> startTile;				// Coordinates of start tile
	std::vector<int> endTile;				// Coordinates of end tile
	std::vector<int> currentTile;			// Coordinates of current tile

public:
	// Constructor
	Stage();

	// Destructor
	virtual ~Stage();

	bool initialize(std::vector<std::vector<int>> layout, std::vector<int> startTile, std::vector<int> endTile);

	void logLayout();
	
	int getTileAtCoordinate(std::vector<int> coordinate);

	int getCurrentTileValue();

	std::string getCurrentTileType();

	bool setCurrentTile(std::vector<int> currentTile);

	bool moveCurrentTile(int direction);
};

#endif
