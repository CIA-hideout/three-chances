#ifndef _HUD_H
#define _HUD_H

#include <vector>

#include "constants.h"
#include "entityConstants.h"

#include "textureManager.h"
#include "image.h"
#include "graphics.h"
#include "player.h"
#include "font.h"

class Hud {
private:
	TextureManager movesHeaderTexture;
	TextureManager healthHeaderTexture;
	TextureManager enemiesLeftHeaderTexture;
	TextureManager moveIconTexture;
	TextureManager emptyMoveIconTexture;
	TextureManager healthIconTexture;
	TextureManager halfHealthIconTexture;
	TextureManager emptyHealthIconTexture;
	Image movesHeader;
	Image healthHeader;
	Image enemiesLeftHeader;
	std::vector<Image> moveIcons;
	std::vector<Image> emptyMoveIcons;
	std::vector<Image> healthIcons;
	std::vector<Image> halfHealthIcons;
	std::vector<Image> emptyHealthIcons;
	
	Font* enemiesLeftFont;

	bool initialized;

public:
	Hud();
	~Hud();

	void initializeTexture(Graphics *graphics, TextureManager* fontTM);
	void setInitialPosition();
	void resetMovesHud();
	void update(float frameTime, Player* player, int enemiesLeft);
	void draw(int enemiesLeft);
	void drawEnemiesLeft(int enemiesLeft);
	void releaseAll();
	void resetAll();
};
#endif
