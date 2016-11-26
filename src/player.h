#ifndef _PLAYER_H
#define _PLAYER_H

#include <map>
#include <string>

#include "input.h"
#include "entity.h"
#include "stage.h"

class Player : public Entity {
public:
	Player();
	~Player();

	void update(float frameTime, Stage *stage, Input *input, std::map<std::string, bool> *keysPressed);
	void rotateEntity(std::string direction, bool moveValid);
	void startAttackAnimation();
	void startWalkAnimation();
};
#endif