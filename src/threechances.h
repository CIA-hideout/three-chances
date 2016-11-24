#ifndef _THREECHANCES_H
#define _THREECHANCES_H
#define _WIN32_LEAN_AND_MEAN

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include "game.h"
#include "image.h"
#include "stage.h"
#include "entityConstants.h"
#include "textureManager.h"
#include "image.h"

#include "player.h"
#include "duck.h"

class ThreeChances : public Game {
private:
	// Game items
	TextureManager mapTexture;
	TextureManager playerMaleTexture;
	TextureManager duckTexture;

	Image		   map;
	Player		   player;
	Duck		   duck;
	std::map<std::string, bool> keysPressed;
	std::string	   lastKeyPressed;
	Stage*		   stage;

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
