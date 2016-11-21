#include "threechances.h"
#include <iostream>

//=============================================================================
// Constructor
//=============================================================================
ThreeChances::ThreeChances() {
	keysPressed["LEFT"] = false;
	keysPressed["RIGHT"] = false;
	keysPressed["UP"] = false;
	keysPressed["DOWN"] = false;
}

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
	malePlayer.setFrames(PLAYER_START_FRAME, PLAYER_END_FRAME);	// animation frames
	malePlayer.setCurrentFrame(PLAYER_START_FRAME);				// starting frame
	malePlayer.setFrameDelay(PLAYER_ANIMATION_DELAY);
	
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void cleanKeys(Input *input, std::map<std::string, bool> *keysPressed) {
	if (!input->isKeyDown(LEFT_KEY)) 
		(*keysPressed)["LEFT"] = false;
	if (!input->isKeyDown(RIGHT_KEY)) 
		(*keysPressed)["RIGHT"] = false;
	if (!input->isKeyDown(UP_KEY)) 
		(*keysPressed)["UP"] = false;
	if (!input->isKeyDown(DOWN_KEY))
		(*keysPressed)["DOWN"] = false;
}

//std::string findKeyDown(std::map<std::string, bool> *keysPressed) {
//	if ((*keysPressed)["LEFT"])
//		return "LEFT";
//	if ((*keysPressed)["RIGHT"])
//		return "RIGHT";
//	if ((*keysPressed)["UP"])
//		return "UP";
//	if ((*keysPressed)["DOWN"])
//		return "DOWN";
//	return "";
//}

void ThreeChances::update() {
	// make the map move at a certain velocity, trigger player animation at that time
	// switch the sprites and align them

	if (input->isKeyDown(LEFT_KEY) && !keysPressed["LEFT"]) {
		keysPressed["LEFT"] = true;
		lastKeyPressed = "LEFT";
		if (map.getX() < 0)
			map.setX(map.getX() + TILE_SIZE * SCALE);

	}

	if (input->isKeyDown(RIGHT_KEY) && !keysPressed["RIGHT"]) {
		keysPressed["RIGHT"] = true;
		lastKeyPressed = "RIGHT";
		if (-map.getX() < map.getWidth() * SCALE - GAME_WIDTH)
			map.setX(map.getX() - TILE_SIZE * SCALE);
	}

	if (input->isKeyDown(UP_KEY) && !keysPressed["UP"]) {
		keysPressed["UP"] = true;
		lastKeyPressed = "UP";
		if (map.getY() < 0)
			map.setY(map.getY() + TILE_SIZE * SCALE);
	}

	if (input->isKeyDown(DOWN_KEY) && !keysPressed["DOWN"]) {
		keysPressed["DOWN"] = true;
		lastKeyPressed = "DOWN";
		if (-map.getY() < map.getHeight() * SCALE - GAME_HEIGHT)
			map.setY(map.getY() - TILE_SIZE * SCALE);
	}



	cleanKeys(input, &keysPressed);
	//std::cout << findKeyDown(&keysPressed);
	malePlayer.update(frameTime, lastKeyPressed);
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