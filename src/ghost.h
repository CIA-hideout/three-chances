#ifndef _GHOST_H
#define _GHOST_H

#include <vector>
#include "entity.h"

class Ghost : public Entity {
public:
	Ghost();
	~Ghost();

	void update(float frameTime);
	void rotateEntity(int direction);
	void startAttackAnimation();
	void startWalkAnimation();
	void startHurtAnimation();
	void startDeathAnimation();

	bool isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction);
};
#endif