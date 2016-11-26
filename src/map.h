#ifndef _MAP_H
#define _MAP_H

#include <map>
#include "constants.h"
#include "stage.h"
#include "input.h"
#include "player.h"

class Map : public Image {
public:
	Map();
	~Map();

	virtual bool initialize(Game *gamePtr, TextureManager *textureM);
	void update(Stage *stage, Player player, Input *input, std::map<std::string, bool> *keysPressed);
};

#endif