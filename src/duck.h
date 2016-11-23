#ifndef _DUCK_H
#define _DUCK_H

#include "entity.h"

class Duck : public Entity {
public:
	Duck();
	~Duck();

	void update(float frameTime);
	void ai(float frameTime, Entity &ent);
	void setRect();
	void startAttackAnimation();
	void startWalkAnimation();
};

#endif