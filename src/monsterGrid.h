#ifndef _MONSTERGRID_H
#define _MONSTERGRID_H

#include <iostream>
#include <vector>
#include "constants.h"
#include "levelConstants.h"

class MonsterGrid {
private:
	std::vector<std::vector<int>> grid;

public:
	MonsterGrid();
	~MonsterGrid();

	std::vector<std::vector<int>> getGrid() { return grid; }

	void logLayout();
	int getValueAtCoordinates(Coordinates coordinates);

	Coordinates findMonsterCoord(int id);
	Position getMonsterPos(Coordinates currentTile, int id);

	void addMonster(Coordinates coord, int id);
	void moveMonster(Coordinates currCoord, Coordinates nextCoord);
	void removeMonster(int id);
};

#endif