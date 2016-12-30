#ifndef ENTITYGRID_H
#define ENTITYGRID_H

#include <vector>
#include "constants.h"
#include "levelConstants.h"

class EntityGrid {
private:
	std::vector<std::vector<int>> grid;

public:
	EntityGrid();
	~EntityGrid();

	std::vector<std::vector<int>> getGrid() { return grid; }
	void setGrid(std::vector<std::vector<int>> g) { grid = g; }

	// Logging
	void logGrid();

	int getTileValueAtCoordinates(Coordinates coordinates);

	Coordinates getNextTileCoordinates(Coordinates currCoord, int direction);
	int getNextTileValue(Coordinates coordinates, int direction);

	Coordinates getEntityCoordinates(int id);
	Position getEntityPosition(int id);

	Coordinates getPlayerCoordinates();

	void addEntity(Coordinates coordinates, int id);
	void moveEntity(Coordinates currCoord, Coordinates nextCoord);
	void removeEntity(int id);

	bool isEntityOnGrid(Coordinates coord);
};

#endif
