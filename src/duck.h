#ifndef _DUCK_H
#define _DUCK_H

#include "entity.h"

namespace duckNS {
	const int DUCK_STANDING_FRAME = 0;
	const int DUCK_WALK_START_FRAME = 0;
	const int DUCK_WALK_END_FRAME = 3;
	const int DUCK_ATK_START_FRAME = 4;
	const int DUCK_ATK_END_FRAME = 5;
	const float DUCK_ANIMATION_DELAY = 0.2f;
	const int DUCK_HURT_FRAME = 6;
	const int DUCK_COLS = 7;
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
