#ifndef _DUCK_H
#define _DUCK_H

#include "entity.h"

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
