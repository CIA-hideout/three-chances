#include "duck.h"

//bool operator==(const Coordinates& lhs, const Coordinates& rhs) {
//	return lhs.x == rhs.x && lhs.y == rhs.y;
//}
//
//bool isTargetInRange (int range, int target, int start) {
//	int lowerLimit = start - range;
//	int upperLimit = start + range;
//	return lowerLimit < target && lowerLimit < upperLimit;
//}
//
//std::vector<Coordinates> getGridAroundEntity(int range, int startX, int startY) {
//	std::vector<Coordinates> coordVec;
//	int lowerX = startX - range;
//	int upperX = startX + range;
//	int lowerY = startY - range;
//	int upperY = startY + range;
//
//	for (int i = lowerY; i <= upperY; i++) {
//		for (int j = lowerX; j <= upperX; j++) {
//			coordVec.push_back(Coordinates(j, i));
//		}
//	}
//
//	return coordVec;
//}
//
//std::vector<Coordinates> getSidesOfEntity(int range, int startX, int startY) {
//	std::vector<Coordinates> coordVec;
//	int lowerX = startX - range;
//	int upperX = startX + range;
//	int lowerY = startY - range;
//	int upperY = startY + range;	
//
//	for (int i = lowerY; i <= upperY; i++) {
//		coordVec.push_back(Coordinates(startX, i));
//	}
//
//	for (int j = lowerX; j <= upperX; j++) {
//		coordVec.push_back(Coordinates(j, startY));
//	}
//
//	return coordVec;
//}
//
//bool isCoordMatched(std::vector<Coordinates> coordVec, Coordinates target) {
//	for (size_t i = 0; i < coordVec.size(); i++) {
//		if (target == coordVec[i]) {
//			return true;
//		}
//	}
//
//	return false;
//}
//
//Coordinates findNextPostToTarget (Coordinates target, Coordinates start) {
//	if (start.x != target.x) {
//		if (start.x < target.x)
//			return Coordinates(start.x + 1, start.y);
//		else
//			return Coordinates(start.x - 1, start.y);
//	}
//	else {
//		if (start.y < target.y)
//			return Coordinates(start.x, start.y + 1);
//		else
//			return Coordinates(start.x, start.y - 1);
//	}
//}
//
//int findDirectionOfTarget(Coordinates target, Coordinates start) {
//	int direction = -1;
//
//	if (start.y == target.y) {
//		if (start.x > target.x)
//			direction = LEFT;
//		else
//			direction = RIGHT;
//	}
//
//	if (start.x == target.x) {
//		if (start.y > target.y)
//			direction = DOWN;
//		else
//			direction = UP;
//	}
//
//	return direction;
//}

Duck::Duck() : Entity() {
	this->setFrameDelay(DUCK_ANIMATION_DELAY);
	this->setLoop(false);
}

Duck::~Duck() {}

void Duck::update(float frameTime, MonsterGrid* monsterGrid) {
	//Coordinates duckXY = monsterGrid->findCoord(1);

	//float xMap = monsterGrid->convertXCoord(duckXY.x);
	//float yMap = monsterGrid->convertYCoord(duckXY.y);

	//if (xMap > -1.0 && yMap > -1.0) {
	//	this->setVisible(true);
	//	this->setX(monsterGrid->convertXCoord(duckXY.x));
	//	this->setY(monsterGrid->convertYCoord(duckXY.y));
	//   }
	//else {
	//	this->setVisible(false);
	//}

	if (this->getAnimationComplete()) {
		// Clean up
		this->setFrames(0, 0);
		this->setCurrentFrame(DUCK_STANDING_FRAME);
	}

	Entity::update(frameTime);
}

void Duck::ai(float frameTime, Player *player, LevelGrid *lvlGrid, MonsterGrid *mg) {

	//Coordinates duckTC = mg->findCoord(1);
	////Coordinates playerTC = lvlGrid->convertXYToCoord(player->getX(), player->getY());
	//Coordinates playerTC = Coordinates(mg->convertMapToXCoord(player->getX()),
	//	mg->convertMapToYCoord(player->getY()));

	//std::vector<Coordinates> pointsToBeMatched = getGridAroundEntity(2, duckTC.x, duckTC.y);
	//bool targetDetected = isCoordMatched(pointsToBeMatched, playerTC);

	//std::vector<Coordinates> duckAtkRange;
	//Coordinates currentPost;
	//Coordinates nextPost;
	//bool targetInRange;
	//int directionOfTarget;

	//if (targetDetected) {
	//	// move towards target, find direction to move
	//	currentPost = Coordinates(duckTC.x, duckTC.y);
	//	for (int i = 0; i < this->getMoves(); i++) {
	//		// check if target is around entity
	//		duckAtkRange = getSidesOfEntity(this->getAtkRange(), currentPost.x, currentPost.y);
	//		targetInRange = isCoordMatched(duckAtkRange, playerTC);

	//		if (targetInRange) {
	//			// attack target
	//			directionOfTarget = findDirectionOfTarget(playerTC, currentPost);
	//			this->rotateEntity(directionOfTarget);
	//			this->startAttackAnimation();

	//			// inflict dmg code
	//		}
	//		else {
	//			// add in movement checking code
	//			nextPost = findNextPostToTarget(playerTC, currentPost);
	//			mg->moveMonster(currentPost, nextPost);
	//			/*this->setX(lvlGrid->convertCoordToXY(nextPost.x));
	//			this->setY(lvlGrid->convertCoordToXY(nextPost.y));*/
	//			currentPost = nextPost;
	//		}
	//	}
	//}
	//else {
	//	// move randomly
	//}
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

bool Duck::moveInDirection(float frameTime, int direction, Position endPos) {
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
