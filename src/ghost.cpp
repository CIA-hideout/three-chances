#include "ghost.h"

Ghost::Ghost() : Entity() {
	this->setFrameDelay(ghostNS::ANIMATION_DELAY);
	this->setLoop(false);
}

Ghost::~Ghost() {}

void Ghost::update(float frameTime) {
	// Need to block stage change and wait till animation is played finish for death
	if (this->getAnimationComplete()) {
		// Clean up
		this->setFrames(0, 0);
		this->setCurrentFrame(ghostNS::STANDING_FRAME);
		this->setAnimationComplete(false);

		if (this->getHealth() <= 0.0) {
			this->startDeathAnimation();
		}
	}

	if (this->getCurrentFrame() == ghostNS::HURT_FRAME) {
		this->setTimer(this->getTimer() + frameTime);

		if (this->getTimer() > 0.2) {
			this->setTimer(0.0f);
			this->setAnimationComplete(true);
		}
	}

	Entity::update(frameTime);
}

void Ghost::startAttackAnimation() {
	this->setFrames(ghostNS::ATK_START_FRAME, ghostNS::ATK_END_FRAME);
	this->setCurrentFrame(ghostNS::ATK_START_FRAME);
}

void Ghost::startWalkAnimation() {
	this->setFrames(ghostNS::WALK_START_FRAME, ghostNS::WALK_END_FRAME);
	this->setCurrentFrame(ghostNS::WALK_START_FRAME);
}

void Ghost::startHurtAnimation() {
	this->setCurrentFrame(ghostNS::HURT_FRAME);
}

void Ghost::startDeathAnimation() {
	this->setVisible(false);
}

// Ghost can pass through obstacles but cannot move pass floors and cannot float on water
bool Ghost::isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction) {
	int currentTileValue = levelGrid->getTileValueAtCoordinates(currCoord);
	int nextTileValue = levelGrid->getNextTileValue(currCoord, direction);

	bool valid = false;

	if (currentTileValue == 1)
		valid = nextTileValue == 1 || nextTileValue == 3 || nextTileValue == 5;
	else if (currentTileValue == 2)
		valid = nextTileValue == 2 || nextTileValue == 3 || nextTileValue == 5;
	else if (currentTileValue == 3)
		valid = nextTileValue == 1 || nextTileValue == 2 || nextTileValue == 3;
	else if (currentTileValue == 5)
		valid = nextTileValue == 1 || nextTileValue == 2 || nextTileValue == 3 || nextTileValue == 5;

	return valid;
}

bool Ghost::isValidSpawn(LevelGrid *levelGrid, Coordinates currCoord) {
	int currentTileValue = levelGrid->getTileValueAtCoordinates(currCoord);
	return currentTileValue != 0 && currentTileValue != 4;
}