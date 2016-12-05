#ifndef _THREECHANCES_H
#define _THREECHANCES_H
#define _WIN32_LEAN_AND_MEAN

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include "game.h"
#include "font.h"
#include "textureManager.h"
#include "entityConstants.h"

#include "levelGrid.h"
#include "monsterGrid.h"
#include "gameControl.h"

#include "hud.h"
#include "level.h"
#include "entity.h"
#include "player.h"
#include "duck.h"
#include "ghost.h"
#include "slug.h"
#include "sword.h"

class ThreeChances : public Game {
private:
	// Consts
	GameControl*	gameControl;
	LevelGrid*		levelGrid;
	MonsterGrid*	monsterGrid;
	Hud*			hud;

	// Game items
	TextureManager	levelTexture;
	TextureManager	playerMaleTexture;
	TextureManager	duckTexture;
	TextureManager	ghostTexture;
	TextureManager	slugTexture;
	TextureManager	hudBgTexture;
	TextureManager	swordTexture;
	TextureManager	fontTexture;

	// Sprites
	Level			level;
	Player			player;
	Sword			sword;
	Duck			duck;
	//Ghost			ghost;
	Slug			slug;
	Image			movesHeader;

	Font*			titleFont;
	Font*			secondaryTitleFont;

	std::map<int, bool> keysPressed;
	int				lastKeyPressed;

public:
	// Constructor
	ThreeChances();

	// Destructor
	virtual ~ThreeChances();

	// Initialize the game
	void initialize(HWND hwnd);
	void initializeFonts();
	void initializeMonsters();
	void update();      // must override pure virtual from Game
	void enemyAi();
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();
};

#endif
