#include "duck.h"

Duck::Duck() : Entity() {
	this->setFrameDelay(DUCK_ANIMATION_DELAY);
	this->setLoop(false);
	animating = false;
}

Duck::~Duck() {}

