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

	// Legend
	// 0 - border
	// 1 - 1st floor path
	// 2 - 2nd floor path
	// 3 - stairs
	// 4 - water
	// 5 - obstacle
	// 6 - blockage

	std::vector<std::vector<int>> layout = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0 },
		{ 0, 0, 0, 4, 4, 5, 2, 2, 2, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 5, 0, 0, 0 },
		{ 0, 0, 0, 4, 4, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 4, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 6, 6, 6, 6, 0, 0, 0 },
		{ 0, 0, 0, 4, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 6, 6, 6, 6, 0, 0, 0 },
		{ 0, 0, 0, 4, 5, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 4, 5, 2, 2, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 1, 1, 1, 1, 1, 4, 4, 5, 2, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 1, 1, 1, 1, 1, 4, 4, 5, 2, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 1, 1, 1, 1, 1, 4, 4, 5, 2, 2, 5, 5, 5, 5, 5, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 1, 1, 1, 1, 1, 4, 4, 5, 2, 2, 5, 1, 5, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 4, 5, 2, 2, 5, 4, 4, 1, 1, 1, 1, 1, 4, 4, 5, 2, 2, 5, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 5, 5, 2, 2, 5, 4, 4, 4, 4, 1, 4, 4, 4, 4, 5, 2, 2, 5, 1, 1, 1, 5, 5, 5, 5, 5, 0, 0, 0 },
		{ 0, 0, 0, 1, 5, 2, 2, 5, 4, 4, 4, 4, 1, 4, 4, 4, 4, 5, 2, 2, 5, 1, 1, 1, 5, 5, 5, 5, 5, 0, 0, 0 },
		{ 0, 0, 0, 1, 5, 3, 3, 5, 4, 4, 4, 4, 1, 1, 4, 4, 4, 5, 2, 2, 5, 1, 1, 1, 5, 5, 5, 5, 5, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 4, 4, 4, 5, 2, 2, 5, 1, 1, 1, 5, 5, 5, 5, 5, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 4, 4, 1, 5, 2, 2, 5, 1, 1, 1, 5, 5, 5, 5, 5, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 1, 1, 1, 1, 5, 2, 2, 5, 1, 1, 1, 1, 1, 5, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 5, 2, 2, 5, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 1, 5, 1, 4, 4, 4, 4, 1, 1, 1, 5, 2, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 1, 1, 1, 5, 2, 2, 2, 2, 2, 2, 5, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 5, 1, 4, 4, 4, 4, 4, 1, 1, 1, 5, 5, 5, 5, 5, 3, 3, 5, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 5, 5, 1, 1, 1, 4, 4, 4, 4, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 5, 1, 1, 1, 1, 4, 4, 4, 4, 1, 5, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	std::vector<int> startTile = { 5, 28 };
	std::vector<int> endTile = { 16, 4 };

	stage->initialize(layout, startTile, endTile);

	// map texture
	if (!mapTexture.initialize(graphics, MAP_1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map texture"));

	if (!playerMaleTexture.initialize(graphics, PLAYER_MALE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing male texture"));

	if (!map.initialize(graphics, 0, 0, 0, &mapTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map"));

	if (!playerMale.initialize(graphics, TILE_SIZE, TILE_SIZE, 3, &playerMaleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing male player"));

	// Set map to default scale and starting position
	map.setScale((float)SCALE);
	map.setX(-(TILE_SIZE * SCALE * 2));
	map.setY(-(TILE_SIZE * SCALE * 25));

	playerMale.setScale((float)SCALE);
	playerMale.setX(TILE_SIZE * SCALE * 3);
	playerMale.setY(TILE_SIZE * SCALE * 3);

	// Set initial male position, should follow grid later
	playerMale.setLoop(false);
	playerMale.setFrames(PLAYER_START_FRAME, PLAYER_END_FRAME);	// animation frames
	playerMale.setFrameDelay(PLAYER_ANIMATION_DELAY);
	playerMale.setCurrentFrame(3);

	map.setScale(SCALE);
	map.setX(-(TILE_SIZE * SCALE * (startTile[0] - 3)));
	map.setY(-(TILE_SIZE * SCALE * (startTile[1] - 3)));

	std::cout << "X: " << map.getX() << " Y: " << map.getY() << " Tile: " << stage->getCurrentTileType() << std::endl;
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

void rotatePlayer(Image *player, std::string direction) {
	RECT sampleRect = player->getSpriteDataRect();

	if (direction != "") {
		sampleRect.left = 0;
		sampleRect.right = TILE_SIZE;

		if (direction == "LEFT")
			sampleRect.top = 32;
		if (direction == "RIGHT")
			sampleRect.top = 96;
		if (direction == "UP")
			sampleRect.top = 64;
		if (direction == "DOWN")
			sampleRect.top = 0;

		sampleRect.bottom = sampleRect.top + TILE_SIZE;
		player->setCurrentFrame(0);
	}

	player->setSpriteDataRect(sampleRect);
}

//=============================================================================
// Update all game items
//=============================================================================
void ThreeChances::update() {
	// make the map move at a certain velocity, trigger player animation at that time
	// switch the sprites and align them

	if (input->isKeyDown(LEFT_KEY) && !keysPressed["LEFT"]) {
		keysPressed["LEFT"] = true;
		lastKeyPressed = "LEFT";

		if (map.getX() < 0) {
			map.setX(map.getX() + TILE_SIZE * SCALE);
			stage->moveCurrentTile(LEFT);
			std::cout << "X: " << map.getX() << " Y: " << map.getY() << " Tile: " << stage->getCurrentTileType() << std::endl;
		}

		rotatePlayer(&playerMale, findKeyDown(&keysPressed));
	}

	if (input->isKeyDown(RIGHT_KEY) && !keysPressed["RIGHT"]) {
		keysPressed["RIGHT"] = true;
		lastKeyPressed = "RIGHT";

		if (-map.getX() < map.getWidth() * SCALE - GAME_WIDTH) {
			map.setX(map.getX() - TILE_SIZE * SCALE);
			stage->moveCurrentTile(RIGHT);
			std::cout << "X: " << map.getX() << " Y: " << map.getY() << " Tile: " << stage->getCurrentTileType() << std::endl;
		}

		rotatePlayer(&playerMale, findKeyDown(&keysPressed));
	}

	if (input->isKeyDown(UP_KEY) && !keysPressed["UP"]) {
		keysPressed["UP"] = true;
		lastKeyPressed = "UP";

		if (map.getY() < 0) {
			map.setY(map.getY() + TILE_SIZE * SCALE);
			stage->moveCurrentTile(UP);
			std::cout << "X: " << map.getX() << " Y: " << map.getY() << " Tile: " << stage->getCurrentTileType() << std::endl;
		}

		rotatePlayer(&playerMale, findKeyDown(&keysPressed));
	}

	if (input->isKeyDown(DOWN_KEY) && !keysPressed["DOWN"]) {
		keysPressed["DOWN"] = true;
		lastKeyPressed = "DOWN";

		if (-map.getY() < map.getHeight() * SCALE - GAME_HEIGHT) {
			map.setY(map.getY() - TILE_SIZE * SCALE);
			stage->moveCurrentTile(DOWN);
			std::cout << "X: " << map.getX() << " Y: " << map.getY() << " Tile: " << stage->getCurrentTileType() << std::endl;
		}

		rotatePlayer(&playerMale, findKeyDown(&keysPressed));
	}

	resetKeysPressedMap(input, &keysPressed);
	playerMale.update(frameTime);
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
	playerMale.draw();

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void ThreeChances::releaseAll() {
	mapTexture.onLostDevice();
	playerMaleTexture.onLostDevice();

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

	Game::resetAll();
	return;
}
