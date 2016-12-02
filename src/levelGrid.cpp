#include "levelGrid.h"

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
void LevelGrid::logLayout() {
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
void LevelGrid::logTile(float x, float y) {
	printf("X: %.2f Y: %.2f Tile: %s\n", x, y, this->getCurrentTileType().c_str());
}

//=============================================================================
// Returns tile at specified coordinates
//=============================================================================
int LevelGrid::getTileValueAtCoordinates(Coordinates coordinates) {
	// Y coordinate has to be first because of how the 2D array is structured
	return layout[coordinates.y][coordinates.x];
}

//=============================================================================
// Returns value of tile at current coordinates
//=============================================================================
int LevelGrid::getCurrentTileValue() {
	return layout[currentTile.y][currentTile.x];
}

//=============================================================================
// Returns value of next tile in specified direction from current tile
//=============================================================================
int LevelGrid::getNextTileValue(Coordinates coordinates, int direction) {
	Coordinates nextCoord = this->getNextTileCoordinates(coordinates, direction);
	return this->getTileValueAtCoordinates(nextCoord);
}

Coordinates LevelGrid::getNextTileCoordinates(Coordinates currCoord, int direction) {
	Coordinates nextCoord;

	switch (direction) {
	case LEFT:
		nextCoord = { currCoord.x - 1, currCoord.y };
		break;
	case RIGHT:
		nextCoord = { currCoord.x + 1, currCoord.y };
		break;
	case UP:
		nextCoord = { currCoord.x, currCoord.y - 1 };
		break;
	case DOWN:
		nextCoord = { currCoord.x, currCoord.y + 1 };
		break;
	}

	return nextCoord;
}


Coordinates LevelGrid::convertXYToCoord(float x, float y) {
	return Coordinates( int(x/ SCALE/ TILE_SIZE), int(y/ SCALE /TILE_SIZE));
}

//=============================================================================
// Returns type of tile at current coordinates
//=============================================================================
std::string LevelGrid::getCurrentTileType() {
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
void LevelGrid::moveCurrentTile(int direction) {
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