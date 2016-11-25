#include "threechances.h"

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

	// initialize map class
	stage = new Stage;
	stage->initialize(1);

	// map texture
	if (!mapTexture.initialize(graphics, MAP_1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map texture"));

	if (!playerMaleTexture.initialize(graphics, PLAYER_MALE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing male texture"));

	if (!duckTexture.initialize(graphics, DUCK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing duck texture"));

	if (!map.initialize(graphics, 0, 0, 0, &mapTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map"));

	if (!player.initialize(this, TILE_SIZE, TILE_SIZE, PLAYER_COLS, &playerMaleTexture, PLAYER_DATA))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing male player"));

	if (!duck.initialize(this, TILE_SIZE, TILE_SIZE, DUCK_COLS, &duckTexture, DUCK_DATA))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing duck monster"));

	// Set map to default scale and starting position
	map.setScale((float)SCALE);
	map.setX(-(TILE_SIZE * SCALE * ((float)stage->getStartTile().x - 3)));
	map.setY(-(TILE_SIZE * SCALE * ((float)stage->getStartTile().y - 3)));

	player.setScale((float)SCALE);
	player.setX(TILE_SIZE * SCALE * 3);
	player.setY(TILE_SIZE * SCALE * 3);

	duck.setScale((float)SCALE);
	duck.setX(TILE_SIZE * SCALE * 3);
	duck.setY(TILE_SIZE * SCALE * 2);

	return;
}

void resetKeysPressedMap(Input *input, std::map<std::string, bool> *keysPressed) {
	if (!input->isKeyDown(LEFT_KEY))
		(*keysPressed)["LEFT"] = false;
	if (!input->isKeyDown(RIGHT_KEY)) 
		(*keysPressed)["RIGHT"] = false;
	if (!input->isKeyDown(UP_KEY))
		(*keysPressed)["UP"] = false;
	if (!input->isKeyDown(DOWN_KEY))
		(*keysPressed)["DOWN"] = false;
}

std::string findKeyDown(std::map<std::string, bool> *keysPressed) {
	if ((*keysPressed)["LEFT"])
		return "LEFT";
	if ((*keysPressed)["RIGHT"])
		return "RIGHT";
	if ((*keysPressed)["UP"])
		return "UP";
	if ((*keysPressed)["DOWN"])
		return "DOWN";
	return "";
}

//=============================================================================
// Update all game items
//=============================================================================
void ThreeChances::update() {
	if (input->isKeyDown(LEFT_KEY) && !keysPressed["LEFT"]) {
		keysPressed["LEFT"] = true;
		lastKeyPressed = "LEFT";

		if (map.getX() < 0) {
			map.setX(map.getX() + TILE_SIZE * SCALE);
			stage->moveCurrentTile(LEFT);
			stage->logTile(map.getX(), map.getY());
		}
	}

	if (input->isKeyDown(RIGHT_KEY) && !keysPressed["RIGHT"]) {
		keysPressed["RIGHT"] = true;
		lastKeyPressed = "RIGHT";

		if (-map.getX() < map.getWidth() * SCALE - GAME_WIDTH) {
			map.setX(map.getX() - TILE_SIZE * SCALE);
			stage->moveCurrentTile(RIGHT);
			stage->logTile(map.getX(), map.getY());
		}
	}

	if (input->isKeyDown(UP_KEY) && !keysPressed["UP"]) {
		keysPressed["UP"] = true;
		lastKeyPressed = "UP";

		if (map.getY() < 0) {
			map.setY(map.getY() + TILE_SIZE * SCALE);
			stage->moveCurrentTile(UP);
			stage->logTile(map.getX(), map.getY());
		}
	}

	if (input->isKeyDown(DOWN_KEY) && !keysPressed["DOWN"]) {
		keysPressed["DOWN"] = true;
		lastKeyPressed = "DOWN";

		if (-map.getY() < map.getHeight() * SCALE - GAME_HEIGHT) {
			map.setY(map.getY() - TILE_SIZE * SCALE);
			stage->moveCurrentTile(DOWN);
			stage->logTile(map.getX(), map.getY());
		}
	}

	resetKeysPressedMap(input, &keysPressed);
	player.update(frameTime, input, &keysPressed);
	duck.update(frameTime);
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
	player.draw();
	duck.draw();

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void ThreeChances::releaseAll() {
	mapTexture.onLostDevice();
	playerMaleTexture.onLostDevice();
	duckTexture.onLostDevice();

	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void ThreeChances::resetAll() {
	mapTexture.onResetDevice();
	playerMaleTexture.onResetDevice();
	duckTexture.onResetDevice();

	Game::resetAll();
	return;
}
