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

	if (!level.initialize(this, &levelTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map"));

	if (!player.initialize(this, TILE_SIZE, TILE_SIZE, PLAYER_COLS, &playerMaleTexture, PLAYER_DATA))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing male player"));

	if (!duck.initialize(this, TILE_SIZE, TILE_SIZE, DUCK_COLS, &duckTexture, DUCK_DATA))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing duck monster"));

	if (!ghost.initialize(this, TILE_SIZE, TILE_SIZE, GHOST_COLS, &ghostTexture, GHOST_DATA))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing duck monster"));

	//if (!slug.initialize(this, TILE_SIZE, TILE_SIZE, SLUG_COLS, &slugTexture, SLUG_DATA))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initialising slug monster"));

	if (!sword.initialize(this, 112, 112, 4, &swordTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sword"));

	hud = new Hud;
	hud->initializeTexture(graphics);
	
	// Set map position based off startTile
	level.setX(-(TILE_SIZE * SCALE * ((float)levelGrid->getStartTile().x - 3)));
	level.setY(-(TILE_SIZE * SCALE * ((float)levelGrid->getStartTile().y - 3)));

	//slug.setX(TILE_SIZE * SCALE * 2);
	//slug.setY(TILE_SIZE * SCALE * 0);

	this->initializeMonsters();
	hud->setInitialPosition();
	monsterGrid->logLayout();
	sword.setDirection(DOWN);

	return;
}

void ThreeChances::initializeMonsters() {
	std::vector<Entity*> mv = gameControl->getMonsterVec();

	// Add to monster grid
	monsterGrid->addMonster(Coordinates(6, 25), duck.getId());
	monsterGrid->addMonster(Coordinates(5, 25), ghost.getId());

	// Add to monster vec
	mv.push_back(&duck);
	mv.push_back(&ghost);

	duck.setX(TILE_SIZE * SCALE * 4);
	duck.setY(TILE_SIZE * SCALE * 0);

	ghost.setX(TILE_SIZE * SCALE * 3);
	ghost.setY(TILE_SIZE * SCALE * 0);

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
	// Check no animation currently running
	if (!player.getAnimating()) {
		// Check if it's player's turn
		if (gameControl->getGameState() == GAME_STATE::player) {
			float endPoint;

			if (input->isKeyDown(LEFT_KEY) && !keysPressed[LEFT]) {
				keysPressed[LEFT] = true;
				lastKeyPressed = LEFT;
				endPoint = level.getX() + TILE_SIZE * SCALE;
				player.moveInDirection(levelGrid, monsterGrid, LEFT, endPoint);
			}

			if (input->isKeyDown(RIGHT_KEY) && !keysPressed[RIGHT]) {
				keysPressed[RIGHT] = true;
				lastKeyPressed = RIGHT;
				endPoint = level.getX() - TILE_SIZE * SCALE;
				player.moveInDirection(levelGrid, monsterGrid, RIGHT, endPoint);
			}

			if (input->isKeyDown(UP_KEY) && !keysPressed[UP]) {
				keysPressed[UP] = true;
				lastKeyPressed = UP;
				endPoint = level.getY() + TILE_SIZE * SCALE;
				player.moveInDirection(levelGrid, monsterGrid, UP, endPoint);
			}

			if (input->isKeyDown(DOWN_KEY) && !keysPressed[DOWN]) {
				keysPressed[DOWN] = true;
				lastKeyPressed = DOWN;
				endPoint = level.getY() - TILE_SIZE * SCALE;
				player.moveInDirection(levelGrid, monsterGrid, DOWN, endPoint);
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
		if (player.getDirection() == LEFT)
			oppDirection = RIGHT;
		else if (player.getDirection() == RIGHT)
			oppDirection = LEFT;
		else if (player.getDirection() == UP)
			oppDirection = DOWN;
		else if (player.getDirection() == DOWN)
			oppDirection = UP;

		if (level.moveInDirection(frameTime, oppDirection, player.getEndPoint())) {
			level.update(levelGrid, &player);
		}

		// Loop thu monster vec and run 1 by 1
		duck.moveInDirection(frameTime, oppDirection, monsterGrid->getMonsterPos(levelGrid->getCurrentTile(), duck.getId()));
		ghost.moveInDirection(frameTime, oppDirection, monsterGrid->getMonsterPos(levelGrid->getCurrentTile(), ghost.getId()));
		// end loop
		player.update(frameTime, gameControl);
		hud->update(frameTime, &player);			
	}

	// Loop thu monster vec
	ghost.update(frameTime);
	// end loop
	resetKeysPressedMap(input, &keysPressed);
}

void ThreeChances::enemyAi() {
	// Loop thu monster vec
	if (ghost.getMovesLeft() > 0) {
		if (!gameControl->getEnemyAnimating()) {
			printf("Enemy AI action: ");
			int action = ghost.ai(frameTime, monsterGrid->findMonsterCoord(ghost.getId()), levelGrid->getCurrentTile());

			Coordinates currCoord = monsterGrid->findMonsterCoord(ghost.getId());

			switch (action) {
			case LEFT:
				monsterGrid->moveMonster(currCoord, Coordinates(currCoord.x - 1, currCoord.y));
				break;
			case RIGHT:
				monsterGrid->moveMonster(currCoord, Coordinates(currCoord.x + 1, currCoord.y));
				break;
			case UP:
				monsterGrid->moveMonster(currCoord, Coordinates(currCoord.x, currCoord.y - 1));
				break;
			case DOWN:
				monsterGrid->moveMonster(currCoord, Coordinates(currCoord.x, currCoord.y + 1));
				break;
			case ATTACK:
				break;
			}

			gameControl->setEnemyAnimating(true);
		}
		else {
			bool ghostAiComplete = false;

			Position endPos = monsterGrid->getMonsterPos(levelGrid->getCurrentTile(), ghost.getId());

			int ghostAction = ghost.getAction();

			if (ghostAction == ATTACK) {
				if (ghost.getAnimationComplete()) {
					ghostAiComplete = true;
					ghost.moveExecuted();
				}
			}
			else if (ghostAction == STAY) {
				ghostAiComplete = true;
				ghost.setMovesLeft(0);
			}
			else if (ghostAction > -1) {
				if (ghost.aiMoveInDirection(frameTime, ghostAction, endPos)) {
					ghostAiComplete = true;
					ghost.moveExecuted();
				}
			}

			if (ghostAiComplete) {
				printf("Enemy moves left: %d\n", ghost.getMovesLeft());
				gameControl->setEnemyAnimating(false);
			}
		}
	}
	// end loop

	// run below code once all monsters have moved
	else {
		printf("Enemy AI complete\n");
		gameControl->setGameState(GAME_STATE::player);

		// Loop monster vec
		ghost.resetMovesLeft();
		player.resetMovesLeft();
		// end loop
		hud->resetMovesHud();
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

	level.draw();
	player.draw();
	duck.draw();
	ghost.draw();
	//slug.draw();
	hud->draw();
	movesHeader.draw();
	sword.draw();

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
	//slugTexture.onLostDevice();
	swordTexture.onLostDevice();

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
	//slugTexture.onResetDevice();
	swordTexture.onResetDevice();

	hud->resetAll();
	Game::resetAll();
	return;
}
