#include "duck.h"

Duck::Duck() : Entity() {
	this->setFrameDelay(DUCK_ANIMATION_DELAY);
	this->setLoop(false);
	animating = false;
}

Duck::~Duck() {}

void Duck::update(float frameTime, MonsterGrid* monsterGrid) {
	if (this->getAnimationComplete()) {
		// Clean up
		this->setFrames(0, 0);
		this->setCurrentFrame(DUCK_STANDING_FRAME);
	}

	Entity::update(frameTime);
}

void Duck::ai(float frameTime, Player *player, LevelGrid *lvlGrid, MonsterGrid *mg) {
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
