#ifndef _MONSTERSDATA_H
#define _MONSTERSDATA_H

#include "entity.h"

const EntityData DUCK_DATA = {
	5.0f,	// health
	0.5f,	// dmg
	1,		// atkRange
	2,		// moves
	std::vector<int> { 1, 2 },
	std::vector<entityNS::ABILITY_TYPE> {},
};

#endif