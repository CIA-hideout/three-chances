#ifndef _LEVEL_H
#define _LEVEL_H

#include <map>
#include "constants.h"
#include "levelGrid.h"
#include "input.h"
#include "player.h"

class Level : public Image {
public:
	Level();
	~Level();

	virtual bool initialize(Game *gamePtr, TextureManager *textureM);
	void update(LevelGrid *levelGrid, Player player, Input *input, std::map<std::string, bool> *keysPressed);
};

#endif