#ifndef _ENTITY_H
#define _ENTITY_H

#include <vector>
#include <string>
#include "game.h"
#include "image.h"
#include "levelGrid.h"
#include "entityGrid.h"
#include "levelConstants.h"

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
	int id;
	float health;
	float damage;
	int atkRange;
	int moves;
	int movesLeft;
	std::vector<int> levels;
	std::vector<entityNS::ABILITY_TYPE> abilities;

	Position endPoint;
	bool animating;
	int action;
	float timer;
	Audio *audio;	// pointer to audio system

public:
	Entity();
	~Entity();

	// getters
	int getId() const { return id; }
	float getHealth() const { return health; }
	float getDamage() const { return damage; }
	int getAtkRange() const { return atkRange; }
	int getMoves() const { return moves; }
	int getMovesLeft() const { return movesLeft; }
	std::vector<int> getLevels() const { return levels; }
	std::vector<entityNS::ABILITY_TYPE> getAbilities() const { return abilities; }
	Position getEndPoint() const { return endPoint; }
	bool getAnimating() const { return animating; }
	int getAction() const { return action; }
	float getTimer() const { return timer; }

	// setters
	void setId(int i) { id = i; }
	void setHealth(float h) { health = h; }
	void setDamage(float d) { damage = d; }
	void setAtkRange(int ar) { atkRange = ar; }
	void setMoves(int m) { moves = m; }
	void setMovesLeft(int ml) { movesLeft = ml; }
	void setLevel(std::vector<int> l) { levels = l; }
	void setAbilities(std::vector<entityNS::ABILITY_TYPE> a) { abilities = a; }
	void setEndPoint(Position ep) { endPoint = ep; }
	void setAnimating(bool a) { animating = a; }
	void setAction(int a) { action = a; }
	void setTimer(float t) { timer = t; }

	// can be overridden
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM, EntityData ed);
	virtual void update(float frameTime);
	virtual void ai(float frameTime, Entity &ent);
	virtual void setRect();
	virtual void rotateEntity(int direction);
	virtual void moveExecuted();
	virtual void resetMovesLeft();

	virtual void startAttackAnimation() {}
	virtual void startWalkAnimation() {}
	virtual void startHurtAnimation() {}
	virtual void startDeathAnimation() {}
	
	// To compensate for map movement
	virtual bool moveInDirection(float frameTime, int direction, Position endPos);

	// For AI moving
	virtual bool aiMoveInDirection(float frameTime, int direction, Position endPos);

	virtual void logAction();

	virtual void initAi(EntityGrid *entityGrid, LevelGrid *levelGrid);
	virtual bool animateAi(float frameTime, EntityGrid *entityGrid);
	
	virtual bool isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction);
	virtual bool isTileEmpty(EntityGrid *entityGrid, int direction);

	virtual int getBestXmove(int monsterX, int playerX);
	virtual int getBestYmove(int monsterY, int playerY);

	virtual std::vector<int> getBestMoves(Coordinates monsterCoord, Coordinates playerCoord);
	virtual std::vector<int> getAvailableMoves(EntityGrid *entityGrid, LevelGrid *levelGrid, Coordinates monsterCoord);
};

#endif