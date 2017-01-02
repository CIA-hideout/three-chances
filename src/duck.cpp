#include "duck.h"

Duck::Duck() : Entity() {
	this->setFrameDelay(duckNS::ANIMATION_DELAY);
	this->setLoop(false);
}

Duck::~Duck() {}

void Duck::update(float frameTime) {
	if (this->getAnimationComplete()) {
		this->setFrames(0, 0);
		this->setCurrentFrame(duckNS::STANDING_FRAME);
		this->setAnimationComplete(false);

		if (this->getHealth() <= 0.0) {
			this->startDeathAnimation();
		}
	}

	if (this->getCurrentFrame() == duckNS::HURT_FRAME) {
		this->setTimer(this->getTimer() + frameTime);

		if (this->getTimer() > 0.2) {
			this->setTimer(0.0f);
			this->setAnimationComplete(true);
		}
	}

	Entity::update(frameTime);
}

void Duck::startAttackAnimation() {
	this->setFrames(duckNS::ATK_START_FRAME, duckNS::ATK_END_FRAME);
	this->setCurrentFrame(duckNS::ATK_START_FRAME);
}

void Duck::startWalkAnimation() {
	this->setFrames(duckNS::WALK_START_FRAME, duckNS::WALK_END_FRAME);
	this->setCurrentFrame(duckNS::WALK_START_FRAME);
}

void Duck::startHurtAnimation() {
	this->setCurrentFrame(duckNS::HURT_FRAME);
}

void Duck::startDeathAnimation() {
	this->setVisible(false);
}

bool Duck::isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction) {
	int currentTileValue = levelGrid->getTileValueAtCoordinates(currCoord);
	int nextTileValue = levelGrid->getNextTileValue(currCoord, direction);
	
	bool valid = false;

	// Duck can move over water and land
	if (currentTileValue == 1)
		valid = nextTileValue == 1 || nextTileValue == 3 || nextTileValue == 4;
	else if (currentTileValue == 2)
		valid = nextTileValue == 2 || nextTileValue == 3;
	else if (currentTileValue == 3)
		valid = nextTileValue == 1 || nextTileValue == 2 || nextTileValue == 3;
	else if (currentTileValue == 4)
		valid = nextTileValue == 1 || nextTileValue == 4;

	return valid;
}

bool Duck::isValidSpawn(LevelGrid *levelGrid, Coordinates currCoord) {
	int currentTileValue = levelGrid->getTileValueAtCoordinates(currCoord);
	return currentTileValue != 0 && currentTileValue != 5;
}

