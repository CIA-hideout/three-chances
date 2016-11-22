#include "map.h"

//=============================================================================
// Constructor
//=============================================================================
Map::Map() {}

//=============================================================================
// Destructor
//=============================================================================
Map::~Map() {}

//=============================================================================
// Initializes the map
//=============================================================================
bool Map::initialize(std::vector<std::vector<int>> mLayout, std::vector<int> mStartTile, std::vector<int> mEndTile) {
	layout = mLayout;
	startTile = mStartTile;
	endTile = mEndTile;
	currentTile = mStartTile;

	return true;
}

//=============================================================================
// Logs entire map layout
//=============================================================================
void Map::logLayout() {
	for (int i = 0; i < layout.size(); i++) {
		for (int j = 0; j < layout[i].size(); j++) {
			std::cout << layout[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

//=============================================================================
// Returns tile at specified coordinates
//=============================================================================
int Map::getTileAtCoordinate(std::vector<int>mCoordinate) {
	// Y coordinate has to be first because of how the 2D array is structured
	return layout[mCoordinate[1]][mCoordinate[0]];
}

//=============================================================================
// Returns value of tile at current coordinates
//=============================================================================
int Map::getCurrentTileValue() {
	return layout[currentTile[1]][currentTile[0]];
}

//=============================================================================
// Returns type of tile at current coordinates
//=============================================================================
std::string Map::getCurrentTileType() {
	int value = Map::getCurrentTileValue();
	std::string tileType = "";

	switch (value) {
	case 0:
		tileType = "Border";
		break;
	case 1:
		tileType = "1st Floor Path";
		break;
	case 2:
		tileType = "2nd Floor Path";
		break;
	case 3:
		tileType = "Stairs";
		break;
	case 4:
		tileType = "Water";
		break;
	case 5:
		tileType = "Obstacle";
		break;
	case 6:
		tileType = "Blockage";
		break;
	};

	return tileType;
}

//=============================================================================
// Updates currentTile to specified coordinates
//=============================================================================
bool Map::setCurrentTile(std::vector<int> mCurrentTile) {
	currentTile = mCurrentTile; 
	return true;
}

//=============================================================================
// Shifts current tile by 1 tile in specified direction
//=============================================================================
bool Map::moveCurrentTile(int direction) {
	switch (direction) {
	case LEFT:
		currentTile = { currentTile[0] - 1, currentTile[1] };
		break;
	case RIGHT:
		currentTile = { currentTile[0] + 1, currentTile[1] };
		break;
	case UP:
		currentTile = { currentTile[0], currentTile[1] - 1 };
		break;
	case DOWN:
		currentTile = { currentTile[0], currentTile[1] + 1 };
		break;
	}

	return true;
}
