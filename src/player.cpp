#include "player.h"

Player::Player() : Entity() {
	this->setFrameDelay(PLAYER_ANIMATION_DELAY);
	this->setLoop(false);
}

Player::~Player() {}

void Player::update(float frameTime, Input *input, std::map<std::string, bool> *keysPressed) {
	Entity::update(frameTime);

	if (input->isKeyDown(LEFT_KEY) && (*keysPressed)["LEFT"]) {
		this->rotateEntity("LEFT");
	}

	if (input->isKeyDown(RIGHT_KEY) && (*keysPressed)["RIGHT"]) {
		this->rotateEntity("RIGHT");
	}

	if (input->isKeyDown(UP_KEY) && (*keysPressed)["UP"]) {
		this->rotateEntity("UP");
	}

	if (input->isKeyDown(DOWN_KEY) && (*keysPressed)["DOWN"]) {
		this->rotateEntity("DOWN");
	}

	if (this->getAnimationComplete()) {
		// Clean up
		this->setFrames(0, 0);
		this->setCurrentFrame(PLAYER_STANDING_FRAME);
	}
}

void Player::rotateEntity(std::string direction) {
	RECT sampleRect = this->getSpriteDataRect();

	if (direction != "") {
		sampleRect.left = 0;
		sampleRect.right = TILE_SIZE;

		if (direction == "LEFT")
			sampleRect.top = 32;
		if (direction == "RIGHT")
			sampleRect.top = 96;
		if (direction == "UP")
			sampleRect.top = 64;
		if (direction == "DOWN")
			sampleRect.top = 0;

		sampleRect.bottom = sampleRect.top + TILE_SIZE;
		startWalkAnimation();
	}

	this->setSpriteDataRect(sampleRect);
}


void Player::startWalkAnimation() {
	this->setFrames(PLAYER_WALK_START_FRAME, PLAYER_WALK_END_FRAME);
	this->setCurrentFrame(PLAYER_WALK_START_FRAME);
}

void Player::startAttackAnimation() {

}