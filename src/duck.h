#ifndef _DUCK_H
#define _DUCK_H

#include "entity.h"
#include "levelGrid.h"
#include "input.h"
#include "player.h"
#include "levelGrid.h"

class Duck : public Entity {
public:
	Duck();
	~Duck();

	void rotateEntity(std::string direction, bool moveValid);
	void update(float frameTime);
	void ai(float frameTime, Player *player, LevelGrid *lvlGrid);
	void startAttackAnimation();
	void startWalkAnimation();
	bool isValidMove(LevelGrid *levelGrid, int direction);
};
#endif
