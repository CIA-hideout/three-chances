#ifndef _DUCK_H
#define _DUCK_H

#include "entity.h"
#include "levelGrid.h"
#include "input.h"
#include "player.h"

class Duck : public Entity {
public:
	Duck();
	~Duck();

	void update(float frameTime, LevelGrid *levelGrid, Player player, Input *input, std::map<std::string, bool> *keysPressed);
	void ai(float frameTime, Entity &ent);
	void rotateEntity(std::string direction, bool moveValid);
	void startAttackAnimation();
	void startWalkAnimation();
};
#endif