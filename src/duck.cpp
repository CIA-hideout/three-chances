#include "duck.h"

Duck::Duck() : Entity() {
	this->setFrameDelay(DUCK_ANIMATION_DELAY);
	this->setLoop(false);
}

Duck::~Duck() {}

void Duck::update(float frameTime) {
	Entity::update(frameTime);

	if (this->getAnimationComplete()) {
		// Clean up
		this->setFrames(0, 0);
		this->setCurrentFrame(DUCK_STANDING_FRAME);
	}
}

void Duck::ai(float frameTime, Entity &ent) {
}

void Duck::startWalkAnimation() {
	this->setFrames(DUCK_WALK_START_FRAME, DUCK_WALK_END_FRAME);
	this->setCurrentFrame(DUCK_WALK_START_FRAME);
}

void Duck::startAttackAnimation() {
	this->setFrames(DUCK_ATK_START_FRAME, DUCK_ATK_END_FRAME);
	this->setCurrentFrame(DUCK_ATK_START_FRAME);
}