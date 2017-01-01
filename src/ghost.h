#ifndef _GHOST_H
#define _GHOST_H

#include "entity.h"

namespace ghostNS {
	const int GHOST_STANDING_FRAME = 0;
	const int GHOST_WALK_START_FRAME = 0;
	const int GHOST_WALK_END_FRAME = 3;
	const int GHOST_ATK_START_FRAME = 4;
	const int GHOST_ATK_END_FRAME = 5;
	const float GHOST_ANIMATION_DELAY = 0.2f;
	const int GHOST_HURT_FRAME = 6;
	const int GHOST_COLS = 7;
}

class Ghost : public Entity {
public:
	Ghost();
	~Ghost();

	void update(float frameTime);
	void startAttackAnimation();
	void startWalkAnimation();
	void startHurtAnimation();
	void startDeathAnimation();

	bool isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction);
	bool isValidSpawn(LevelGrid *levelGrid, Coordinates currCoord);
};

#endif