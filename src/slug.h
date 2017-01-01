#ifndef _SLUG_H
#define _SLUG_H

#include "entity.h"

namespace slugNS {
	const int SLUG_STANDING_FRAME = 0;
	const int SLUG_WALK_START_FRAME = 0;
	const int SLUG_WALK_END_FRAME = 2;
	const int SLUG_ATK_START_FRAME = 3;
	const int SLUG_ATK_END_FRAME = 4;
	const float SLUG_ANIMATION_DELAY = 0.2f;
	const int SLUG_HURT_FRAME = 5;
	const int SLUG_COLS = 6;
}

class Slug : public Entity {
public:
	Slug();
	~Slug();

	void update(float frameTime);
	void startAttackAnimation();
	void startWalkAnimation();
	void startHurtAnimation();
	void startDeathAnimation();

	bool isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction);
	bool isValidSpawn(LevelGrid *levelGrid, Coordinates currCoord);
};

#endif