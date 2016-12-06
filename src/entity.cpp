#include "entity.h"

int currentId = 0;

bool targetWithinRange(Coordinates entityCoord, Coordinates playerCoord, int range) {
	// Check x coordinate within range
	if (playerCoord.x <= entityCoord.x + range && playerCoord.x >= entityCoord.x - range) {
		// Check y coordinate within range
		if (playerCoord.y <= entityCoord.y + range && playerCoord.y >= entityCoord.y - range) {
			return true;
		}
	}

	return false;
}

int targetWithinAtkRange(Coordinates entityCoord, Coordinates playerCoord, int atkRange) {
	// True if player is on the same row as monster
	if (playerCoord.y == entityCoord.y) {
		// Check if player is within LEFT atk range
		if (playerCoord.x < entityCoord.x && playerCoord.x >= entityCoord.x - atkRange) {
			return LEFT;
		}
		// Check if player is within RIGHT atk range
		if (playerCoord.x > entityCoord.x && playerCoord.x <= entityCoord.x + atkRange) {
			return RIGHT;
		}
	}
	// True if player is on the same column as monster
	if (playerCoord.x == entityCoord.x) {
		// Check if player is within UP atk range
		if (playerCoord.y < entityCoord.y && playerCoord.y >= entityCoord.y - atkRange) {
			return UP;
		}
		// Check if player is within DOWN atk range
		if (playerCoord.y > entityCoord.y && playerCoord.y <= entityCoord.y + atkRange) {
			return DOWN;
		}
	}

	return -1;
}

Entity::Entity() : Image() {
	timer = 0.0;
	animating = false;
	action = -1;
}

Entity::~Entity() {
}

