#ifndef _LEVEL_H
#define _LEVEL_H

#include <map>
#include "player.h"
#include "levelGrid.h"

class Level : public Image {
public:
	Level();
	~Level();

	virtual bool initialize(Game *gamePtr, TextureManager *textureM);
	void finishAnimating(LevelGrid *levelGrid, Player *player);
	bool moveInDirection(float frameTime, int direction, float endPoint);
};

#endif
