#ifndef _PLAYER_H
#define _PLAYER_H

#include <map>

#include "input.h"
#include "entity.h"
#include "levelGrid.h"
#include "gameControl.h"

class Player : public Entity {
public:
	Player();
	~Player();

	void update(float frameTime, LevelGrid *levelGrid, Input *input, 
		std::map<int, bool> *keysPressed, GameControl *gc);
	void rotateEntity(int direction, bool moveValid);
	void startAttackAnimation();
	void startWalkAnimation();
	bool isValidMove(LevelGrid *levelGrid, int direction);
};
#endif