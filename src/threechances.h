#ifndef _THREECHANCES_H
#define _THREECHANCES_H
#define _WIN32_LEAN_AND_MEAN

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include "game.h"
#include "entityConstants.h"
#include "textureManager.h"
#include "levelGrid.h"
#include "level.h"
#include "player.h"
#include "duck.h"

class ThreeChances : public Game {
private:
	// Game items
	TextureManager levelTexture;
	TextureManager playerMaleTexture;
	TextureManager duckTexture;

	Level		   level;
	Player		   player;
	Duck		   duck;
	std::map<std::string, bool> keysPressed;
	std::string	   lastKeyPressed;
	LevelGrid*	   levelGrid;

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
