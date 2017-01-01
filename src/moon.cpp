#include "moon.h"

Moon::Moon() : Entity() {
	this->setFrameDelay(MOON_ANIMATION_DELAY);
	this->setLoop(false);
}

Moon::~Moon() {}

void Moon::update(float frameTime) {
	if (this->getAnimationComplete()) {
		this->setFrames(0, 0);
		this->setCurrentFrame(MOON_STANDING_FRAME);
		this->setAnimationComplete(false);

		if (this->getHealth() <= 0.0) {
			this->startDeathAnimation();
		}
	}

	if (this->getCurrentFrame() == MOON_HURT_FRAME) {
		this->setTimer(this->getTimer() + frameTime);

		if (this->getTimer() > 0.2) {
			this->setTimer(0.0f);
			this->setAnimationComplete(true);
		}
	}

	Entity::update(frameTime);
}

void Moon::startAttackAnimation() {
	this->setFrames(MOON_ATK_START_FRAME, MOON_ATK_END_FRAME);
	this->setCurrentFrame(MOON_ATK_START_FRAME);
}

void Moon::startWalkAnimation() {
	this->setFrames(MOON_WALK_START_FRAME, MOON_WALK_END_FRAME);
	this->setCurrentFrame(MOON_WALK_START_FRAME);
}

void Moon::startHurtAnimation() {
	this->setCurrentFrame(MOON_HURT_FRAME);
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