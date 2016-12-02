#include "ghost.h"

bool targetWithinRange(Coordinates monsterCoord, Coordinates playerCoord, int range) {
	// Check x coordinate within range
	if (playerCoord.x <= monsterCoord.x + range && playerCoord.x >= monsterCoord.x - range) {
		// Check y coordinate within range
		if (playerCoord.y <= monsterCoord.y + range && playerCoord.y >= monsterCoord.y - range) {
			return true;
		}
	}

	return false;
}

int targetWithinAtkRange(Coordinates monsterCoord, Coordinates playerCoord, int atkRange) {
	// True if player is on the same row as monster
	if (playerCoord.y == monsterCoord.y) {
		// Check if player is within LEFT atk range
		if (playerCoord.x < monsterCoord.x && playerCoord.x >= monsterCoord.x - atkRange) {
			return LEFT;
		}
		// Check if player is within RIGHT atk range
		if (playerCoord.x > monsterCoord.x && playerCoord.x <= monsterCoord.x + atkRange) {
			return RIGHT;
		}
	}
	// True if player is on the same column as monster
	if (playerCoord.x == monsterCoord.x) {
		// Check if player is within UP atk range
		if (playerCoord.y < monsterCoord.y && playerCoord.y >= monsterCoord.y - atkRange) {
			return UP;
		}
		// Check if player is within DOWN atk range
		if (playerCoord.y > monsterCoord.y && playerCoord.y <= monsterCoord.y + atkRange) {
			return DOWN;
		}
	}

	return -1;
}


Ghost::Ghost() : Entity() {
	this->setFrameDelay(GHOST_ANIMATION_DELAY);
	this->setLoop(false);
}

Ghost::~Ghost() {}

void Ghost::update(float frameTime) {
	// Need to block stage change and wait till animation is played finish for death
	if (this->getAnimationComplete()) {
		// Clean up
		this->setFrames(0, 0);
		this->setCurrentFrame(GHOST_STANDING_FRAME);
		this->setAnimationComplete(false);

		if (this->getHealth() <= 0.0) {
			this->startDeathAnimation();
		}
	}

	if (this->getCurrentFrame() == GHOST_HURT_FRAME) {
		this->setTimer(this->getTimer() + frameTime);

		if (this->getTimer() > 0.2) {
			this->setTimer(0.0f);
			this->setAnimationComplete(true);
		}

	}

	Entity::update(frameTime);
}

bool Ghost::animateAi(float frameTime, MonsterGrid *monsterGrid, Coordinates playerCoord) {
	int action = this->getAction();
	bool animationComplete = false;
	Position endPos = monsterGrid->getMonsterPos(playerCoord, this->getId());

	if (action == ATTACK) {
		if (this->getAnimationComplete()) {
			animationComplete = true;
			this->moveExecuted();
		}
	}
	else if (action == STAY) {
		animationComplete = true;
		this->setMovesLeft(0);
	}
	else if (action > -1) {
		if (this->aiMoveInDirection(frameTime, action, endPos)) {
			animationComplete = true;
			this->moveExecuted();
		}
	}

	if (animationComplete) {
		printf("Enemy %d moves left: %d\n", this->getId(), this->getMovesLeft());
		this->setAnimating(false);
		return true;
	}

	return false;
}

void Ghost::initAi(MonsterGrid *monsterGrid, LevelGrid *levelGrid, GameControl *gc) {
	int action = -1;
	int directionToAttack;
	Coordinates monsterCoord = monsterGrid->findMonsterCoord(this->getId());
	Coordinates playerCoord = levelGrid->getCurrentTile();

	if (targetWithinRange(monsterCoord, playerCoord, 3)) {
		directionToAttack = targetWithinAtkRange(monsterCoord, playerCoord, this->getAtkRange());

		// Attack if target is directly beside
		if (directionToAttack != -1) {
			action = ATTACK;
			this->rotateEntity(directionToAttack);
			this->startAttackAnimation();
			gc->damagePlayer(this->getId());
		}
		// Move if target is out of atk range
		else {
			std::vector<int> availableMoves = this->getAvailableMoves(monsterGrid, levelGrid, monsterCoord);

			// All directions are blocked. Stay.
			if (availableMoves.size() == 0) {
				action = STAY;
			}
			else {
				std::vector<int> bestMoves = this->getBestMoves(monsterCoord, playerCoord);

				// Get best available move
				for (size_t i = 0; i < bestMoves.size(); ++i) {
					for (size_t j = 0; j < availableMoves.size(); ++j) {
						if (availableMoves[j] == bestMoves[i]) {
							action = bestMoves[i];
							break;
						}
					}

					if (action != -1) break;
				}

				// Best move found, move in direction
				this->rotateEntity(action);
				this->startWalkAnimation();
			}                                 
		}
	}
	// Stay if target is out of range
	else {
		action = STAY;
	}

	switch (action) {
	case LEFT:
		monsterGrid->moveMonster(monsterCoord, Coordinates(monsterCoord.x - 1, monsterCoord.y));
		break;
	case RIGHT:
		monsterGrid->moveMonster(monsterCoord, Coordinates(monsterCoord.x + 1, monsterCoord.y));
		break;
	case UP:
		monsterGrid->moveMonster(monsterCoord, Coordinates(monsterCoord.x, monsterCoord.y - 1));
		break;
	case DOWN:
		monsterGrid->moveMonster(monsterCoord, Coordinates(monsterCoord.x, monsterCoord.y + 1));
		break;
	}

	this->setAnimating(true);
	this->setAction(action);
	this->logAction();
}

