#include "ghost.h"

Ghost::Ghost() : Entity() {
	this->setFrameDelay(GHOST_ANIMATION_DELAY);
	this->setLoop(false);
}

Ghost::~Ghost() {}

void Ghost::update(float frameTime, LevelGrid *levelGrid, Player player, Input *input, std::map<std::string, bool> *keysPressed) {
	Entity::update(frameTime);

	if (this->getAnimationComplete()) {
		// Clean up
		this->setFrames(0, 0);
		this->setCurrentFrame(DUCK_STANDING_FRAME);
	}
	if (input->isKeyDown(LEFT_KEY) && !(*keysPressed)["LEFT"]) {
		if (player.isValidMove(levelGrid, LEFT)) {
			this->setX(this->getX() + TILE_SIZE * SCALE);
			this->rotateEntity("LEFT", true);
		}
	}

	if (input->isKeyDown(RIGHT_KEY) && !(*keysPressed)["RIGHT"]) {
		if (player.isValidMove(levelGrid, RIGHT)) {
			this->setX(this->getX() - TILE_SIZE * SCALE);
			this->rotateEntity("RIGHT", true);
		}
	}

	if (input->isKeyDown(UP_KEY) && !(*keysPressed)["UP"]) {
		if (player.isValidMove(levelGrid, UP)) {
			this->setY(this->getY() + TILE_SIZE * SCALE);
			this->rotateEntity("UP", true);
		}
	}

	if (input->isKeyDown(DOWN_KEY) && !(*keysPressed)["DOWN"]) {
		if (player.isValidMove(levelGrid, DOWN)) {
			this->setY(this->getY() - TILE_SIZE * SCALE);
			this->rotateEntity("DOWN", true);
		}
	}
}

void Ghost::ai(float frameTime, Entity &ent) {
}

void Ghost::rotateEntity(std::string direction, bool moveValid) {
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

		if (moveValid) {
			startWalkAnimation();
		}
	}

	this->setSpriteDataRect(sampleRect);
}

void Ghost::startWalkAnimation() {
	this->setFrames(GHOST_WALK_START_FRAME, GHOST_WALK_END_FRAME);
	this->setCurrentFrame(GHOST_WALK_START_FRAME);
}

void Ghost::startAttackAnimation() {
	this->setFrames(GHOST_ATK_START_FRAME, GHOST_ATK_END_FRAME);
	this->setCurrentFrame(GHOST_ATK_START_FRAME);
}