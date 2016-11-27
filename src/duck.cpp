#include "duck.h"

bool isTargetInRange (int range, int target, int start) {
	int lowerLimit = start - range;
	int upperLimit = start + range;
	return lowerLimit < target < upperLimit;
}

std::vector<Coordinates> getGridAroundEntity(int range, int startX, int startY) {
	std::vector<Coordinates> coordVec;
	int lowerX = startX - range;
	int upperX = startX + range;
	int lowerY = startY - range;
	int upperY = startY + range;
	
	for (int i = lowerY; i <= upperY; i++) {
		for (int j = lowerX; j <= upperX; j++) {
			coordVec.push_back(Coordinates(i, j));
		}
	}

	return coordVec;
}

bool isCoordMatched(std::vector<Coordinates> coordVec, Coordinates target) {
	for (size_t i = 0; i < coordVec.size(); i++) {
		if (target == coordVec[i]) {
			return true;
		}
	}

	return false;
}

Coordinates moveTowardsTarget (Coordinates target, Coordinates start) {
	if (start.x != target.x) {
		if (start.x < target.x) 
			return Coordinates(start.x + 1, start.y);
		else 
			return Coordinates(start.x - 1, start.y);
	}
	else {
		if (start.y < target.y)
			return Coordinates(start.x, start.y + 1);
		else
			return Coordinates(start.x, start.y - 1);
	}
}

int findDirectionOfTarget(Coordinates target, Coordinates start) {
	int direction = -1;

	if (start.y == target.y) {
		if (start.x > target.x)
			direction = LEFT;
		else
			direction = RIGHT;
	}

	if (start.x == target.x) {
		if (start.y > target.y)
			direction = DOWN;
		else
			direction = UP;
	}

	return direction;
}

Duck::Duck() : Entity() {
	this->setFrameDelay(DUCK_ANIMATION_DELAY);
	this->setLoop(false);
}

Duck::~Duck() {}

void Duck::update(float frameTime, LevelGrid *levelGrid, Player player, Input *input, std::map<std::string, bool> *keysPressed) {
	Entity::update(frameTime);

	if (this->getAnimationComplete()) {
		// Clean up
		this->setFrames(0, 0);
		this->setCurrentFrame(DUCK_STANDING_FRAME);
	}
	if (input->isKeyDown(LEFT_KEY) && !(*keysPressed)["LEFT"]) {
		if (player.isValidMove(levelGrid, LEFT)) {
			this->setX(this->getX() + TILE_SIZE * SCALE);
			this->rotateEntity("LEFT", true);
		}
	}

	if (input->isKeyDown(RIGHT_KEY) && !(*keysPressed)["RIGHT"]) {
		if (player.isValidMove(levelGrid, RIGHT)) {
			this->setX(this->getX() - TILE_SIZE * SCALE);
			this->rotateEntity("RIGHT", true);
		}
	}

	if (input->isKeyDown(UP_KEY) && !(*keysPressed)["UP"]) {
		if (player.isValidMove(levelGrid, UP)) {
			this->setY(this->getY() + TILE_SIZE * SCALE);
			this->rotateEntity("UP", true);
		}
	}

	if (input->isKeyDown(DOWN_KEY) && !(*keysPressed)["DOWN"]) {
		if (player.isValidMove(levelGrid, DOWN)) {
			this->setY(this->getY() - TILE_SIZE * SCALE);
			this->rotateEntity("DOWN", true);
		}
	}
}

void Duck::ai(float frameTime, Player *player, LevelGrid *lvlGrid) {
	// draw a 3 * 3 grid around Duck
	Coordinates duckTC = lvlGrid->convertXYToCoord(this->getX(), this->getY());
	Coordinates playerTC = lvlGrid->convertXYToCoord(player->getX(), player->getY());

	std::vector<Coordinates> pointsToBeMatched = getGridAroundEntity(2, duckTC.x, duckTC.y);
	bool targetDetected = isCoordMatched(pointsToBeMatched, playerTC);

	std::vector<Coordinates> duckAtkRange;
	Coordinates currentPost;
	bool targetInRange;
	int directionOfTarget;

	if (targetDetected) {
		// move towards target, find direction to move
		currentPost = Coordinates(duckTC.x, duckTC.y);
		for (int i = 0; i < this->getMoves(); i++) {
			// check if target is around entity
			duckAtkRange = getGridAroundEntity(this->getAtkRange(), currentPost.x, currentPost.y);
			targetInRange = isCoordMatched(duckAtkRange, playerTC);

			if (targetInRange) {
				// attack target
				directionOfTarget = findDirectionOfTarget(playerTC, currentPost);
				this->rotateEntity(directionOfTarget);
			}
		}
	}
	else {
		// move randomly
	}
}

void Duck::rotateEntity(std::string direction, bool moveValid) {
	RECT sampleRect = this->getSpriteDataRect();

	if (direction != "") {
		sampleRect.left = 0;
		sampleRect.right = TILE_SIZE;

		if (direction == "LEFT")
			sampleRect.top = 64;
		if (direction == "RIGHT")
			sampleRect.top = 96;
		if (direction == "UP")
			sampleRect.top = 32;
		if (direction == "DOWN")
			sampleRect.top = 0;

		sampleRect.bottom = sampleRect.top + TILE_SIZE;

		if (moveValid) {
			startWalkAnimation();
		}
	}

	this->setSpriteDataRect(sampleRect);
}

void Duck::startWalkAnimation() {
	this->setFrames(DUCK_WALK_START_FRAME, DUCK_WALK_END_FRAME);
	this->setCurrentFrame(DUCK_WALK_START_FRAME);
}

void Duck::startAttackAnimation() {
	this->setFrames(DUCK_ATK_START_FRAME, DUCK_ATK_END_FRAME);
	this->setCurrentFrame(DUCK_ATK_START_FRAME);
}

bool Duck::isValidMove(LevelGrid *levelGrid, int direction) {
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