void Ghost::rotateEntity(int direction) {
	RECT sampleRect = this->getSpriteDataRect();

	if (direction != -1) {
		sampleRect.left = 0;
		sampleRect.right = TILE_SIZE;

		if (direction == LEFT)
			sampleRect.top = 32;
		if (direction == RIGHT)
			sampleRect.top = 96;
		if (direction == UP)
			sampleRect.top = 64;
		if (direction == DOWN)
			sampleRect.top = 0;

		sampleRect.bottom = sampleRect.top + TILE_SIZE;
	}

	this->setSpriteDataRect(sampleRect);
}

void Ghost::startAttackAnimation() {
	this->setFrames(GHOST_ATK_START_FRAME, GHOST_ATK_END_FRAME);
	this->setCurrentFrame(GHOST_ATK_START_FRAME);
}

void Ghost::startWalkAnimation() {
	this->setFrames(GHOST_WALK_START_FRAME, GHOST_WALK_END_FRAME);
	this->setCurrentFrame(GHOST_WALK_START_FRAME);
}

void Ghost::startHurtAnimation() {
	this->setCurrentFrame(GHOST_HURT_FRAME);
}

void Ghost::startDeathAnimation() {
	this->setVisible(false);
}

void Ghost::logAction() {
	printf("Enemy %d action: ", this->getId());
	switch (this->getAction()) {
	case 0:
		printf("LEFT\n");
		break;
	case 1:
		printf("RIGHT\n");
		break;
	case 2:
		printf("UP\n");
		break;
	case 3:
		printf("DOWN\n");
		break;
	case 4:
		printf("ATTACK\n");
		break;
	case 5:
		printf("STAY\n");
		break;
	default:
		break;
	}
}

bool Ghost::isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction) {
	int currentTileValue = levelGrid->getTileValueAtCoordinates(currCoord);
	int nextTileValue = levelGrid->getNextTileValue(currCoord, direction);

	bool valid = false;

	if (currentTileValue == 1)								// 1st floor
		valid = nextTileValue == 1 || nextTileValue == 3;	// 1st floor or stairs
	else if (currentTileValue == 2)							// 2nd floor
		valid = nextTileValue == 2 || nextTileValue == 3;	// 2nd floor or stairs
	else if (currentTileValue == 3)							// Stairs
		valid = nextTileValue == 1 || nextTileValue == 2;	// 1st floor or 2nd floor

	return valid;
}

bool Ghost::isTileEmpty(MonsterGrid *monsterGrid, int direction) {
	Coordinates currCoord = monsterGrid->findMonsterCoord(this->getId());
	int nextTileValue = monsterGrid->getNextTileValue(currCoord, direction);

	return nextTileValue == 0;
}

int Ghost::getBestXmove(int monsterX, int playerX) {
	if (monsterX > playerX)
		return LEFT;
	else if (monsterX < playerX)
		return RIGHT;
	
	return STAY;
}

int Ghost::getBestYmove(int monsterY, int playerY) {
	if (monsterY > playerY)
		return UP;
	else if (monsterY < playerY)
		return DOWN;

	return STAY;
}

std::vector<int> Ghost::getBestMoves(Coordinates monsterCoord, Coordinates playerCoord) {
	std::vector<int> bestMoves;

	int bestXmove = this->getBestXmove(monsterCoord.x, playerCoord.x);
	int bestYmove = this->getBestYmove(monsterCoord.y, playerCoord.y);

	if (bestXmove != STAY && bestYmove != STAY) {
		bestMoves.push_back(bestXmove);
		bestMoves.push_back(bestYmove);
		bestMoves.push_back(bestXmove == LEFT ? RIGHT : LEFT);
		bestMoves.push_back(bestYmove == UP ? DOWN : UP);
	}
	else if (bestXmove == STAY) {
		bestMoves.push_back(bestYmove);
		bestMoves.push_back(LEFT);
		bestMoves.push_back(RIGHT);
		bestMoves.push_back(bestYmove == UP ? DOWN : UP);
	}
	else if (bestYmove == STAY) {
		bestMoves.push_back(bestXmove);
		bestMoves.push_back(UP);
		bestMoves.push_back(DOWN);
		bestMoves.push_back(bestXmove == LEFT ? RIGHT : LEFT);
	}

	return bestMoves;
}

std::vector<int> Ghost::getAvailableMoves(MonsterGrid *monsterGrid, LevelGrid *levelGrid, Coordinates monsterCoord) {
	std::vector<int> moves = { LEFT, RIGHT, UP, DOWN };
	std::vector<int> availableMoves;
	for (size_t i = 0; i < moves.size(); ++i) {
		if (this->isValidMove(levelGrid, monsterCoord, moves[i])
			&& this->isTileEmpty(monsterGrid, moves[i]))
			availableMoves.push_back(moves[i]);
	}

	return availableMoves;
}
