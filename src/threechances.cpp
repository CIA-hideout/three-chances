#include "threechances.h"

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

void resetScreenKeysPressedMap(Input *input, std::map<int, bool> *keysPressed) {
	if (!input->isKeyDown(SPACE_KEY))
		(*keysPressed)[SPACE] = false;
	if (!input->isKeyDown(ESC_KEY))
		(*keysPressed)[ESC] = false;
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
// Constructor
//=============================================================================
ThreeChances::ThreeChances() {
	keysPressed[LEFT] = false;
	keysPressed[RIGHT] = false;
	keysPressed[UP] = false;
	keysPressed[DOWN] = false;

	screenKeysPressed[ESC] = false;
	screenKeysPressed[SPACE] = false;

	gameControl = new GameControl;
}

//=============================================================================
// Destructor
//=============================================================================
ThreeChances::~ThreeChances() {
	releaseAll();
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void ThreeChances::initialize(HWND hwnd) {
	std::vector<Entity> enemyVector;

	Game::initialize(hwnd);
	graphics->setBackColor(graphicsNS::BLACK);

	// initialize level grid
	levelGrid = new LevelGrid;
	levelGrid->initialize(1);

	// initialize entity grid
	entityGrid = new EntityGrid;

	// game screens
	if (!startScreenTexture.initialize(graphics, START_SCREEN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing startScreen texture"));

	if (!pauseScreenTexture.initialize(graphics, PAUSE_SCREEN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pauseScreen texture"));

	if (!gameOverScreenTexture.initialize(graphics, GAME_OVER_SCREEN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gameOverScreen texture"));

	if (!gameClearScreenTexture.initialize(graphics, GAME_CLEAR_SCREEN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gameClearScreen texture"));

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
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing slug texture"));

	if (!moonTexture.initialize(graphics, MOON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing moon texture"));

	if (!swordTexture.initialize(graphics, SWORD_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sword texture"));

	if (!fontTexture.initialize(graphics, FONT_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing font texture"));

	if (!level.initialize(this, LEVEL_SIZE, LEVEL_SIZE, LEVEL_COLS, &levelTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map"));

	if (!player.initialize(this, TILE_SIZE, TILE_SIZE, PLAYER_COLS, &playerMaleTexture, PLAYER_DATA))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing male player"));

	if (!sword.initialize(this, SWORD_WIDTH, SWORD_HEIGHT, SWORD_COLS, &swordTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sword"));

	// Initialize screens
	startScreen.initialize(graphics, 0, 0, 0, &startScreenTexture);
	pausedScreen.initialize(graphics, 0, 0, 0, &pauseScreenTexture);
	gameOverScreen.initialize(graphics, 0, 0, 0, &gameOverScreenTexture);
	gameClearScreen.initialize(graphics, 0, 0, 0, &gameClearScreenTexture);

	startScreen.setScale(SCALE_2X);
	pausedScreen.setScale(SCALE_2X);
	gameOverScreen.setScale(SCALE_2X);
	gameClearScreen.setScale(SCALE_2X);

	pausedScreen.setX(GAME_WIDTH / 2 - PAUSE_SCREEN_WIDTH / 2);
	pausedScreen.setY(GAME_HEIGHT / 2 - PAUSE_SCREEN_HEIGHT / 2);

	hud = new Hud;
	hud->initializeTexture(graphics, &fontTexture);

	this->initializeEntities();
	hud->setInitialPosition();

	return;
}

void ThreeChances::restartGame() {
	// Clear mv
	std::vector<Entity*> mv;
	gameControl->setGameState(GAME_STATE::player);
	gameControl->setMonsterVec(mv);

	// initialize level grid
	levelGrid = new LevelGrid;
	levelGrid->initialize(1);

	// initialize entity grid
	entityGrid = new EntityGrid;

	player.setHealth(PLAYER_DATA.health);
	player.setMovesLeft(PLAYER_DATA.moves);
	player.setAnimating(false);

	level.setX(levelNS::X);
	level.setY(levelNS::Y);

	hud->resetMovesHud();
	hud->resetHealthHud();
	this->initializeEntities();
}

std::vector<Entity*> setInitPos(std::vector<Entity*> mv, EntityGrid* entityGrid,
	Entity* entity, Coordinates currentTile, Coordinates startCoord) {

	entityGrid->addEntity(startCoord, entity->getId());
	Position startPos = entityGrid->getEntityPosition(entity->getId());
	entity->setX(startPos.x);
	entity->setY(startPos.y);
	mv.push_back(entity);
	return mv;
}

void ThreeChances::initializeEntities() {
	// Add to entity grid
	entityGrid->addEntity(levelGrid->getStartTile(), PLAYER_ID);

	std::vector<Entity*> mv = gameControl->getMonsterVec();

	Entity *tempMonster;

	for (size_t i = 0; i < DUCK_START_COORDS.size(); i++) {
		tempMonster = new Duck;
		tempMonster->initialize(this, TILE_SIZE, TILE_SIZE, DUCK_COLS, &duckTexture, DUCK_DATA);
		mv = setInitPos(mv, entityGrid, tempMonster, entityGrid->getPlayerCoordinates(), DUCK_START_COORDS[i]);
	}

	for (size_t i = 0; i < GHOST_START_COORDS.size(); i++) {
		tempMonster = new Ghost;
		tempMonster->initialize(this, TILE_SIZE, TILE_SIZE, GHOST_COLS, &ghostTexture, GHOST_DATA);
		mv = setInitPos(mv, entityGrid, tempMonster, entityGrid->getPlayerCoordinates(), GHOST_START_COORDS[i]);
	}

	for (size_t i = 0; i < MOON_START_COORDS.size(); i++) {
		tempMonster = new Moon;
		tempMonster->initialize(this, TILE_SIZE, TILE_SIZE, MOON_COLS, &moonTexture, MOON_DATA);
		mv = setInitPos(mv, entityGrid, tempMonster, entityGrid->getPlayerCoordinates(), MOON_START_COORDS[i]);
	}

	gameControl->setPlayer(&player);
	gameControl->setMonsterVec(mv);
}

//=============================================================================
// Update all game items
//=============================================================================
void ThreeChances::update() {
	GENERAL_STATE gs = gameControl->getGeneralState();
	std::vector<Entity*> mv = gameControl->getMonsterVec();

	switch (gs) {
		case GENERAL_STATE::menu: {
		if (input->isKeyDown(SPACE_KEY) && !screenKeysPressed[SPACE]) {
				gameControl->setGeneralState(GENERAL_STATE::game);
				screenKeysPressed[SPACE] = true;
				PlaySound(START_GAME_SOUND, NULL, SND_SYNC);				
			}
		} break;
		case GENERAL_STATE::paused: {
			if (input->isKeyDown(SPACE_KEY) && !screenKeysPressed[SPACE]) {
				gameControl->setGeneralState(GENERAL_STATE::game);
				screenKeysPressed[SPACE] = true;
				PlaySound(UNPAUSE_SOUND, NULL, SND_ASYNC);
			}
		} break;
		case GENERAL_STATE::gameOver: {
			if (input->isKeyDown(SPACE_KEY) && !screenKeysPressed[SPACE]) {
				gameControl->setGeneralState(GENERAL_STATE::menu);
				this->restartGame();
				screenKeysPressed[SPACE] = true;
				PlaySound(CLICK_SOUND, NULL, SND_ASYNC);
			}
		} break;
		case GENERAL_STATE::gameClear: {
			if (input->isKeyDown(SPACE_KEY) && !screenKeysPressed[SPACE]) {
				gameControl->setGeneralState(GENERAL_STATE::menu);
				this->restartGame();
				screenKeysPressed[SPACE] = true;
				PlaySound(CLICK_SOUND, NULL, SND_ASYNC);
			}
		} break;
		case GENERAL_STATE::game: {
			if (input->isKeyDown(ESC_KEY) && !screenKeysPressed[ESC]) {
				gameControl->setGeneralState(GENERAL_STATE::paused);
				screenKeysPressed[ESC] = true;
				PlaySound(PAUSE_SOUND, NULL, SND_ASYNC);
			}

			// Check no animation currently running
			if (!player.getAnimating()) {
				gameControl->cleanupEnemy(entityGrid);

				// Check if it's player's turn
				if (gameControl->getGameState() == GAME_STATE::player) {
					float endPoint;

					if (input->isKeyDown(LEFT_KEY) && !keysPressed[LEFT]) {
						keysPressed[LEFT] = true;
						lastKeyPressed = LEFT;
						endPoint = level.getX() + TILE_SIZE * SCALE;
						player.moveInDirection(levelGrid, entityGrid, LEFT, endPoint, gameControl);
						sword.setDirection(LEFT, player.getX(), player.getY());
					}

					if (input->isKeyDown(RIGHT_KEY) && !keysPressed[RIGHT]) {
						keysPressed[RIGHT] = true;
						lastKeyPressed = RIGHT;
						endPoint = level.getX() - TILE_SIZE * SCALE;
						player.moveInDirection(levelGrid, entityGrid, RIGHT, endPoint, gameControl);
						sword.setDirection(RIGHT, player.getX(), player.getY());
					}

					if (input->isKeyDown(UP_KEY) && !keysPressed[UP]) {
						keysPressed[UP] = true;
						lastKeyPressed = UP;
						endPoint = level.getY() + TILE_SIZE * SCALE;
						player.moveInDirection(levelGrid, entityGrid, UP, endPoint, gameControl);
						sword.setDirection(UP, player.getX(), player.getY());
					}

					if (input->isKeyDown(DOWN_KEY) && !keysPressed[DOWN]) {
						keysPressed[DOWN] = true;
						lastKeyPressed = DOWN;
						endPoint = level.getY() - TILE_SIZE * SCALE;
						player.moveInDirection(levelGrid, entityGrid, DOWN, endPoint, gameControl);
						sword.setDirection(DOWN, player.getX(), player.getY());
					}
				}
				// Enemy's turn
				else {
					enemyAi();
				}
			}
			// Animates sprites for player turn
			else {
				int oppDirection = -1;
				// player direction is set in player.cpp
				if (player.getAction() == LEFT)
					oppDirection = RIGHT;
				else if (player.getAction() == RIGHT)
					oppDirection = LEFT;
				else if (player.getAction() == UP)
					oppDirection = DOWN;
				else if (player.getAction() == DOWN)
					oppDirection = UP;

				// If action is a movement
				if (player.getAction() != ATTACK) {
					if (level.moveInDirection(frameTime, oppDirection, player.getEndPoint())) {
						level.finishAnimating(levelGrid, &player);
						levelGrid->logTile(entityGrid->getPlayerCoordinates(), level.getX(), level.getY());

						if (entityGrid->getPlayerCoordinates() == STAGE_1_END_TILE)
							gameControl->setGeneralState(GENERAL_STATE::gameClear);
					}
				}
				// If action is ATTACK
				else {
					sword.setVisible(true);
					if (sword.attack(frameTime)) {
						sword.finishAnimating(&player);
					}
				}

				for (size_t i = 0; i < mv.size(); i++) {
					mv[i]->moveInDirection(frameTime, oppDirection, entityGrid->getEntityPosition(mv[i]->getId()));
				}
			}

			// Remove blockage on level if monsters left == 0
			if (gameControl->getMonstersLeft() == 0 && level.getPathBlocked()) {
				level.removeBlockage();
				levelGrid->removeBlockage();
			}

			// Update and reset
			for (size_t i = 0; i < mv.size(); i++) {
				mv[i]->update(frameTime);
			}
			player.update(frameTime, gameControl);
			hud->update(frameTime, &player, gameControl->getMonstersLeft());

			resetKeysPressedMap(input, &keysPressed);
		} break;
	}

	resetScreenKeysPressedMap(input, &screenKeysPressed);
}

void ThreeChances::enemyAi() {
	std::vector<Entity*> mv = gameControl->getMonsterVec();
	std::queue<Entity*> aq = gameControl->getAnimationQueue();
	Entity *entityPtr;

	if (!gameControl->getEnemyAiInitialized() && mv.size() > 0) {
		for (size_t i = 0; i < mv.size(); i++) {
			aq.push(mv[i]);
		}

		gameControl->setEnemyAiInitialized(true);
	}

	if (gameControl->getEnemyAiInitialized()) {
		entityPtr = aq.front();
		if (entityPtr->getMovesLeft() > 0) {
			if (!entityPtr->getAnimating()) {
				entityPtr->initAi(entityGrid, levelGrid);

				if (entityPtr->getAction() == ATTACK) {
					gameControl->damagePlayer(entityPtr->getId());
				}
			}
			else {
				entityPtr->animateAi(frameTime, entityGrid);
			}
		} else {
			aq.pop();
		}
	}

	if (gameControl->checkMonstersMovesCompleted()) {
		// Reset moves
		for (size_t i = 0; i < mv.size(); i++) {
			mv[i]->resetMovesLeft();
		}

		player.resetMovesLeft();
		hud->resetMovesHud();

		// Update game state
		gameControl->setGameState(GAME_STATE::player);
		gameControl->setEnemyAnimating(false);
		gameControl->setEnemyAiInitialized(false);
	}
	else {
		gameControl->setEnemyAnimating(true);
	}

	gameControl->setAnimationQueue(aq);
}

void ThreeChances::ai() {}

void ThreeChances::collisions() {}

//=============================================================================
// Render game items
//=============================================================================
void ThreeChances::render() {
	graphics->spriteBegin();
	std::vector<Entity*> mv = gameControl->getMonsterVec();

	switch (gameControl->getGeneralState()) {
		case GENERAL_STATE::menu: {
			startScreen.draw();
		} break;
		case GENERAL_STATE::paused: {
			pausedScreen.draw();
		} break;
		case GENERAL_STATE::gameOver: {
			gameOverScreen.draw();
		} break;
		case GENERAL_STATE::gameClear: {
			gameClearScreen.draw();
		} break;
		case GENERAL_STATE::game: {
			level.draw();
			player.draw();

			for (size_t i = 0; i < mv.size(); i++) {
				mv[i]->draw();
			}

			hud->draw(gameControl->getMonstersLeft());
			movesHeader.draw();
			sword.draw();
		} break;
	}

	graphics->spriteEnd();
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
	moonTexture.onLostDevice();
	swordTexture.onLostDevice();
	fontTexture.onLostDevice();

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
	moonTexture.onResetDevice();
	swordTexture.onResetDevice();
	fontTexture.onResetDevice();

	hud->resetAll();
	Game::resetAll();
	return;
}
