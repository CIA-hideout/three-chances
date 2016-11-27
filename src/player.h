#ifndef _PLAYER_H
#define _PLAYER_H

#include <map>
#include <string>

#include "input.h"
#include "entity.h"
#include "levelGrid.h"
#include "gameControl.h"

class Player : public Entity {
public:
	Player();
	~Player();

	void update(float frameTime, LevelGrid *levelGrid, Input *input, 
		std::map<std::string, bool> *keysPressed, GameControl *gc);
	void rotateEntity(std::string direction, bool moveValid);
	void startAttackAnimation();
	void startWalkAnimation();
	bool isValidMove(LevelGrid *levelGrid, int direction);
};
#endif