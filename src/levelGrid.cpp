#include "levelGrid.h"

//=============================================================================
// Constructor
//=============================================================================
LevelGrid::LevelGrid() {}

//=============================================================================
// Destructor
//=============================================================================
LevelGrid::~LevelGrid() {}

//=============================================================================
// Initializes the map
//=============================================================================
bool LevelGrid::initialize(int stageNo) {
	switch (stageNo) {
	case 1:
		grid = STAGE_1_LAYOUT;
		startTile = STAGE_1_START_TILE;
		endTile = STAGE_1_END_TILE;
		break;
	}

	return true;
}

//=============================================================================
// Logs entire map layout
//=============================================================================
void LevelGrid::logGrid() {
	for (size_t i = 0; i < grid.size(); ++i) {
		for (size_t j = 0; j < grid[i].size(); ++j) {
			printf("%d ", grid[i][j]);
		}

		printf("\n");
	}
}

//=============================================================================
// Log tile information with x and y coordinates
//=============================================================================
void LevelGrid::logTile(Coordinates coordinates, float x, float y) {
	printf("X: %.2f Y: %.2f Tile: %s\n", x, y, this->getTileType(coordinates).c_str());
}

//=============================================================================
// Returns type of tile at current coordinates
//=============================================================================
std::string LevelGrid::getTileType(Coordinates coordinates) {
	int value = this->getTileValueAtCoordinates(coordinates);
	std::string tileType;

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
// Returns tile at specified coordinates
//=============================================================================
int LevelGrid::getTileValueAtCoordinates(Coordinates coordinates) {
	// Y coordinate has to be first because of how the 2D array is structured
	return grid[coordinates.y][coordinates.x];
}

//=============================================================================
// Returns coordinates of next tile in direction from specified coordinates
//=============================================================================
Coordinates LevelGrid::getNextTileCoordinates(Coordinates coordinates, int direction) {
	Coordinates nextCoord;

	switch (direction) {
	case LEFT:
		nextCoord = { coordinates.x - 1, coordinates.y };
		break;
	case RIGHT:
		nextCoord = { coordinates.x + 1, coordinates.y };
		break;
	case UP:
		nextCoord = { coordinates.x, coordinates.y - 1 };
		break;
	case DOWN:
		nextCoord = { coordinates.x, coordinates.y + 1 };
		break;
	}

	return nextCoord;
}

//=============================================================================
// Returns value of next tile in direction from specified coordinates
//=============================================================================
int LevelGrid::getNextTileValue(Coordinates coordinates, int direction) {
	Coordinates nextCoord = this->getNextTileCoordinates(coordinates, direction);
	return this->getTileValueAtCoordinates(nextCoord);
}
