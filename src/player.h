#ifndef _PLAYER_H
#define _PLAYER_H

#include <map>

#include "constants.h"
#include "entity.h"
#include "levelGrid.h"
#include "entityGrid.h"
#include "gameControl.h"

namespace playerNS
{
	// Place player in middle of screen
	const int X = TILE_SIZE * SCALE * 3;
	const int Y = TILE_SIZE * SCALE * 3;
}

class Player : public Entity {
private:
	bool	animating;
	float	endPoint;

public:
	Player();
	~Player();

	bool getAnimating() const { return animating; }
	float getEndPoint() const { return endPoint; }

	void setAnimating(bool a) { animating = a; }
	void setEndPoint(float ep) { endPoint = ep; }

	void update(float frameTime, GameControl* gc);
	void startAttackAnimation();
	void startWalkAnimation();
	bool isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction);
	void moveInDirection(LevelGrid *levelGrid, EntityGrid *entityGrid, 
		int direction, float endPoint, GameControl* gc);
};
#endif