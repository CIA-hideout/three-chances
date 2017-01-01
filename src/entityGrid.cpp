#include "entityGrid.h"

EntityGrid::EntityGrid() {
	std::vector<int> gridRow;

	for (int i = 0; i < 32; ++i) {
		gridRow.push_back(0);
	}

	for (int j = 0; j < 32; ++j) {
		grid.push_back(gridRow);
	}
}

EntityGrid::~EntityGrid() {}

void EntityGrid::logGrid() {
	for (size_t i = 0; i < grid.size(); ++i) {
		for (size_t j = 0; j < grid[i].size(); ++j) {
			printf("%d ", grid[i][j]);
		}

		printf("\n");
	}
}

int EntityGrid::getTileValueAtCoordinates(Coordinates coordinates) {
	return grid[coordinates.y][coordinates.x];
}

Coordinates EntityGrid::getNextTileCoordinates(Coordinates coordinates, int direction) {
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

int EntityGrid::getNextTileValue(Coordinates coordinates, int direction) {
	Coordinates nextCoord = this->getNextTileCoordinates(coordinates, direction);
	return this->getTileValueAtCoordinates(nextCoord);
}

Coordinates EntityGrid::getEntityCoordinates(int id) {
	for (size_t i = 0; i < grid.size(); ++i) {
		for (size_t j = 0; j < grid[i].size(); ++j) {
			if (grid[i][j] == id) {
				return Coordinates(j, i);
			}
		}
	}

	return Coordinates(-1, -1);
}

Position EntityGrid::getEntityPosition(int id) {
	Coordinates playerCoord = this->getPlayerCoordinates();
	Coordinates entityCoord = this->getEntityCoordinates(id);

	if (entityCoord.x != -1 && entityCoord.y != -1) {
		Coordinates startCoord = Coordinates(playerCoord.x - 3, playerCoord.y - 3);

		float entityXPos = (float)(entityCoord.x - startCoord.x) * TILE_SIZE * SCALE;
		float entityYPos = (float)(entityCoord.y - startCoord.y) * TILE_SIZE * SCALE;

		return Position(entityXPos, entityYPos);
	}

	return Position(-1.0, -1.0);
}

Coordinates EntityGrid::getPlayerCoordinates() {
	return this->getEntityCoordinates(PLAYER_ID);
}

void EntityGrid::addEntity(Coordinates coordinates, int id) {
	grid[coordinates.y][coordinates.x] = id;
}

void EntityGrid::moveEntity(Coordinates currCoord, Coordinates nextCoord) {
	int id = grid[currCoord.y][currCoord.x];
	grid[currCoord.y][currCoord.x] = 0;
	grid[nextCoord.y][nextCoord.x] = id;
}

void EntityGrid::removeEntity(int id) {
	Coordinates coordinates = this->getEntityCoordinates(id);
	if (coordinates.x != -1 && coordinates.y != -1)
		grid[coordinates.y][coordinates.x] = 0;
}

bool EntityGrid::isCoordOccupied(Coordinates coord) {
	return grid[coord.y][coord.x] != 0;
}