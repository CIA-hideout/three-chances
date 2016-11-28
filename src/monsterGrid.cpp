#include "monsterGrid.h"

MonsterGrid::MonsterGrid() {
	std::vector<int> tempVec;

	for (int i = 0; i < 32; ++i) {
		tempVec.push_back(0);
	}

	for (int j = 0; j < 32; ++j) {
		grid.push_back(tempVec);
	}

	topLeft = Coordinates(0, 25);
	topRight = Coordinates(6, 25);
	bottomLeft = Coordinates(0, 31);
	bottomRight = Coordinates(6, 31);
}

MonsterGrid::~MonsterGrid() {}

void MonsterGrid::add(Coordinates coord, int type) {
	grid[coord.y][coord.x] = type;
}

void MonsterGrid::logLayout() {
	for (size_t i = 0; i < grid.size(); ++i) {
		for (size_t j = 0; j < grid[i].size(); ++j) {
			printf("%d ", grid[i][j]);
		}

		printf("\n");
	}
}

Coordinates MonsterGrid::findCoord(int id) {
	for (size_t i = 0; i < grid.size(); ++i) {
		for (size_t j = 0; j < grid[i].size(); ++j) {
			if (grid[i][j] == id) {
				return Coordinates(j, i);
			}
		}
	}

	return Coordinates(-1, -1);
}

float MonsterGrid::convertYCoord(int yIndex) {
	int noOfGrids = 0;
	bool inMap = false;

	for (int i = topLeft.y; i <= bottomLeft.y; i++) {
		if (i == yIndex) {
			inMap = true;
			break;
		}
		noOfGrids++;
	}

	if (!inMap) {
		return -1.0;
	}

	return float(noOfGrids * TILE_SIZE * SCALE);
}

float MonsterGrid::convertXCoord(int xIndex) {
	int noOfGrids = 0;
	bool inMap = false;
	
	for (int i = bottomLeft.x; i <= bottomRight.x; i++) {
		if (i == xIndex) {
			inMap = true;
			break;
		}
		noOfGrids++;
	}

	if (!inMap) {
		return -1.0;
	}

	return float(noOfGrids * TILE_SIZE * SCALE);
}

// Assuming target is seen on map
float MonsterGrid::convertMapToXCoord(float x) {
	float noOfGrids = x / TILE_SIZE / SCALE;
	return noOfGrids + topLeft.x;
}

// Assuming target is seen on map
float MonsterGrid::convertMapToYCoord(float y) {
	float noOfGrids = y / TILE_SIZE / SCALE;
	return noOfGrids + topLeft.y;
}

void MonsterGrid::moveEdgesX(int range) {
	topLeft.x = topLeft.x + range;
	bottomLeft.x = bottomLeft.x + range;
	topRight.x = topRight.x + range;
	bottomRight.x = bottomRight.x + range;
}

void MonsterGrid::moveEdgesY(int range) {
	topLeft.y = topLeft.y + range;
	bottomLeft.y = bottomLeft.y + range;
	topRight.y = topRight.y + range;
	bottomRight.y = bottomRight.y + range;
}

void MonsterGrid::moveCamera(int direction) {
	if (direction == LEFT)
		moveEdgesX(-1);
	else if (direction == RIGHT)
		moveEdgesX(1);
	else if (direction == UP)
		moveEdgesY(-1);
	else if (direction == DOWN)
		moveEdgesY(1);
}

void MonsterGrid::moveMonster(Coordinates prevCoord, Coordinates nextCoord) {
	int id = grid[prevCoord.y][prevCoord.x];
	grid[prevCoord.y][prevCoord.x] = 0;
	grid[nextCoord.y][nextCoord.x] = id;
}