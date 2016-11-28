#include "threechances.h"

//=============================================================================
// Constructor
//=============================================================================
ThreeChances::ThreeChances() {
	keysPressed[LEFT] = false;
	keysPressed[RIGHT] = false;
	keysPressed[UP] = false;
	keysPressed[DOWN] = false;

	gameControl = new GameControl;
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
	std::vector<Entity> enemyVector;

	Game::initialize(hwnd); // throws GameError

	// initialize map class
	levelGrid = new LevelGrid;
	levelGrid->initialize(1);

	// initialize monster grid
	monsterGrid = new MonsterGrid;

	// map texture
	if (!levelTexture.initialize(graphics, LEVEL_1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map texture"));

	if (!playerMaleTexture.initialize(graphics, PLAYER_MALE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing male texture"));

	if (!duckTexture.initialize(graphics, DUCK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing duck texture"));

	if (!ghostTexture.initialize(graphics, GHOST_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ghost texture"));

	if (!slugTexture.initialize(graphics, SLUG_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initialising slug texture"));

	if (!level.initialize(this, &levelTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map"));

	if (!player.initialize(this, TILE_SIZE, TILE_SIZE, PLAYER_COLS, &playerMaleTexture, PLAYER_DATA))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing male player"));

	if (!duck.initialize(this, TILE_SIZE, TILE_SIZE, DUCK_COLS, &duckTexture, DUCK_DATA))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing duck monster"));

	if (!ghost.initialize(this, TILE_SIZE, TILE_SIZE, GHOST_COLS, &ghostTexture, GHOST_DATA))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing duck monster"));

	if (!slug.initialize(this, TILE_SIZE, TILE_SIZE, SLUG_COLS, &slugTexture, SLUG_DATA))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initialising slug monster"));

	hud = new Hud;
	hud->initializeTexture(graphics);

	// Set map and hud to default scale and starting position
	level.setX(-(TILE_SIZE * SCALE * ((float)levelGrid->getStartTile().x - 3)));
	level.setY(-(TILE_SIZE * SCALE * ((float)levelGrid->getStartTile().y - 3)));

	player.setX(TILE_SIZE * SCALE * 3);
	player.setY(TILE_SIZE * SCALE * 3);

<<<<<<< HEAD
	duck.setX(TILE_SIZE * SCALE * 3);
	duck.setY(TILE_SIZE * SCALE * 0);

	ghost.setX(TILE_SIZE * SCALE * 4);
	ghost.setY(TILE_SIZE * SCALE * 0);

	slug.setX(TILE_SIZE * SCALE * 2);
	slug.setY(TILE_SIZE * SCALE * 0);
=======
	//duck.setX(TILE_SIZE * SCALE * 3);
	//duck.setY(TILE_SIZE * SCALE * 2);

	//duck.setX(TILE_SIZE * SCALE * 3);
	//duck.setY(TILE_SIZE * SCALE * 2);

	// x = 192, y = 128
	std::cout << "X: " << TILE_SIZE * SCALE * 3 << std::endl;
	std::cout << "Y: " << TILE_SIZE * SCALE * 2 << std::endl;

	monsterGrid->add(Coordinates(3, 27), 1);

	hud->setInitialPosition();
	monsterGrid->logLayout();

	return;
}

void resetKeysPressedMap(Input *input, std::map<int, bool> *keysPressed) {
	if (!input->isKeyDown(LEFT_KEY))
		(*keysPressed)[LEFT] = false;
	if (!input->isKeyDown(RIGHT_KEY))
		(*keysPressed)[RIGHT] = false;
	if (!input->isKeyDown(UP_KEY))
		(*keysPressed)[UP] = false;
	if (!input->isKeyDown(DOWN_KEY))
		(*keysPressed)[DOWN] = false;
}

int findKeyDown(std::map<int, bool> *keysPressed) {
	if ((*keysPressed)[LEFT])
		return LEFT;
	if ((*keysPressed)[RIGHT])
		return RIGHT;
	if ((*keysPressed)[UP])
		return UP;
	if ((*keysPressed)[DOWN])
		return DOWN;
	return -1;
}

//=============================================================================
// Update all game items
//=============================================================================
void ThreeChances::update() {
	// map will update last as player has to check
	// if next move is valid so as to play walking animation
	player.update(frameTime, levelGrid, input, &keysPressed, gameControl);
	level.update(levelGrid, &player, input, &keysPressed, gameControl);
	ghost.update(frameTime, levelGrid, player, input, &keysPressed);
	slug.update(frameTime, levelGrid, player, input, &keysPressed);
	duck.update(frameTime, monsterGrid);
	level.update(levelGrid, &player, input, &keysPressed, gameControl, monsterGrid);
	hud->update(frameTime, &player);

	//std::cout << static_cast<char>(gameControl->getGameState()) << std::endl;

	// Prevent long key press
	if (input->isKeyDown(LEFT_KEY) && !keysPressed[LEFT]) {
		keysPressed[LEFT] = true;
		lastKeyPressed = LEFT;
	}

	if (input->isKeyDown(RIGHT_KEY) && !keysPressed[RIGHT]) {
		keysPressed[RIGHT] = true;
		lastKeyPressed = RIGHT;
	}

	if (input->isKeyDown(UP_KEY) && !keysPressed[UP]) {
		keysPressed[UP] = true;
		lastKeyPressed = UP;
	}

	if (input->isKeyDown(DOWN_KEY) && !keysPressed[DOWN]) {
		keysPressed[DOWN] = true;
		lastKeyPressed = DOWN;
	}

	if (gameControl->getGameState() == GAME_STATE::enemy) {
		enemyAi(frameTime);
	}

	resetKeysPressedMap(input, &keysPressed);
}

void ThreeChances::enemyAi(float frameTime) {
	std::cout << "Running enemy AI" << std::endl;
	duck.ai(frameTime, &player, levelGrid, monsterGrid);

	player.resetMovesLeft();
	hud->resetMovesHud();
	gameControl->setGameState(GAME_STATE::player);
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void ThreeChances::ai() {
}

//=============================================================================
// Handle collisions
//=============================================================================
void ThreeChances::collisions() {}

//=============================================================================
// Render game items
//=============================================================================
void ThreeChances::render() {
	graphics->spriteBegin();                // begin drawing sprites

	level.draw();								// add the map to the scene
	player.draw();
	duck.draw();
	ghost.draw();
	slug.draw();
	hud->draw();

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void ThreeChances::releaseAll() {
	levelTexture.onLostDevice();
	playerMaleTexture.onLostDevice();
	duckTexture.onLostDevice();
	ghostTexture.onLostDevice();
	slugTexture.onLostDevice();

	hud->releaseAll();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void ThreeChances::resetAll() {
	levelTexture.onResetDevice();
	playerMaleTexture.onResetDevice();
	duckTexture.onResetDevice();
	ghostTexture.onResetDevice();
	slugTexture.onResetDevice();

	hud->resetAll();
	Game::resetAll();
	return;
}
