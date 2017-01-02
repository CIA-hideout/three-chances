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
	if (!input->isKeyDown(X_KEY))
		(*keysPressed)[END] = false;
}

void resetScreenKeysPressedMap(Input *input, std::map<int, bool> *keysPressed) {
	if (!input->isKeyDown(SPACE_KEY))
		(*keysPressed)[SPACE] = false;
	if (!input->isKeyDown(ESC_KEY))
		(*keysPressed)[ESC] = false;
	if (!input->isKeyDown(M_KEY))
		(*keysPressed)[MUTE] = false;
}

//=============================================================================
// Constructor
//=============================================================================
ThreeChances::ThreeChances() {
	keysPressed[LEFT] = false;
	keysPressed[RIGHT] = false;
	keysPressed[UP] = false;
	keysPressed[DOWN] = false;
	keysPressed[END] = false;

	screenKeysPressed[ESC] = false;
	screenKeysPressed[SPACE] = false;
	screenKeysPressed[MUTE] = false;

	startBtnPressed = false;
	muted = true;

	gameMode = GAME_MODE::demo;
	stageNo = 1;
	finalStageNo = gameMode == GAME_MODE::demo ? DEMO_LEVEL::NO_OF_STAGE : NORMAL_LEVEL::NO_OF_STAGE;
	levelSize = gameMode == GAME_MODE::demo ? DEMO_LEVEL::LEVEL_SIZE : NORMAL_LEVEL::LEVEL_SIZE;
	levelCols = gameMode == GAME_MODE::demo ? DEMO_LEVEL::LEVEL_COLS : NORMAL_LEVEL::LEVEL_COLS;
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

	gameControl = new GameControl(audio);

	// initialize level grid
	levelGrid = new LevelGrid;
	levelGrid->initialize(gameMode);

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
	if (!levelTexture.initialize(graphics, gameMode == GAME_MODE::demo ? DEMO_LVL_1_IMAGE : LEVEL_1_IMAGE))
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

	// initialize images
	if (!level.initialize(this, levelSize, levelSize, levelCols, &levelTexture, levelGrid->getStartTile()))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map"));

	if (!player.initialize(this, TILE_SIZE, TILE_SIZE, playerNS::PLAYER_COLS, &playerMaleTexture, PLAYER_DATA))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing male player"));

	if (!sword.initialize(this, swordNS::SWORD_WIDTH, swordNS::SWORD_HEIGHT, swordNS::SWORD_COLS, &swordTexture))
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

	settings = new Settings;
	settings->initializeTexture(graphics);

	hud = new Hud;
	hud->initializeTexture(graphics, &fontTexture);

	this->initializeEntities();
	settings->setInitialPosition(muted);
	hud->setInitialPosition();

	return;
}

void ThreeChances::clearEntities() {
	// Clear mv
	std::vector<Entity*> mv;
	std::queue<Entity*> aq;
	gameControl->setGameState(GAME_STATE::player);
	gameControl->setMonsterVec(mv);
	gameControl->setAnimationQueue(aq);

	// initialize entity grid
	entityGrid = new EntityGrid;
}

void ThreeChances::restartGame() {
	clearEntities();

	// initialize level grid
	levelGrid = new LevelGrid;
	levelGrid->initialize(gameMode);

	levelTexture.initialize(graphics, gameMode == GAME_MODE::demo ? DEMO_LVL_1_IMAGE : LEVEL_1_IMAGE);
	level.initialize(this, levelSize, levelSize, levelCols, &levelTexture, levelGrid->getStartTile());

	player.setHealth(PLAYER_DATA.health);
	player.setMovesLeft(PLAYER_DATA.moves);
	player.setAnimating(false);
	player.rotateEntity(DOWN);

	level.setX(level.getStartX());
	level.setY(level.getStartY());

	hud->resetMovesHud();
	hud->resetHealthHud();
	this->initializeEntities();

	gameControl->setEnemyAiInitialized(false);
}

