#ifndef _THREECHANCES_H
#define _THREECHANCES_H
#define _WIN32_LEAN_AND_MEAN

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "map.h"

class ThreeChances : public Game {
private:
	// Game items
	TextureManager mapTexture;
	TextureManager playerMaleTexture;
	Image		   map;
	Image		   playerMale;
	std::map<std::string, bool> keysPressed;
	std::string	   lastKeyPressed;
	Map*		   level;
	float		   velocity;

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
