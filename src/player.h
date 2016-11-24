#ifndef _PLAYER_H
#define _PLAYER_H

#include "entity.h"

class Player : public Entity {
public:
	Player();
	~Player();

	void update(float frameTime);
	void rotateEntity(std::string direction);
	void startAttackAnimation();
	void startWalkAnimation();
};
#endif