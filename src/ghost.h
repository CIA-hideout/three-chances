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
	void rotateEntity(int direction);
	void startAttackAnimation();
	void startWalkAnimation();
	void startHurtAnimation();
	void startDeathAnimation();
	bool isValidMove(LevelGrid *levelGrid, int direction);
	
	// ai woes
	void initAi(MonsterGrid *mg, Coordinates playerCoord, GameControl *gc);
	bool animateAi(float frameTime, MonsterGrid *mg, Coordinates playerCoord);
};
#endif