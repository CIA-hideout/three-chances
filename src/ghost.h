#ifndef _GHOST_H
#define _GHOST_H

#include "entity.h"
#include "input.h"
#include "player.h"
#include "levelGrid.h"
#include "monsterGrid.h"
#include "gameControl.h"

class Ghost : public Entity {
public:
	Ghost();
	~Ghost();

	void update(float frameTime);
	int ai(float frameTime, Coordinates monsterCoord, Coordinates playerCoord, GameControl *gc);
	void rotateEntity(int direction);
	void startAttackAnimation();
	void startWalkAnimation();
	void startHurtAnimation();
	bool isValidMove(LevelGrid *levelGrid, int direction);
};
#endif