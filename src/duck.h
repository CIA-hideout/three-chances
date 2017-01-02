#ifndef _DUCK_H
#define _DUCK_H

#include "entity.h"

namespace duckNS {
	const int STANDING_FRAME = 0;
	const int WALK_START_FRAME = 0;
	const int WALK_END_FRAME = 3;
	const int ATK_START_FRAME = 4;
	const int ATK_END_FRAME = 5;
	const int HURT_FRAME = 6;
	const int COLS = 7;
	const float ANIMATION_DELAY = 0.2f;
}

class Duck : public Entity {
public:
	Duck();
	~Duck();

	void update(float frameTime);
	void startAttackAnimation();
	void startWalkAnimation();
	void startHurtAnimation();
	void startDeathAnimation();

	bool isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction);
	bool isValidSpawn(LevelGrid *levelGrid, Coordinates currCoord);
};

#endif
