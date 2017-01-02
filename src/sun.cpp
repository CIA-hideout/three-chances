#include "sun.h"

Sun::Sun() : Entity() {
	this->setFrameDelay(sunNS::ANIMATION_DELAY);
	this->setLoop(false);
}

Sun::~Sun() {}

void Sun::update(float frameTime) {
	if (this->getAnimationComplete()) {
		this->setFrames(0, 0);
		this->setCurrentFrame(sunNS::STANDING_FRAME);
		this->setAnimationComplete(false);

		if (this->getHealth() <= 0.0) {
			this->startDeathAnimation();
		}
	}

	if (this->getCurrentFrame() == sunNS::HURT_FRAME) {
		this->setTimer(this->getTimer() + frameTime);

		if (this->getTimer() > 0.2) {
			this->setTimer(0.0f);
			this->setAnimationComplete(true);
		}
	}

	Entity::update(frameTime);
}

void Sun::startAttackAnimation() {
	this->setFrames(sunNS::ATK_START_FRAME, sunNS::ATK_END_FRAME);
	this->setCurrentFrame(sunNS::ATK_START_FRAME);
}

void Sun::startWalkAnimation() {
	this->setFrames(sunNS::WALK_START_FRAME, sunNS::WALK_END_FRAME);
	this->setCurrentFrame(sunNS::WALK_START_FRAME);
}

void Sun::startHurtAnimation() {
	this->setCurrentFrame(sunNS::HURT_FRAME);
}

void Sun::startDeathAnimation() {
	this->setVisible(false);
}

bool Sun::isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction) {
	int nextTileValue = levelGrid->getNextTileValue(currCoord, direction);

	bool valid = false;

	// Sun can move anywhere within the borders
	if (nextTileValue != 0)
		return true;

	return valid;
}

bool Sun::isValidSpawn(LevelGrid *levelGrid, Coordinates currCoord) {
	int currentTileValue = levelGrid->getTileValueAtCoordinates(currCoord);
	return currentTileValue != 0;
}