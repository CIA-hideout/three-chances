#ifndef _HUD_H
#define _HUD_H

#include <vector>

#include "constants.h"
#include "entityConstants.h"

#include "textureManager.h"
#include "image.h"
#include "graphics.h"
#include "player.h"

class Hud {
private:
	TextureManager hudBgTexture;
	TextureManager turnIconTexture;
	Image hudBg;
	std::vector<Image> turnIcons;
	
	bool initialized;

public:
	Hud();
	~Hud();

	void initializeTexture(Graphics *graphics);
	void setInitialPosition();
	void update(float frameTime, Player* player);
	void draw();
	void releaseAll();
	void resetAll();
};
#endif