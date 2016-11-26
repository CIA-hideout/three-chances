#include "stage.h"

//=============================================================================
// Helpers
//=============================================================================
bool isObstacle(int prevTileValue, int tileValue) {
	return
		(prevTileValue == 1 && tileValue == 2) ||
		(prevTileValue == 2 && tileValue == 1) ||
		tileValue == 0 || tileValue == 3 || 
		tileValue == 4 || tileValue == 5 || 
		tileValue == 6;
}

//=============================================================================
// Constructor
//=============================================================================
Stage::Stage() {}

//=============================================================================
// Destructor
//=============================================================================
Stage::~Stage() {}

//=============================================================================
// Initializes the map
//=============================================================================
bool Stage::initialize(int stageNo) {
	switch (stageNo) {
	case 1:
		layout = STAGE_1_LAYOUT;
		startTile = STAGE_1_START_TILE;
		endTile = STAGE_1_END_TILE;
		currentTile = STAGE_1_START_TILE;
		break;
	}

	return true;
}

//=============================================================================
// Logs entire map layout
//=============================================================================
void Stage::logLayout() {
	for (size_t i = 0; i < layout.size(); ++i) {
		for (size_t j = 0; j < layout[i].size(); ++j) {
			printf("%d ", layout[i][j]);
		}

		printf("\n");
	}
}

//=============================================================================
// Log tile information with x and y coordinates
//=============================================================================
void Stage::logTile(float x, float y) {
	printf("X: %.2f Y: %.2f Tile: %s\n", x, y, this->getCurrentTileType().c_str());
}

//=============================================================================
// Returns tile at specified coordinates
//=============================================================================
int Stage::getTileValueAtCoordinates(Coordinates coordinates) {
	// Y coordinate has to be first because of how the 2D array is structured
	return layout[coordinates.y][coordinates.x];
}

//=============================================================================
// Returns value of tile at current coordinates
//=============================================================================
int Stage::getCurrentTileValue() {
	return layout[currentTile.y][currentTile.x];
}

//=============================================================================
// Returns value of next tile in specified direction from current tile
//=============================================================================
int Stage::getNextTileValue(int direction) {
	Coordinates nextCoord;

	switch (direction) {
	case LEFT:
		nextCoord = { currentTile.x - 1, currentTile.y };
		break;
	case RIGHT:
		nextCoord = { currentTile.x + 1, currentTile.y };
		break;
	case UP:
		nextCoord = { currentTile.x, currentTile.y - 1 };
		break;
	case DOWN:
		nextCoord = { currentTile.x, currentTile.y + 1 };
		break;
	}

	return this->getTileValueAtCoordinates(nextCoord);
}

//=============================================================================
// Returns type of tile at current coordinates
//=============================================================================
std::string Stage::getCurrentTileType() {
	int value = getCurrentTileValue();
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
// Shifts current tile by 1 tile in specified direction
//=============================================================================
void Stage::moveCurrentTile(int direction) {
	switch (direction) {
	case LEFT:
		currentTile = { currentTile.x - 1, currentTile.y };
		break;
	case RIGHT:
		currentTile = { currentTile.x + 1, currentTile.y };
		break;
	case UP:
		currentTile = { currentTile.x, currentTile.y - 1 };
		break;
	case DOWN:
		currentTile = { currentTile.x, currentTile.y + 1 };
		break;
	}
}