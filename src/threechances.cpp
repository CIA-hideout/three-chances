#include "threechances.h"
#include <string>

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

	// map texture
	if (!mapTexture.initialize(graphics, MAP_1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map texture"));

	// map
	if (!map.initialize(graphics, 0, 0, 0, &mapTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map"));

	map.setScale(SCALE);
	map.setX(-(TILE_SIZE * 2));
	map.setY(-(TILE_SIZE * 25));

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void ThreeChances::update() {
	if (input->wasKeyPressed(RIGHT_KEY)) {
		if (-map.getX() < map.getWidth() * SCALE - GAME_WIDTH)
			map.setX(map.getX() - TILE_SIZE);
	}
	if (input->wasKeyPressed(LEFT_KEY)) {
		if (map.getX() < 0)
			map.setX(map.getX() + TILE_SIZE);
	}
	if (input->wasKeyPressed(UP_KEY)) {
		if (map.getY() < 0)
			map.setY(map.getY() + TILE_SIZE);
	}
	if (input->wasKeyPressed(DOWN_KEY)) {
		if (-map.getY() < map.getHeight() * SCALE - GAME_HEIGHT)
			map.setY(map.getY() - TILE_SIZE);
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

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void ThreeChances::releaseAll() {
	mapTexture.onLostDevice();

	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void ThreeChances::resetAll() {
	mapTexture.onResetDevice();

	Game::resetAll();
	return;
}