bool Entity::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM, EntityData ed) {
	currentId++;

	health = ed.health;
	damage = ed.damage;
	atkRange = ed.atkRange;
	moves = ed.moves;
	movesLeft = ed.moves;
	levels = ed.levels;
	abilities = ed.abilities;
	id = currentId;
	action = -1;

	this->setScale((float)SCALE);

	return(Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

void Entity::update(float frameTime) {
	// Call the base image update func to update the screen
	Image::update(frameTime);
}

void Entity::ai(float frameTime, Entity &ent) {}

void Entity::setRect() {
	spriteData.rect.left = currentFrame * spriteData.width;
	spriteData.rect.right = spriteData.rect.left + spriteData.width;
}

void Entity::rotateEntity(int direction) {
	RECT sampleRect = this->getSpriteDataRect();

	if (direction != -1) {
		sampleRect.left = 0;
		sampleRect.right = TILE_SIZE;

		if (direction == LEFT)
			sampleRect.top = 64;
		if (direction == RIGHT)
			sampleRect.top = 96;
		if (direction == UP)
			sampleRect.top = 32;
		if (direction == DOWN)
			sampleRect.top = 0;

		sampleRect.bottom = sampleRect.top + TILE_SIZE;
	}

	this->setSpriteDataRect(sampleRect);
}

void Entity::moveExecuted() {
	this->setMovesLeft(this->getMovesLeft() - 1);
}

void Entity::resetMovesLeft() {
	this->setMovesLeft(this->getMoves());
}

bool Entity::moveInDirection(float frameTime, int direction, Position endPos) {
	bool reachedEndPoint = false;

	switch (direction) {
	case LEFT:
		if (this->getX() > endPos.x) {
			this->setX(this->getX() - VELOCITY * frameTime);
		}
		else {
			this->setX(endPos.x);
			reachedEndPoint = true;
		}
		break;
	case RIGHT:
		if (this->getX() < endPos.x) {
			this->setX(this->getX() + VELOCITY * frameTime);
		}
		else {
			this->setX(endPos.x);
			reachedEndPoint = true;
		}
		break;

	case UP:
		if (this->getY() > endPos.y) {
			this->setY(this->getY() - VELOCITY * frameTime);
		}
		else {
			this->setY(endPos.y);
			reachedEndPoint = true;
		}
		break;

	case DOWN:
		if (this->getY() < endPos.y) {
			this->setY(this->getY() + VELOCITY * frameTime);
		}
		else {
			this->setY(endPos.y);
			reachedEndPoint = true;
		}
		break;
	}

	return reachedEndPoint;
}

bool Entity::aiMoveInDirection(float frameTime, int direction, Position endPos) {
	if (!this->getAnimating())
		return false;
	else
		return moveInDirection(frameTime, direction, endPos);
}

void Entity::logAction() {
	int id = this->getId();
	printf("%s %d action: ", id == 1 ? "Player" : "Enemy", id);
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

void Entity::initAi(EntityGrid *entityGrid, LevelGrid *levelGrid) {
	int action = -1;
	Coordinates entityCoord = entityGrid->getEntityCoordinates(this->getId());
	Coordinates playerCoord = entityGrid->getPlayerCoordinates();

	if (targetWithinRange(entityCoord, playerCoord, 3)) {
		int directionToAttack = targetWithinAtkRange(entityCoord, playerCoord, this->getAtkRange());

		// Attack if target is directly beside
		if (directionToAttack != -1) {
			action = ATTACK;
			this->rotateEntity(directionToAttack);
			this->startAttackAnimation();
			
		}
		// Move if target is out of atk range
		else {
			std::vector<int> availableMoves = this->getAvailableMoves(entityGrid, levelGrid, entityCoord);

			// All directions are blocked. Stay.
			if (availableMoves.size() == 0) {
				action = STAY;
			}
			else {
				std::vector<int> bestMoves = this->getBestMoves(entityCoord, playerCoord);

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
				Coordinates nextCoord = entityGrid->getNextTileCoordinates(entityCoord, action);
				entityGrid->moveEntity(entityCoord, nextCoord);
				this->rotateEntity(action);
				this->startWalkAnimation();
			}
		}
	}
	// Stay if target is out of range
	else {
		action = STAY;
	}

	this->setAnimating(true);
	this->setAction(action);
	this->logAction();
}

bool Entity::animateAi(float frameTime, EntityGrid *entityGrid) {
	int action = this->getAction();
	bool animationComplete = false;
	Position endPos = entityGrid->getEntityPosition(this->getId());

	if (action == ATTACK) {
		if (this->getAnimationComplete()) {
			animationComplete = true;
			this->moveExecuted();
			PlaySound(ATTACK_SOUND, NULL, SND_ASYNC);
		}
	}
	else if (action == STAY) {
		animationComplete = true;
		this->setMovesLeft(0);
	}
	else if (action != -1) {
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

bool Entity::isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction) {
	int currTileValue = levelGrid->getTileValueAtCoordinates(currCoord);
	int nextTileValue = levelGrid->getNextTileValue(currCoord, direction);

	bool valid = false;

	if (currTileValue == 1)									// 1st floor
		valid = nextTileValue == 1 || nextTileValue == 3;	// 1st floor or stairs
	else if (currTileValue == 2)							// 2nd floor
		valid = nextTileValue == 2 || nextTileValue == 3;	// 2nd floor or stairs
	else if (currTileValue == 3)							// Stairs
		valid = nextTileValue == 1 || nextTileValue == 2 || nextTileValue == 3;	// 1st floor or 2nd floor or stairs

	return valid;
}

bool Entity::isTileEmpty(EntityGrid *entityGrid, int direction) {
	Coordinates currCoord = entityGrid->getEntityCoordinates(this->getId());
	int nextTileValue = entityGrid->getNextTileValue(currCoord, direction);

	return nextTileValue == 0;
}

int Entity::getBestXmove(int entityX, int playerX) {
	if (entityX > playerX)
		return LEFT;
	else if (entityX < playerX)
		return RIGHT;

	return STAY;
}

int Entity::getBestYmove(int entityY, int playerY) {
	if (entityY > playerY)
		return UP;
	else if (entityY < playerY)
		return DOWN;

	return STAY;
}

std::vector<int> Entity::getBestMoves(Coordinates entityCoord, Coordinates playerCoord) {
	std::vector<int> bestMoves;

	int bestXmove = this->getBestXmove(entityCoord.x, playerCoord.x);
	int bestYmove = this->getBestYmove(entityCoord.y, playerCoord.y);

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

std::vector<int> Entity::getAvailableMoves(EntityGrid *entityGrid, LevelGrid *levelGrid, Coordinates entityCoord) {
	std::vector<int> moves = { LEFT, RIGHT, UP, DOWN };
	std::vector<int> availableMoves;

	for (size_t i = 0; i < moves.size(); ++i) {
		if (this->isValidMove(levelGrid, entityCoord, moves[i])
			&& this->isTileEmpty(entityGrid, moves[i]))
			availableMoves.push_back(moves[i]);
	}

	return availableMoves;
}
