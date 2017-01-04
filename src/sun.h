#ifndef _SUN_H
#define _SUN_H

#include "entity.h"

namespace sunNS {
	const int STANDING_FRAME = 0;
	const int WALK_START_FRAME = 0;
	const int WALK_END_FRAME = 2;
	const int ATK_START_FRAME = 3;
	const int ATK_END_FRAME = 4;
	const int HURT_FRAME = 5;
	const int COLS = 6;
	const float ANIMATION_DELAY = 0.2f;
}

class Sun : public Entity {
public:
	Sun();
	~Sun();

	void update(float frameTime);
	void startAttackAnimation();
	void startWalkAnimation();
	void startHurtAnimation();
	void startDeathAnimation();

	bool isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction);
	bool isValidSpawn(LevelGrid *levelGrid, Coordinates currCoord);
};

#endif