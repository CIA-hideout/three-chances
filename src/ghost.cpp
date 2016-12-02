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

bool Ghost::animateAi(float frameTime, MonsterGrid *mg, Coordinates playerCoord) {
	int ghostAction = this->getAction();
	bool ghostAiCompleted = false;
	Position endPos = mg->getMonsterPos(playerCoord, this->getId());

	if (ghostAction == ATTACK) {
		if (this->getAnimationComplete()) {
			ghostAiCompleted = true;
			this->moveExecuted();
		}
	}
	else if (ghostAction == STAY) {
		ghostAiCompleted = true;
		this->setMovesLeft(0);
	}
	else if (ghostAction > -1) {
		if (this->aiMoveInDirection(frameTime, ghostAction, endPos)) {
			ghostAiCompleted = true;
			this->moveExecuted();
		}
	}

	if (ghostAiCompleted) {
		printf("Enemy moves left: %d\n", this->getMovesLeft());
		this->setAnimating(false);
		return true;
	}

	return false;
}

void Ghost::initAi(MonsterGrid *mg, Coordinates playerCoord, GameControl *gc) {
	int action = -1;
	int directionToAttack;
	Coordinates monsterCoord = mg->findMonsterCoord(this->getId());
	this->setAnimating(true);

	if (targetWithinRange(monsterCoord, playerCoord, 3)) {
		directionToAttack = targetWithinAtkRange(monsterCoord, playerCoord, this->getAtkRange());

		// Attack if target is beside
		if (directionToAttack != -1) {
			this->startAttackAnimation();
			action = ATTACK;
			gc->damagePlayer(this->getId());
			printf(" Attack\n");
		}
		// Move if target is out of atk range
		else {
			this->startWalkAnimation();

			if (monsterCoord.x > playerCoord.x) {
				action = LEFT;
				printf(" Left\n");
			}
			else if (monsterCoord.x < playerCoord.x) {
				action = RIGHT;
				printf(" Right\n");
			}
			else {
				if (monsterCoord.y > playerCoord.y) {
					action = UP;
					printf(" Up\n");
				}
				else if (monsterCoord.y < playerCoord.y) {
					action = DOWN;
					printf(" Down\n");
				}
			}
		}
	}
	// Stay if target is out of range
	else {
		action = STAY;
		printf(" Stay\n");
	}

	switch (action) {
	case LEFT:
		mg->moveMonster(monsterCoord, Coordinates(monsterCoord.x - 1, monsterCoord.y));
		break;
	case RIGHT:
		mg->moveMonster(monsterCoord, Coordinates(monsterCoord.x + 1, monsterCoord.y));
		break;
	case UP:
		mg->moveMonster(monsterCoord, Coordinates(monsterCoord.x, monsterCoord.y - 1));
		break;
	case DOWN:
		mg->moveMonster(monsterCoord, Coordinates(monsterCoord.x, monsterCoord.y + 1));
		break;
	}

	// only rotate for movement and attack actions
	if (action == ATTACK)
		this->rotateEntity(directionToAttack);
	else if (action != STAY)
		this->rotateEntity(action);

	this->setAction(action);
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

void Ghost::startWalkAnimation() {
	this->setFrames(GHOST_WALK_START_FRAME, GHOST_WALK_END_FRAME);
	this->setCurrentFrame(GHOST_WALK_START_FRAME);
}

void Ghost::startAttackAnimation() {
	this->setFrames(GHOST_ATK_START_FRAME, GHOST_ATK_END_FRAME);
	this->setCurrentFrame(GHOST_ATK_START_FRAME);
}

void Ghost::startHurtAnimation() {
	this->setCurrentFrame(GHOST_HURT_FRAME);
}

bool Ghost::isValidMove(LevelGrid *levelGrid, int direction) {
	int currentTileValue = levelGrid->getCurrentTileValue();
	int nextTileValue = levelGrid->getNextTileValue(direction);

	bool valid = false;

	if (currentTileValue == 1)								// 1st floor
		valid = nextTileValue == 1 || nextTileValue == 3;	// 1st floor or stairs
	else if (currentTileValue == 2)							// 2nd floor
		valid = nextTileValue == 2 || nextTileValue == 3;	// 2nd floor or stairs
	else if (currentTileValue == 3)							// Stairs
		valid = nextTileValue == 1 || nextTileValue == 2;	// 1st floor or 2nd floor

	return valid;
}
