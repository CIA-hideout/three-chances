#ifndef _MONSTERGRID_H
#define _MONSTERGRID_H

#include <iostream>
#include <vector>
#include "constants.h"
#include "levelConstants.h"

class MonsterGrid {
private:
	std::vector<std::vector<int>> grid;

	// edges of screen
	Coordinates topLeft;
	Coordinates topRight;
	Coordinates bottomLeft;
	Coordinates bottomRight;

public:
	MonsterGrid();
	~MonsterGrid();

	std::vector<std::vector<int>> getGrid() { return grid; }
	void add(Coordinates coord, int type);
	Coordinates findCoord(int id);
	float convertCoordToXY(int index);
	void logLayout();

	float convertXCoord(int xIndex);
	float convertYCoord(int yIndex);

	void setTopLeft(Coordinates tl);
	void setTopRight(Coordinates tr);
	void setBottomLeft(Coordinates bl);
	void setBottomRight(Coordinates br);

	void moveCamera(int direction);
	void moveEdgesX(int range);
	void moveEdgesY(int range);

	void moveMonster(Coordinates prevCoord, Coordinates nextCoord);
};

#endif