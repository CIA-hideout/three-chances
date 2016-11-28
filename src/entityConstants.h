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
	2,		// moves
	std::vector < int > { 1, 2 },
	std::vector < entityNS::ABILITY_TYPE > {},
};

const EntityData GHOST_DATA = {
	2.0f,	// health
	0.5f,	// dmg
	1,		// atkRange
	2,		// moves
	std::vector < int > { 1, 2 },
	std::vector < entityNS::ABILITY_TYPE > {},
};

const EntityData SLUG_DATA = {
	2.0f,	// health
	0.5f,	// dmg
	1,		// atkRange
	2,		// moves
	std::vector < int > { 1, 2 },
	std::vector < entityNS::ABILITY_TYPE > {},
};

#endif