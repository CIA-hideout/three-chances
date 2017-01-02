#include "moon.h"

Moon::Moon() : Entity() {
	this->setFrameDelay(moonNS::ANIMATION_DELAY);
	this->setLoop(false);
}

Moon::~Moon() {}

void Moon::update(float frameTime) {
	if (this->getAnimationComplete()) {
		this->setFrames(0, 0);
		this->setCurrentFrame(moonNS::STANDING_FRAME);
		this->setAnimationComplete(false);

		if (this->getHealth() <= 0.0) {
			this->startDeathAnimation();
		}
	}

	if (this->getCurrentFrame() == moonNS::HURT_FRAME) {
		this->setTimer(this->getTimer() + frameTime);

		if (this->getTimer() > 0.2) {
			this->setTimer(0.0f);
			this->setAnimationComplete(true);
		}
	}

	Entity::update(frameTime);
}

void Moon::startAttackAnimation() {
	this->setFrames(moonNS::ATK_START_FRAME, moonNS::ATK_END_FRAME);
	this->setCurrentFrame(moonNS::ATK_START_FRAME);
}

void Moon::startWalkAnimation() {
	this->setFrames(moonNS::WALK_START_FRAME, moonNS::WALK_END_FRAME);
	this->setCurrentFrame(moonNS::WALK_START_FRAME);
}

void Moon::startHurtAnimation() {
	this->setCurrentFrame(moonNS::HURT_FRAME);
}

void Moon::startDeathAnimation() {
	this->setVisible(false);
}

bool Moon::isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction) {
	int nextTileValue = levelGrid->getNextTileValue(currCoord, direction);

	bool valid = false;

	// Moon can move anywhere within the borders
	if (nextTileValue != 0)
		return true;

	return valid;
}

bool Moon::isValidSpawn(LevelGrid *levelGrid, Coordinates currCoord) {
	int currentTileValue = levelGrid->getTileValueAtCoordinates(currCoord);
	return currentTileValue != 0;
}