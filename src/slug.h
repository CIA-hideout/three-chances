#ifndef _SLUG_H
#define _SLUG_H

#include "entity.h"
#include "levelGrid.h"
#include "input.h"
#include "player.h"

class Slug : public Entity {
public:
	Slug();
	~Slug();

	void update(float frameTime, LevelGrid *levelGrid, Player player, Input *input, std::map<std::string, bool> *keysPressed);
	void ai(float frameTime, Entity &ent);
	void rotateEntity(std::string direction, bool moveValid);
	void startAttackAnimation();
	void startWalkAnimation();
};
#endif