#ifndef _GHOST_H
#define _GHOST_H

#include "entity.h"
#include "input.h"
#include "player.h"
#include "levelGrid.h"
#include "monsterGrid.h"

class Ghost : public Entity {
public:
	Ghost();
	~Ghost();

	void update(float frameTime, MonsterGrid *monsterGrid);
	bool ai(float frameTime, Coordinates monsterCoord, Coordinates playerCoord);
	void rotateEntity(int direction);
	void startAttackAnimation();
	void startWalkAnimation();
	bool isValidMove(LevelGrid *levelGrid, int direction);
};
#endif