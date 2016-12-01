#ifndef _PLAYER_H
#define _PLAYER_H

#include <map>

#include "entity.h"
#include "levelGrid.h"
#include "monsterGrid.h"
#include "gameControl.h"

class Player : public Entity {
private:
	bool	animating;
	int		direction;
	float	endPoint;

public:
	Player();
	~Player();

	void update(float frameTime, GameControl* gc);
	void rotateEntity(int direction);
	void startAttackAnimation();
	void startWalkAnimation();
	bool isValidMove(LevelGrid *levelGrid, int direction);
	void moveInDirection(LevelGrid *levelGrid, MonsterGrid *monsterGrid, 
		int direction, float endPoint, GameControl* gc);

	bool getAnimating() const { return animating; }
	void setAnimating(bool a) { animating = a; }

	int getDirection() const { return direction; }
	void setDirection(int d) { direction = d; }

	float getEndPoint() const { return endPoint; }
	void setEndPoint(float ep) { endPoint = ep; }
};
#endif