#ifndef _LEVELCONSTANTS_H
#define _LEVELCONSTANTS_H

#include <vector>

struct Coordinates {
	int x;
	int y;
	Coordinates() {}
	Coordinates(int x, int y) : x(x), y(y) {}
};

struct Position {
	float x;
	float y;
	Position() {}
	Position(float x, float y) : x(x), y(y) {}
};

// Legend
// 0 - border
// 1 - 1st floor path
// 2 - 2nd floor path
// 3 - stairs
// 4 - water / lava
// 5 - obstacle
// 6 - blockage

const std::vector<std::vector<int>> STAGE_1_LAYOUT = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0 },
	{ 0, 0, 0, 4, 4, 5, 2, 2, 2, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 5, 0, 0, 0 },
	{ 0, 0, 0, 4, 4, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 6, 6, 6, 6, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 6, 6, 6, 6, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 5, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 5, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 5, 2, 2, 5, 5, 5, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 5, 2, 2, 5, 5, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 5, 2, 2, 5, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 5, 5, 2, 2, 5, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 5, 2, 2, 5, 1, 1, 5, 5, 5, 5, 5, 0, 0, 0 },
	{ 0, 0, 0, 1, 5, 2, 2, 5, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 5, 2, 2, 5, 1, 1, 5, 5, 5, 5, 5, 0, 0, 0 },
	{ 0, 0, 0, 1, 5, 3, 3, 5, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 5, 2, 2, 5, 1, 1, 5, 5, 5, 5, 5, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 4, 4, 4, 5, 2, 2, 5, 1, 1, 5, 5, 5, 5, 5, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1, 1, 5, 2, 2, 5, 1, 1, 5, 5, 5, 5, 5, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 1, 1, 1, 1, 1, 5, 2, 2, 5, 1, 1, 1, 1, 5, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1, 5, 2, 2, 5, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 5, 1, 4, 4, 4, 4, 1, 1, 1, 1, 5, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 1, 1, 1, 1, 5, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 5, 1, 4, 4, 4, 4, 4, 1, 1, 1, 1, 5, 5, 5, 5, 3, 3, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 5, 5, 1, 1, 1, 4, 4, 4, 4, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 5, 1, 1, 1, 1, 4, 4, 4, 4, 1, 5, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

const std::vector<std::vector<int>> STAGE_1_LAYOUT_CLEAR = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0 },
	{ 0, 0, 0, 4, 4, 5, 2, 2, 2, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 5, 0, 0, 0 },
	{ 0, 0, 0, 4, 4, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 5, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 5, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 5, 2, 2, 5, 5, 5, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 5, 2, 2, 5, 5, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 5, 2, 2, 5, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 5, 5, 2, 2, 5, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 5, 2, 2, 5, 1, 1, 5, 5, 5, 5, 5, 0, 0, 0 },
	{ 0, 0, 0, 1, 5, 2, 2, 5, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 5, 2, 2, 5, 1, 1, 5, 5, 5, 5, 5, 0, 0, 0 },
	{ 0, 0, 0, 1, 5, 3, 3, 5, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 5, 2, 2, 5, 1, 1, 5, 5, 5, 5, 5, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 4, 4, 4, 5, 2, 2, 5, 1, 1, 5, 5, 5, 5, 5, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1, 1, 5, 2, 2, 5, 1, 1, 5, 5, 5, 5, 5, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 1, 1, 1, 1, 1, 5, 2, 2, 5, 1, 1, 1, 1, 5, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1, 5, 2, 2, 5, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 5, 1, 4, 4, 4, 4, 1, 1, 1, 1, 5, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 1, 1, 1, 1, 5, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 5, 1, 4, 4, 4, 4, 4, 1, 1, 1, 1, 5, 5, 5, 5, 3, 3, 5, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 5, 5, 1, 1, 1, 4, 4, 4, 4, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 5, 1, 1, 1, 1, 4, 4, 4, 4, 1, 5, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

const std::vector<std::vector<int>> DEMO_LAYOUT = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 5, 5, 0, 0, 0 },
	{ 0, 0, 0, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 5, 0, 0, 0 },
	{ 0, 0, 0, 4, 4, 4, 4, 2, 2, 2, 2, 5, 3, 3, 0, 0, 0, 0 },
	{ 0, 0, 0, 4, 4, 4, 2, 2, 2, 2, 5, 5, 1, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 4, 4, 2, 2, 2, 5, 5, 5, 1, 1, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 4, 2, 2, 2, 5, 5, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 4, 2, 2, 5, 5, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 5, 1, 1, 1, 1, 1, 4, 4, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 5, 1, 1, 4, 4, 4, 4, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 5, 4, 4, 4, 4, 0, 0, 0, 0 },
	{ 0, 0, 0, 5, 2, 2, 2, 2, 2, 5, 4, 4, 4, 4, 0, 0, 0, 0 },
	{ 0, 0, 0, 5, 2, 2, 2, 2, 2, 5, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

const Coordinates STAGE_1_START_TILE(5, 28);
const Coordinates STAGE_1_END_TILE(16, 4);

const Coordinates DEMO_START_TILE(5, 14);
const Coordinates DEMO_END_TILE(8, 10);
#endif
