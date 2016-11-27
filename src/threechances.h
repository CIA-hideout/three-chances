#ifndef _THREECHANCES_H
#define _THREECHANCES_H
#define _WIN32_LEAN_AND_MEAN

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include "entityConstants.h"
#include "game.h"
#include "gameControl.h"
#include "levelGrid.h"
#include "hud.h"
#include "textureManager.h"
#include "level.h"
#include "player.h"
#include "duck.h"
#include "ghost.h"
#include "slug.h"

class ThreeChances : public Game {
private:
	// Consts
	GameControl*   gameControl;
	LevelGrid*	   levelGrid;
	Hud*		   hud;

	// Game items
	TextureManager levelTexture;
	TextureManager playerMaleTexture;
	TextureManager duckTexture;
	TextureManager ghostTexture;
	TextureManager slugTexture;
	TextureManager hudBgTexture;

	Level		   level;
	Player		 player;
	Duck		   duck;
	Ghost		   ghost;
	Slug		   slug;

	Image		   hudBg;
	std::map<std::string, bool> keysPressed;
	std::string	   lastKeyPressed;

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
};

#endif
