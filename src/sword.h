#ifndef _SWORD_H
#define _SWORD_H

#include "image.h"
#include "game.h"

class Sword : public Image {
public:
	Sword();
	~Sword();

	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);

	void setRect();

	void setDirection(int direction);

	void rotateSwordCW(float frameTime);
	void rotateSwordACW(float frameTime);

	void attack(float frameTime);
};

#endif
