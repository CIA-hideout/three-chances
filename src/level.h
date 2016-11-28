#ifndef _LEVEL_H
#define _LEVEL_H

#include <map>
#include "player.h"
#include "levelGrid.h"
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
	void update(LevelGrid *levelGrid, Player *player);
	bool moveInDirection(float frameTime, int direction, float endPoint);
};

#endif
