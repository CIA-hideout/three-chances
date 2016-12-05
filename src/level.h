#ifndef _LEVEL_H
#define _LEVEL_H

#include <map>
#include "player.h"
#include "levelGrid.h"

class Level : public Image {
private:
	bool pathBlocked;

public:
	Level();
	~Level();

	bool getPathBlocked() const { return pathBlocked; }
	void setPathBlocked(bool pb) { pathBlocked = pb; }

	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void finishAnimating(LevelGrid *levelGrid, Player *player);
	bool moveInDirection(float frameTime, int direction, float endPoint);
	void removeBlockage();
};

#endif