void ThreeChances::incrementStage() {
	stageNo++;
	clearEntities();

	// switch layout
	levelGrid->switchLayout(gameMode, stageNo);
	if (gameMode == GAME_MODE::demo) {
		switch (stageNo) {
			case 2: {
				levelTexture.initialize(graphics, DEMO_LVL_2_IMAGE);
				level.initialize(this, levelSize, levelSize, levelCols, &levelTexture, levelGrid->getStartTile());
			} break;
		}
	}

	player.setMovesLeft(PLAYER_DATA.moves);
	player.setAnimating(false);
	player.rotateEntity(DOWN);

	hud->resetMovesHud();
	this->initializeEntities();

	gameControl->setEnemyAiInitialized(false);
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
	// reset random seed
	srand(time(NULL));

	// Add player to entity grid
	entityGrid->addEntity(levelGrid->getStartTile(), PLAYER_ID);

	std::vector<Entity*> mv = gameControl->getMonsterVec();
	std::vector<std::vector<int>> gameGrid = levelGrid->getGrid();
	
	Entity *tempMonster;
	int monsterCols;
	TextureManager *monsterTexture;
	EntityData monsterData;

	if (gameMode == GAME_MODE::demo) {
		int gridSize = gameGrid.size();

		// initialize the 4 boxes
		std::vector<std::vector<Coordinates>> coordSet;
		for (int i = 0; i < 4; i++) {
			std::vector<Coordinates> tempVec;
			coordSet.push_back(tempVec);
		}

		// Add coordinates to that 4 boxes
		for (int i = 0; i < gridSize; i++) {
			for (int j = 0; j < gridSize; j++) {
				
				if (i < gridSize / 2 && j < gridSize / 2)
					coordSet[0].push_back(Coordinates(j, i));
				else if (i < gridSize / 2 && j >= gridSize / 2)
					coordSet[1].push_back(Coordinates(j, i));
				else if (i >= gridSize / 2 && j < gridSize / 2)
					coordSet[2].push_back(Coordinates(j, i));
				else 
					coordSet[3].push_back(Coordinates(j, i));
			}
		}

		// Spawn 5 monsters in each box
		for (size_t i = 0; i < coordSet.size(); i++) {
			int monsterCounter = 0;

			do {
				// try spawn random monster at random index
				int randIndex = rand() % coordSet[i].size();
				double randNo = ((double)rand()) / RAND_MAX;
				Coordinates startCoord = coordSet[i][randIndex];

				if (randNo < 0.5) {
					// ghost 50%
					tempMonster = new Ghost;
					monsterCols = ghostNS::GHOST_COLS;
					monsterTexture = &ghostTexture;
					monsterData = GHOST_DATA;
				}
				else if (randNo > 0.5 && randNo < 0.8) {
					// water monsters 30%
					if (levelGrid->getMapType() == MAP_TYPE::water) {
						tempMonster = new Duck;
						monsterCols = duckNS::DUCK_COLS;
						monsterTexture = &duckTexture;
						monsterData = DUCK_DATA;
					}
					else if (levelGrid->getMapType() == MAP_TYPE::lava) {
						 tempMonster = new Slug;
						 monsterCols = slugNS::SLUG_COLS;
						 monsterTexture = &slugTexture;
						 monsterData = SLUG_DATA;
					}
				}
				else {
					// moon 20%
					tempMonster = new Moon;
					monsterCols = moonNS::MOON_COLS;
					monsterTexture = &moonTexture;
					monsterData = MOON_DATA;
				}

				if (tempMonster->isValidSpawn(levelGrid, startCoord) && !entityGrid->isCoordOccupied(startCoord)) {
					tempMonster->initialize(this, TILE_SIZE, TILE_SIZE, monsterCols, monsterTexture, monsterData);
					mv = setInitPos(mv, entityGrid, tempMonster, entityGrid->getPlayerCoordinates(), startCoord);
					monsterCounter++;
				}
			

			} while (monsterCounter != MAX_NO_OF_MONSTERS_PER_SQUARE);
		}
		
	}
	else {
		for (size_t i = 0; i < DUCK_START_COORDS.size(); i++) {
			tempMonster = new Duck;
			tempMonster->initialize(this, TILE_SIZE, TILE_SIZE, duckNS::DUCK_COLS, &duckTexture, DUCK_DATA);
			mv = setInitPos(mv, entityGrid, tempMonster, entityGrid->getPlayerCoordinates(), DUCK_START_COORDS[i]);
		}

		for (size_t i = 0; i < GHOST_START_COORDS.size(); i++) {
			tempMonster = new Ghost;
			tempMonster->initialize(this, TILE_SIZE, TILE_SIZE, ghostNS::GHOST_COLS, &ghostTexture, GHOST_DATA);
			mv = setInitPos(mv, entityGrid, tempMonster, entityGrid->getPlayerCoordinates(), GHOST_START_COORDS[i]);
		}

		for (size_t i = 0; i < MOON_START_COORDS.size(); i++) {
			tempMonster = new Moon;
			tempMonster->initialize(this, TILE_SIZE, TILE_SIZE, moonNS::MOON_COLS, &moonTexture, MOON_DATA);
			mv = setInitPos(mv, entityGrid, tempMonster, entityGrid->getPlayerCoordinates(), MOON_START_COORDS[i]);
		}
	}

	gameControl->setPlayer(&player);
	gameControl->setMonsterVec(mv);
}

