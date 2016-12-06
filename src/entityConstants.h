#ifndef _ENTITYCONST_H
#define _ENTITYCONST_H

#include "entity.h"

const EntityData PLAYER_DATA = {
	3.0f,	// health
	1.0f,	// dmg
	1,		// atkRange
	4,		// moves
	std::vector < int > {},
	std::vector < entityNS::ABILITY_TYPE > {},
};

const EntityData DUCK_DATA = {
	2.0f,	// health
	0.5f,	// dmg
	1,		// atkRange
	3,		// moves
	std::vector < int > { 1, 2 },
	std::vector < entityNS::ABILITY_TYPE > {},
};

const EntityData GHOST_DATA = {
	2.0f,	// health
	0.5f,	// dmg
	1,		// atkRange
	2,		// moves
	std::vector < int > { 1, 2 },
	std::vector < entityNS::ABILITY_TYPE > {  entityNS::TRAVEL_WALL },
};

const EntityData SLUG_DATA = {
	2.0f,	// health
	1.0f,	// dmg
	1,		// atkRange
	2,		// moves
	std::vector < int > { 1 },
	std::vector < entityNS::ABILITY_TYPE > { entityNS::TRAVEL_LAVA, entityNS::BURNS_PLAYER },
};

const EntityData MOON_DATA = {
	4.0f,	// health
	0.5f,	// dmg
	1,		// atkRange
	4,		// moves
	std::vector < int > { 1 },
	std::vector < entityNS::ABILITY_TYPE > {},
};

const std::vector<Coordinates> DUCK_START_COORDS = {
	Coordinates(7, 24),
	Coordinates(8, 27),
	Coordinates(9, 19),
	Coordinates(10, 12),
	Coordinates(11, 16),
	Coordinates(12, 23),
	Coordinates(14, 25),
	Coordinates(14, 28),
	Coordinates(15, 18),
	Coordinates(15, 13),
	Coordinates(17, 20),
};

const std::vector<Coordinates> GHOST_START_COORDS = {
	Coordinates(4, 19),
	Coordinates(4, 24),
	Coordinates(5, 7),
	Coordinates(6, 12),
	Coordinates(7, 5),
	Coordinates(8, 9),
	Coordinates(11, 5),
	Coordinates(14, 7),
	Coordinates(18, 8),
	Coordinates(18, 23),
	Coordinates(18, 27),
	Coordinates(19, 11),
	Coordinates(20, 18),
	Coordinates(22, 6),
	Coordinates(23, 9),
	Coordinates(23, 23),
	Coordinates(24, 15),
	Coordinates(24, 28),
	Coordinates(27, 21),
	Coordinates(27, 26),
	Coordinates(28, 14),
};

const std::vector<Coordinates> MOON_START_COORDS = {
	Coordinates(6, 19),
	Coordinates(10, 6),
	Coordinates(12, 13),
	Coordinates(21, 27),
	Coordinates(23, 12),
};

#endif