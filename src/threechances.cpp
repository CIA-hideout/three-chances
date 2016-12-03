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

	//if (!slugTexture.initialize(graphics, SLUG_IMAGE))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initialising slug texture"));

	if (!swordTexture.initialize(graphics, SWORD_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sword texture"));

	if (!fontTexture.initialize(graphics, FONT_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing font texture"));

	if (!level.initialize(this, &levelTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map"));

	if (!player.initialize(this, TILE_SIZE, TILE_SIZE, PLAYER_COLS, &playerMaleTexture, PLAYER_DATA))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing male player"));

	if (!duck.initialize(this, TILE_SIZE, TILE_SIZE, DUCK_COLS, &duckTexture, DUCK_DATA))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing duck monster"));

	if (!ghost.initialize(this, TILE_SIZE, TILE_SIZE, GHOST_COLS, &ghostTexture, GHOST_DATA))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ghost monster"));

	//if (!slug.initialize(this, TILE_SIZE, TILE_SIZE, SLUG_COLS, &slugTexture, SLUG_DATA))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initialising slug monster"));

	if (!sword.initialize(this, 112, 112, 4, &swordTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sword"));

	hud = new Hud;
	hud->initializeTexture(graphics, &fontTexture);

	// Set map position based off startTile
	level.setX(-(TILE_SIZE * SCALE * ((float)levelGrid->getStartTile().x - 3)));
	level.setY(-(TILE_SIZE * SCALE * ((float)levelGrid->getStartTile().y - 3)));

	//slug.setX(TILE_SIZE * SCALE * 2);
	//slug.setY(TILE_SIZE * SCALE * 0);

	this->initializeFonts();
	this->initializeMonsters();
	hud->setInitialPosition();
	//monsterGrid->logLayout();
	sword.setDirection(DOWN);

	return;
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

void ThreeChances::initializeMonsters() {
	// creating a temporary ghost
	//Ghost tempGhost;
	//tempGhost.initialize(this, TILE_SIZE, TILE_SIZE, GHOST_COLS, &ghostTexture, GHOST_DATA);

	std::vector<Entity*> mv = gameControl->getMonsterVec();

	// Add to monster grid
	//monsterGrid->addMonster(Coordinates(6, 25), duck.getId());
	monsterGrid->addMonster(Coordinates(5, 25), ghost.getId());

	// Add to monster vec
	//mv.push_back(&duck);
	mv.push_back(&ghost);

	//duck.setX(TILE_SIZE * SCALE * 4);
	//duck.setY(TILE_SIZE * SCALE * 0);

	ghost.setX(TILE_SIZE * SCALE * 3);
	ghost.setY(TILE_SIZE * SCALE * 0);

	gameControl->setPlayer(&player);
	gameControl->setMonsterVec(mv);
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
	GENERAL_STATE gs = gameControl->getGeneralState();
	std::vector<Entity*> mv = gameControl->getMonsterVec();

	switch (gs) {
		case GENERAL_STATE::menu: {
			// detect space
			if (input->isKeyDown(SPACE_KEY)) {
				gameControl->setGeneralState(GENERAL_STATE::game);
			}

		} break;
		case GENERAL_STATE::paused: {
			if (input->isKeyDown(SPACE_KEY)) {
				gameControl->setGeneralState(GENERAL_STATE::game);
			}
		} break;
		case GENERAL_STATE::game: {
			if (input->isKeyDown(ESC_KEY)) {
				gameControl->setGeneralState(GENERAL_STATE::paused);
			}

			// Check no animation currently running
			if (!player.getAnimating()) {
				gameControl->cleanupEnemy(monsterGrid);

				// Check if it's player's turn
				if (gameControl->getGameState() == GAME_STATE::player) {
					float endPoint;

					if (input->isKeyDown(LEFT_KEY) && !keysPressed[LEFT]) {
						keysPressed[LEFT] = true;
						lastKeyPressed = LEFT;
						endPoint = level.getX() + TILE_SIZE * SCALE;
						player.moveInDirection(levelGrid, monsterGrid, LEFT, endPoint, gameControl);
					}

					if (input->isKeyDown(RIGHT_KEY) && !keysPressed[RIGHT]) {
						keysPressed[RIGHT] = true;
						lastKeyPressed = RIGHT;
						endPoint = level.getX() - TILE_SIZE * SCALE;
						player.moveInDirection(levelGrid, monsterGrid, RIGHT, endPoint, gameControl);
					}

					if (input->isKeyDown(UP_KEY) && !keysPressed[UP]) {
						keysPressed[UP] = true;
						lastKeyPressed = UP;
						endPoint = level.getY() + TILE_SIZE * SCALE;
						player.moveInDirection(levelGrid, monsterGrid, UP, endPoint, gameControl);
					}

					if (input->isKeyDown(DOWN_KEY) && !keysPressed[DOWN]) {
						keysPressed[DOWN] = true;
						lastKeyPressed = DOWN;
						endPoint = level.getY() - TILE_SIZE * SCALE;
						player.moveInDirection(levelGrid, monsterGrid, DOWN, endPoint, gameControl);
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
					}
				}

				for (size_t i = 0; i < mv.size(); i++) {
					mv[i]->moveInDirection(frameTime, oppDirection, 
						monsterGrid->getMonsterPos(levelGrid->getCurrentTile(), mv[i]->getId()));
				}
				
				player.update(frameTime, gameControl);
			}

			// Update monsters
			for (size_t i = 0; i < mv.size(); i++) {
				mv[i]->update(frameTime);
			}

			hud->update(frameTime, &player, gameControl->getMonstersLeft());
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
				printf("Enemy AI %i action:", mv[i]->getId());
				mv[i]->initAi(monsterGrid, levelGrid->getCurrentTile(), gameControl);
			}
			else {
				mv[i]->animateAi(frameTime, monsterGrid, levelGrid->getCurrentTile());
			}
		}
	}

	if (gameControl->checkMonstersMovesCompleted()) {
		printf("Enemy AI complete\n");
		for (size_t i = 0; i < mv.size(); i++) {
			mv[i]->resetMovesLeft();
		}

		gameControl->setGameState(GAME_STATE::player);	
		player.resetMovesLeft();
		hud->resetMovesHud();
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
		case GENERAL_STATE::game: {
			level.draw();
			player.draw();
			//duck.draw();
			ghost.draw();
			//slug.draw();
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
