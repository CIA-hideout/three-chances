#ifndef _DUCK_H
#define _DUCK_H

#include "entity.h"
#include "input.h"
#include "player.h"
#include "levelGrid.h"
#include "monsterGrid.h"

class Duck : public Entity {
public:
	Duck();
	~Duck();

	void update(float frameTime, MonsterGrid *monsterGrid);
	void ai(float frameTime, Player *player, LevelGrid *lvlGrid, MonsterGrid *mg);
	void startAttackAnimation();
	void startWalkAnimation();
	bool isValidMove(LevelGrid *levelGrid, int direction);
};
#endif
