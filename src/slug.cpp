#include "slug.h"

Slug::Slug() : Entity() {
	this->setFrameDelay(SLUG_ANIMATION_DELAY);
	this->setLoop(false);
}

Slug::~Slug() {}

void Slug::update(float frameTime) {
	if (this->getAnimationComplete()) {
		this->setFrames(0, 0);
		this->setCurrentFrame(SLUG_STANDING_FRAME);
		this->setAnimationComplete(false);

		if (this->getHealth() <= 0.0) {
			this->startDeathAnimation();
		}
	}

	if (this->getCurrentFrame() == SLUG_HURT_FRAME) {
		this->setTimer(this->getTimer() + frameTime);

		if (this->getTimer() > 0.2) {
			this->setTimer(0.0f);
			this->setAnimationComplete(true);
		}
	}

	Entity::update(frameTime);
}

void Slug::startAttackAnimation() {
	this->setFrames(SLUG_ATK_START_FRAME, SLUG_ATK_END_FRAME);
	this->setCurrentFrame(SLUG_ATK_START_FRAME);
}

void Slug::startWalkAnimation() {
	this->setFrames(SLUG_WALK_START_FRAME, SLUG_WALK_END_FRAME);
	this->setCurrentFrame(SLUG_WALK_START_FRAME);
}

void Slug::startHurtAnimation() {
	this->setCurrentFrame(SLUG_HURT_FRAME);
}

void Slug::startDeathAnimation() {
	this->setVisible(false);
}

bool Slug::isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction) {
	int currentTileValue = levelGrid->getTileValueAtCoordinates(currCoord);
	int nextTileValue = levelGrid->getNextTileValue(currCoord, direction);

	bool valid = false;

	// Slug can move over lava and land
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

bool Slug::isValidSpawn(LevelGrid *levelGrid, Coordinates currCoord) {
	int currentTileValue = levelGrid->getTileValueAtCoordinates(currCoord);
	return currentTileValue != 0 && currentTileValue != 5;
}

