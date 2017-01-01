#ifndef _MOON_H
#define _MOON_H

#include "entity.h"

namespace moonNS {
	const int MOON_STANDING_FRAME = 0;
	const int MOON_WALK_START_FRAME = 0;
	const int MOON_WALK_END_FRAME = 2;
	const int MOON_ATK_START_FRAME = 3;
	const int MOON_ATK_END_FRAME = 4;
	const float MOON_ANIMATION_DELAY = 0.25f;
	const int MOON_HURT_FRAME = 5;
	const int MOON_COLS = 6;
}

class Moon : public Entity {
public:
	Moon();
	~Moon();

	void update(float frameTime);
	void startAttackAnimation();
	void startWalkAnimation();
	void startHurtAnimation();
	void startDeathAnimation();

	bool isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction);
	bool isValidSpawn(LevelGrid *levelGrid, Coordinates currCoord);
};

#endif