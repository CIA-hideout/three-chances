#ifndef _SWORD_H
#define _SWORD_H

#include "image.h"
#include "game.h"
#include "player.h"

class Sword : public Image {
private:
	int count = 0;
public:
	Sword();
	~Sword();

	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);

	void setRect();

	void setDirection(int direction, float playerX, float playerY);

	bool attack(float frameTime);

	void finishAnimating(Player *p);
};

#endif
