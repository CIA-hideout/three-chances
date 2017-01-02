#ifndef _THREECHANCES_H
#define _THREECHANCES_H
#define _WIN32_LEAN_AND_MEAN

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <queue>
#include <time.h>

#include "game.h"
#include "font.h"
#include "textureManager.h"
#include "entityConstants.h"

#include "levelGrid.h"
#include "entityGrid.h"
#include "gameControl.h"

#include "settings.h"
#include "hud.h"
#include "level.h"
#include "entity.h"
#include "player.h"
#include "duck.h"
#include "ghost.h"
#include "slug.h"
#include "moon.h"
#include "sword.h"

bool operator==(const Coordinates& lhs, const Coordinates& rhs);

class ThreeChances : public Game {
private:
	// Consts
	GameControl*	gameControl;
	EntityGrid*		entityGrid;
	LevelGrid*		levelGrid;
	Hud*			hud;
	Settings*		settings;

	GAME_MODE		gameMode;
	int				finalStageNo;
	int				stageNo;
	int				levelSize;
	int				levelCols;

	// Game items
	TextureManager	levelTexture;
	TextureManager	playerMaleTexture;
	TextureManager	duckTexture;
	TextureManager	ghostTexture;
	TextureManager	slugTexture;
	TextureManager	moonTexture;
	TextureManager	hudBgTexture;
	TextureManager	swordTexture;
	TextureManager	fontTexture;
	
	// Screens
	TextureManager	startScreenTexture;
	TextureManager  pauseScreenTexture;
	TextureManager	gameOverScreenTexture;
	TextureManager	gameClearScreenTexture;

	Image startScreen;
	Image pausedScreen;
	Image gameOverScreen;
	Image gameClearScreen;

	// Sprites
	Level	level;
	Player	player;
	Sword	sword;

	std::map<int, bool> keysPressed;
	std::map<int, bool> screenKeysPressed;
	int		lastKeyPressed;

	// audio
	bool startBtnPressed;
	XACT_CUE* startCue;
	bool muted;
	
public:
	// Constructor
	ThreeChances();

	// Destructor
	virtual ~ThreeChances();

	// Initialize the game
	void initialize(HWND hwnd);
	void update();      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();

	void clearEntities();
	void enemyAi();
	void restartGame();
	void initializeEntities();
	void incrementStage();
};

#endif