//=============================================================================
// Update all game items
//=============================================================================
void ThreeChances::update() {
	if (muted)
		audio->pauseCategory("Default");
	else
		audio->resumeCategory("Default");

	GENERAL_STATE gs = gameControl->getGeneralState();
	std::vector<Entity*> mv = gameControl->getMonsterVec();

	switch (gs) {
		case GENERAL_STATE::menu: {
			if (input->isKeyDown(SPACE_KEY) && !screenKeysPressed[SPACE]) {
				screenKeysPressed[SPACE] = true;			
				startBtnPressed = true;
				startCue = audio->playCue(START_GAME_CUE);
			}

			if (startBtnPressed) {
				DWORD* tempCueState = new DWORD;
				startCue->GetState(tempCueState);

				if (*tempCueState == XACT_CUESTATE_STOPPED || muted) {
					gameControl->setGeneralState(GENERAL_STATE::game);
				}
			}
		} break;
		case GENERAL_STATE::paused: {
			if (input->isKeyDown(SPACE_KEY) && !screenKeysPressed[SPACE]) {
				gameControl->setGeneralState(GENERAL_STATE::game);
				screenKeysPressed[SPACE] = true;
				audio->playCue(UNPAUSE_CUE);
			}

			if (input->isKeyDown(M_KEY) && !screenKeysPressed[MUTE]) {
				screenKeysPressed[MUTE] = true;
				muted = !muted;
			}

			settings->update(muted);
		} break;
		case GENERAL_STATE::gameOver: {
			if (input->isKeyDown(SPACE_KEY) && !screenKeysPressed[SPACE]) {
				gameControl->setGeneralState(GENERAL_STATE::menu);
				this->restartGame();
				screenKeysPressed[SPACE] = true;
				audio->stopCue(GAME_OVER_CUE);
				audio->playCue(CLICK_CUE);
			}
		} break;
		case GENERAL_STATE::gameClear: {
			if (input->isKeyDown(SPACE_KEY) && !screenKeysPressed[SPACE]) {
				gameControl->setGeneralState(GENERAL_STATE::menu);
				this->restartGame();
				screenKeysPressed[SPACE] = true;
				audio->playCue(CLICK_CUE);
			}
		} break;
		case GENERAL_STATE::game: {
			if (input->isKeyDown(ESC_KEY) && !screenKeysPressed[ESC]) {
				gameControl->setGeneralState(GENERAL_STATE::paused);
				screenKeysPressed[ESC] = true;
				audio->playCue(PAUSE_CUE);
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

					if (input->isKeyDown(X_KEY) && !keysPressed[END]) {
						keysPressed[END] = true;
						player.setMovesLeft(0);
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

						// Victory
						if (entityGrid->getPlayerCoordinates() == levelGrid->getEndTile()) {
							if (stageNo == finalStageNo)
								gameControl->setGeneralState(GENERAL_STATE::gameClear);
							else
								incrementStage();
						}
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
			if (gameMode != GAME_MODE::demo && gameControl->getMonstersLeft() == 0 && level.getPathBlocked()) {
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
		gameControl->setEnemyAiInitialized(false);
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
			settings->draw();
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

	settings->releaseAll();
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

	settings->resetAll();
	hud->resetAll();
	Game::resetAll();
	return;
}
