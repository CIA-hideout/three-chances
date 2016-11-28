#ifndef _LEVEL_H
#define _LEVEL_H

#include <map>
#include "levelGrid.h"
#include "input.h"
#include "player.h"
#include "gameControl.h"
#include "monsterGrid.h"

class Level : public Image {
public:
	Level();
	~Level();

	virtual bool initialize(Game *gamePtr, TextureManager *textureM);
	void update(float frameTime, LevelGrid *levelGrid, Player *player, 
		GameControl* gc, int direction);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
};

#endif