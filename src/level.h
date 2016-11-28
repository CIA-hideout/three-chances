#ifndef _LEVEL_H
#define _LEVEL_H

#include <map>
#include "levelGrid.h"
#include "input.h"
#include "player.h"
#include "gameControl.h"
#include "monsterGrid.h"

class Level : public Image {
private:
	bool isMoving;
	int direction;
	float endPoint;

public:
	Level();
	~Level();

	void setIsMoving(bool im) { isMoving = im; }
	void setDirection(int d) { direction = d; }
	void setEndPoint(float ep) { endPoint = ep; }

	bool getIsMoving() { return isMoving; }
	int getDirection() { return direction; }
	float getEndPoint() { return endPoint; }

	virtual bool initialize(Game *gamePtr, TextureManager *textureM);
	void update(float frameTime, LevelGrid *levelGrid, Player *player,
		GameControl* gc, int direction);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
};

#endif
