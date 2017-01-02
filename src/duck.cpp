#include "duck.h"

Duck::Duck() : Entity() {
	this->setFrameDelay(duckNS::DUCK_ANIMATION_DELAY);
	this->setLoop(false);
}

Duck::~Duck() {}

void Duck::update(float frameTime) {
	if (this->getAnimationComplete()) {
		this->setFrames(0, 0);
		this->setCurrentFrame(duckNS::DUCK_STANDING_FRAME);
		this->setAnimationComplete(false);

		if (this->getHealth() <= 0.0) {
			this->startDeathAnimation();
		}
	}

	if (this->getCurrentFrame() == duckNS::DUCK_HURT_FRAME) {
		this->setTimer(this->getTimer() + frameTime);

		if (this->getTimer() > 0.2) {
			this->setTimer(0.0f);
			this->setAnimationComplete(true);
		}
	}

	Entity::update(frameTime);
}

void Duck::startAttackAnimation() {
	this->setFrames(duckNS::DUCK_ATK_START_FRAME, duckNS::DUCK_ATK_END_FRAME);
	this->setCurrentFrame(duckNS::DUCK_ATK_START_FRAME);
}

void Duck::startWalkAnimation() {
	this->setFrames(duckNS::DUCK_WALK_START_FRAME, duckNS::DUCK_WALK_END_FRAME);
	this->setCurrentFrame(duckNS::DUCK_WALK_START_FRAME);
}

void Duck::startHurtAnimation() {
	this->setCurrentFrame(duckNS::DUCK_HURT_FRAME);
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

