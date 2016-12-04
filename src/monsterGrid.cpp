#include "monsterGrid.h"

MonsterGrid::MonsterGrid() {
	std::vector<int> gridRow;

	for (int i = 0; i < 32; ++i) {
		gridRow.push_back(0);
	}

	for (int j = 0; j < 32; ++j) {
		grid.push_back(gridRow);
	}
}

MonsterGrid::~MonsterGrid() {}

void MonsterGrid::logLayout() {
	for (size_t i = 0; i < grid.size(); ++i) {
		for (size_t j = 0; j < grid[i].size(); ++j) {
			printf("%d ", grid[i][j]);
		}

		printf("\n");
	}
}

int MonsterGrid::getValueAtCoordinates(Coordinates coordinates) {
	return grid[coordinates.y][coordinates.x];
}

int MonsterGrid::getNextTileValue(Coordinates coordinates, int direction) {
	Coordinates nextCoord = this->getNextTileCoordinates(coordinates, direction);
	return this->getValueAtCoordinates(nextCoord);
}

Coordinates MonsterGrid::getNextTileCoordinates(Coordinates currCoord, int direction) {
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

Coordinates MonsterGrid::findMonsterCoord(int id) {
	for (size_t i = 0; i < grid.size(); ++i) {
		for (size_t j = 0; j < grid[i].size(); ++j) {
			if (grid[i][j] == id) {
				return Coordinates(j, i);
			}
		}
	}

	return Coordinates(-1, -1);
}

Position MonsterGrid::getMonsterPos(Coordinates currentTile, int id) {
	Coordinates monsterCoord = this->findMonsterCoord(id);

	if (monsterCoord.x != -1 && monsterCoord.y != -1) {
		Coordinates startPos = Coordinates(currentTile.x - 3, currentTile.y - 3);

		float monsterXPos = (monsterCoord.x - startPos.x) * TILE_SIZE * SCALE;
		float monsterYPos = (monsterCoord.y - startPos.y) * TILE_SIZE * SCALE;

		return Position(monsterXPos, monsterYPos);
	}
	
	return Position(-1.0, -1.0);
}

void MonsterGrid::addMonster(Coordinates coord, int id) {
	grid[coord.y][coord.x] = id;
}

void MonsterGrid::moveMonster(Coordinates currCoord, Coordinates nextCoord) {
	int id = grid[currCoord.y][currCoord.x];
	grid[currCoord.y][currCoord.x] = 0;
	grid[nextCoord.y][nextCoord.x] = id;
}

void MonsterGrid::removeMonster(int id) {
	Coordinates coord = this->findMonsterCoord(id);
	if (coord.x != -1 && coord.y != -1)
		grid[coord.y][coord.x] = 0;
}
