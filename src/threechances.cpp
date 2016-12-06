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

	// map texture
	if (!levelTexture.initialize(graphics, LEVEL_1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map texture"));

	if (!playerMaleTexture.initialize(graphics, PLAYER_MALE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing male texture"));

	if (!duckTexture.initialize(graphics, DUCK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing duck texture"));

	if (!ghostTexture.initialize(graphics, GHOST_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ghost texture"));

	//if (!slugTexture.initialize(graphics, SLUG_IMAGE))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initialising slug texture"));

	//if (!swordTexture.initialize(graphics, SWORD_IMAGE))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sword texture"));

	if (!fontTexture.initialize(graphics, FONT_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing font texture"));

	if (!level.initialize(this, LEVEL_SIZE, LEVEL_SIZE, LEVEL_COLS, &levelTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map"));

	if (!player.initialize(this, TILE_SIZE, TILE_SIZE, PLAYER_COLS, &playerMaleTexture, PLAYER_DATA))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing male player"));

	//if (!duck.initialize(this, TILE_SIZE, TILE_SIZE, DUCK_COLS, &duckTexture, DUCK_DATA))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing duck monster"));

	//if (!ghost.initialize(this, TILE_SIZE, TILE_SIZE, GHOST_COLS, &ghostTexture, GHOST_DATA))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ghost monster"));

	//if (!slug.initialize(this, TILE_SIZE, TILE_SIZE, SLUG_COLS, &slugTexture, SLUG_DATA))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initialising slug monster"));

	//if (!sword.initialize(this, 112, 112, 4, &swordTexture))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sword"));

	hud = new Hud;
	hud->initializeTexture(graphics, &fontTexture);

	this->initializeFonts();
	this->initializeEntities();
	hud->setInitialPosition();

	sword.setVisible(false);

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

void ThreeChances::initializeFonts() {
	titleFont = new Font();
	titleFont->initialize(graphics, 128, 128, 16, &fontTexture);
	titleFont->loadTextData(FONT_TEXTURE_INFO);
	titleFont->setScale(0.45f);

	secondaryTitleFont = new Font();
	secondaryTitleFont->initialize(graphics, 128, 128, 16, &fontTexture);
	secondaryTitleFont->loadTextData(FONT_TEXTURE_INFO);
	secondaryTitleFont->setScale(0.3f);
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
	std::vector<Coordinates> ghostStartCoords = {
		Coordinates(5, 25),
		Coordinates(7, 25),
		Coordinates(7, 20),
	};
	std::vector<Coordinates> duckStartCoords = {};

	Entity *tempMonster;

	for (int i = 0; i < ghostStartCoords.size(); i++) {
		tempMonster = new Ghost;
		tempMonster->initialize(this, TILE_SIZE, TILE_SIZE, GHOST_COLS, &ghostTexture, GHOST_DATA);
		mv = setInitPos(mv, entityGrid, tempMonster, entityGrid->getPlayerCoordinates(), ghostStartCoords[i]);
	}

	for (int i = 0; i < duckStartCoords.size(); i++) {
		tempMonster = new Duck;
		tempMonster->initialize(this, TILE_SIZE, TILE_SIZE, DUCK_COLS, &duckTexture, DUCK_DATA);
		mv = setInitPos(mv, entityGrid, tempMonster, entityGrid->getPlayerCoordinates(), ghostStartCoords[i]);
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
			if (input->isKeyDown(SPACE_KEY)) {
				gameControl->setGeneralState(GENERAL_STATE::game);
			}
		} break;
		case GENERAL_STATE::paused: {
			if (input->isKeyDown(SPACE_KEY)) {
				gameControl->setGeneralState(GENERAL_STATE::game);
			}
		} break;
		case GENERAL_STATE::gameOver: {
			if (input->isKeyDown(ESC_KEY)) {
				gameControl->setGeneralState(GENERAL_STATE::menu);
				this->restartGame();
			}
		} break;
		case GENERAL_STATE::game: {
			if (input->isKeyDown(ESC_KEY)) {
				gameControl->setGeneralState(GENERAL_STATE::paused);
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
						sword.setDirection(LEFT);
						sword.setX(player.getX() - TILE_SIZE * SCALE * 1);
						sword.setY(player.getY());
					}

					if (input->isKeyDown(RIGHT_KEY) && !keysPressed[RIGHT]) {
						keysPressed[RIGHT] = true;
						lastKeyPressed = RIGHT;
						endPoint = level.getX() - TILE_SIZE * SCALE;
						player.moveInDirection(levelGrid, entityGrid, RIGHT, endPoint, gameControl);
						sword.setDirection(RIGHT);
						sword.setX(player.getX() + TILE_SIZE * SCALE * 1);
						sword.setY(player.getY());
					}

					if (input->isKeyDown(UP_KEY) && !keysPressed[UP]) {
						keysPressed[UP] = true;
						lastKeyPressed = UP;
						endPoint = level.getY() + TILE_SIZE * SCALE;
						player.moveInDirection(levelGrid, entityGrid, UP, endPoint, gameControl);
						sword.setDirection(UP);
						sword.setX(player.getX());
						sword.setY(player.getY() - TILE_SIZE * SCALE * 1);
					}

					if (input->isKeyDown(DOWN_KEY) && !keysPressed[DOWN]) {
						keysPressed[DOWN] = true;
						lastKeyPressed = DOWN;
						endPoint = level.getY() - TILE_SIZE * SCALE;
						player.moveInDirection(levelGrid, entityGrid, DOWN, endPoint, gameControl);
						sword.setDirection(DOWN);
						sword.setX(player.getX());
						sword.setY(player.getY() + TILE_SIZE * SCALE * 1);
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

				if (player.getAction() != ATTACK) {
					if (level.moveInDirection(frameTime, oppDirection, player.getEndPoint())) {
						level.finishAnimating(levelGrid, &player);
						levelGrid->logTile(entityGrid->getPlayerCoordinates(), level.getX(), level.getY());
					}
				}

				if (player.getAction() == ATTACK) {
					sword.attack(frameTime);
				}

				for (size_t i = 0; i < mv.size(); i++) {
					mv[i]->moveInDirection(frameTime, oppDirection, entityGrid->getEntityPosition(mv[i]->getId()));
				}

				player.update(frameTime, gameControl);
			}

			// Update sprites
			for (size_t i = 0; i < mv.size(); i++) {
				mv[i]->update(frameTime);
			}

			player.update(frameTime, gameControl);
			hud->update(frameTime, &player, gameControl->getMonstersLeft());

			// Remove blockage on level if monsters left == 0
			if (gameControl->getMonstersLeft() == 0 && level.getPathBlocked()) {
				level.removeBlockage();
				levelGrid->removeBlockage();
			}

			resetKeysPressedMap(input, &keysPressed);
		} break;
	}
}

void ThreeChances::enemyAi() {
	std::vector<Entity*> mv = gameControl->getMonsterVec();

	for (size_t i = 0; i < mv.size(); i++) {
		Entity* entityPtr = mv[i];

		if (entityPtr->getMovesLeft() > 0) {
			if (!entityPtr->getAnimating()) {
				mv[i]->initAi(entityGrid, levelGrid);

				if (mv[i]->getAction() == ATTACK)
					gameControl->damagePlayer(mv[i]->getId());
			}
			else {
				mv[i]->animateAi(frameTime, entityGrid);
			}
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
	}
	else {
		gameControl->setEnemyAnimating(true);
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
	graphics->spriteBegin();
	std::vector<Entity*> mv = gameControl->getMonsterVec();

	switch (gameControl->getGeneralState()) {
		case GENERAL_STATE::menu: {
			titleFont->Print(
				GAME_WIDTH / 2 - titleFont->getTotalWidth("three") / 2 - 10,
				GAME_HEIGHT / 4,
				"three"
				);
			titleFont->Print(
				GAME_WIDTH / 2 - titleFont->getTotalWidth("chances") / 2 - 10,
				GAME_HEIGHT /4 + 45,
				"chances"
				);
			secondaryTitleFont->Print(
				GAME_WIDTH / 2 - secondaryTitleFont->getTotalWidth("press space to start") / 2 - 10,
				GAME_HEIGHT - 120,
				"press space to start"
				);
		} break;
		case GENERAL_STATE::paused: {
			titleFont->setScale(0.8f);
			titleFont->Print(
				GAME_WIDTH / 2 - titleFont->getTotalWidth("paused") / 2 - 10,
				GAME_HEIGHT / 4,
				"paused"
				);
			secondaryTitleFont->Print(
				GAME_WIDTH / 2 - secondaryTitleFont->getTotalWidth("press space to") / 2 - 10,
				GAME_HEIGHT - 120,
				"press space to"
				);
			secondaryTitleFont->Print(
				GAME_WIDTH / 2 - secondaryTitleFont->getTotalWidth("continue") / 2 - 10,
				GAME_HEIGHT - 120 + 45,
				"continue"
				);
		} break;
		case GENERAL_STATE::gameOver: {
			titleFont->setScale(0.6f);
			titleFont->Print(
				GAME_WIDTH / 2 - titleFont->getTotalWidth("game over") / 2 - 10,
				GAME_HEIGHT / 4,
				"game over"
				);
			secondaryTitleFont->setScale(0.2);
			secondaryTitleFont->Print(
				GAME_WIDTH / 2 - secondaryTitleFont->getTotalWidth("press esc to restart") / 2 - 10,
				GAME_HEIGHT - 120,
				"press esc to restart"
				);
		} break;
		case GENERAL_STATE::game: {
			level.draw();
			player.draw();
			//duck.draw();
			//ghost.draw();
			//slug.draw();

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
	//duckTexture.onLostDevice();
	ghostTexture.onLostDevice();
	//slugTexture.onLostDevice();
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
	//duckTexture.onResetDevice();
	ghostTexture.onResetDevice();
	//slugTexture.onResetDevice();
	swordTexture.onResetDevice();
	fontTexture.onResetDevice();

	hud->resetAll();
	Game::resetAll();
	return;
}
