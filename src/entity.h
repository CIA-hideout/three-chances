#ifndef _ENTITY_H
#define _ENTITY_H

#include <vector>
#include <string>
#include "image.h"
#include "game.h"

namespace entityNS {
	enum ABILITY_TYPE { TRAVEL_WATER, TRAVEL_LAVA, TRAVEL_WALL, BURNS_PLAYER, SHOOTS_FIRE };
}

struct EntityData {
	float health;
	float damage;
	int atkRange;
	int moves;
	std::vector<int> levels;
	std::vector<entityNS::ABILITY_TYPE> abilities;
};

class Entity: public Image {
protected:
	float health;	// there is 0.5 dmg
	float damage;
	int atkRange;
	int moves;
	std::vector<int> levels;
	std::vector<entityNS::ABILITY_TYPE> abilities;

public:
	Entity();
	~Entity();

	// getters
	float getHealth() const { return health; }
	float getDamamge() const { return damage; }
	int getAtkRange() const { return atkRange; }
	int getMoves() const { return moves; }
	std::vector<int> getLevels() const { return levels; }
	std::vector<entityNS::ABILITY_TYPE> getAbilities() const { return abilities; }

	// setters
	void setHealth(float h) { health = h; }
	void setDamage(float d) { damage = d; }
	void setAtkRange(int ar) { atkRange = ar; }
	void setMoves(int m) { moves = m; }
	void setLevel(std::vector<int> l) { levels = l; }
	void setAbilities(std::vector<entityNS::ABILITY_TYPE> a) { abilities = a; }

	// can be overridden
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM, EntityData ed);
	virtual void update(float frameTime);
	virtual void setRect();
	virtual void rotateEntity(std::string direction);
	virtual void startAttackAnimation() {}
	virtual void startWalkAnimation() {}
	virtual void ai(float frameTime, Entity &ent);
};

#endif