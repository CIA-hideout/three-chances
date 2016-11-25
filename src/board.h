#ifndef _BOARD_H
#define _BOARD_H

#include <map>
#include "constants.h"
#include "image.h"
#include "game.h"
#include "stage.h"
#include "input.h"

class Board : public Image {
public:
	Board();
	~Board();

	virtual bool initialize(Game *gamePtr, TextureManager *textureM);
	void update(Stage *stage, Input *input, std::map<std::string, bool> *keysPressed);
};

#endif