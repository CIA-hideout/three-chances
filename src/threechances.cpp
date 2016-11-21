#include "threechances.h"
#include <iostream>

//=============================================================================
// Constructor
//=============================================================================
ThreeChances::ThreeChances() {}

//=============================================================================
// Destructor
//=============================================================================
ThreeChances::~ThreeChances() {
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void ThreeChances::initialize(HWND hwnd) {
	Game::initialize(hwnd); // throws GameError

	if (!mapTexture.initialize(graphics, MAP_1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map texture"));

	if (!malePlayerTexture.initialize(graphics, MALE_PLAYER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing male texture"));

	if (!map.initialize(graphics, 0, 0, 0, &mapTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map"));

	if (!malePlayer.initialize(graphics, TILE_SIZE, TILE_SIZE, 3, &malePlayerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing male player"));

	// Set map to default scale and starting position
	map.setScale((float)SCALE);
	map.setX(-(TILE_SIZE * SCALE * 2));
	map.setY(-(TILE_SIZE * SCALE * 25));

	malePlayer.setScale((float)SCALE);
	malePlayer.setX(TILE_SIZE * SCALE * 3);
	malePlayer.setY(TILE_SIZE * SCALE * 3);
	
	// Set initial male position, should follow grid later
	//std::cout << 

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void ThreeChances::update() {
	if (input->wasKeyPressed(RIGHT_KEY)) {
		if (-map.getX() < map.getWidth() * SCALE - GAME_WIDTH)
			map.setX(map.getX() - TILE_SIZE * SCALE);
	}
	if (input->wasKeyPressed(LEFT_KEY)) {
		if (map.getX() < 0)
			map.setX(map.getX() + TILE_SIZE * SCALE);
	}
	if (input->wasKeyPressed(UP_KEY)) {
		if (map.getY() < 0)
			map.setY(map.getY() + TILE_SIZE * SCALE);
	}
	if (input->wasKeyPressed(DOWN_KEY)) {
		if (-map.getY() < map.getHeight() * SCALE - GAME_HEIGHT)
			map.setY(map.getY() - TILE_SIZE * SCALE);
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void ThreeChances::ai() {}

//=============================================================================
// Handle collisions
//=============================================================================
void ThreeChances::collisions() {}

//=============================================================================
// Render game items
//=============================================================================
void ThreeChances::render() {
	graphics->spriteBegin();                // begin drawing sprites

	map.draw();								// add the map to the scene
	malePlayer.draw();

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void ThreeChances::releaseAll() {
	mapTexture.onLostDevice();
	malePlayerTexture.onLostDevice();

	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void ThreeChances::resetAll() {
	mapTexture.onResetDevice();
	malePlayerTexture.onResetDevice();

	Game::resetAll();
	return;
}