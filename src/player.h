#ifndef _PLAYER_H
#define _PLAYER_H

#include <map>

#include "input.h"
#include "entity.h"
#include "levelGrid.h"
#include "gameControl.h"

class Player : public Entity {
private:
	bool	animating;
	int		direction;
	float	endPoint;

public:
	Player();
	~Player();

	void update(float frameTime, LevelGrid *levelGrid, Input *input, 
		std::map<int, bool> *keysPressed, GameControl *gc);
	void rotateEntity(int direction, bool moveValid);
	void startAttackAnimation();
	void startWalkAnimation();
	bool isValidMove(LevelGrid *levelGrid, int direction);

	bool getAnimating() const { return animating; }
	void setAnimating(bool a) { animating = a; }

	int getDirection() const { return direction; }
	void setDirection(int d) { direction = d; }

	float getEndPoint() const { return endPoint; }
	void setEndPoint(float ep) { endPoint = ep; }
};
#endif