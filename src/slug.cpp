#include "slug.h"

Slug::Slug() : Entity() {
	this->setFrameDelay(SLUG_ANIMATION_DELAY);
	this->setLoop(false);
}

Slug::~Slug() {}

void Slug::update(float frameTime, LevelGrid *levelGrid, Player player, Input *input, std::map<std::string, bool> *keysPressed) {
	Entity::update(frameTime);

	if (this->getAnimationComplete()) {
		// Clean up
		this->setFrames(0, 0);
		this->setCurrentFrame(SLUG_STANDING_FRAME);
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

void Slug::ai(float frameTime, Entity &ent) {
}

void Slug::rotateEntity(std::string direction, bool moveValid) {
	RECT sampleRect = this->getSpriteDataRect();

	if (direction != "") {
		sampleRect.left = 0;
		sampleRect.right = TILE_SIZE;

		if (direction == "LEFT")
			sampleRect.top = 64;
		if (direction == "RIGHT")
			sampleRect.top = 96;
		if (direction == "UP")
			sampleRect.top = 32;
		if (direction == "DOWN")
			sampleRect.top = 0;

		sampleRect.bottom = sampleRect.top + TILE_SIZE;

		if (moveValid) {
			startWalkAnimation();
		}
	}

	this->setSpriteDataRect(sampleRect);
}

void Slug::startWalkAnimation() {
	this->setFrames(SLUG_WALK_START_FRAME, SLUG_WALK_END_FRAME);
	this->setCurrentFrame(SLUG_WALK_START_FRAME);
}

void Slug::startAttackAnimation() {
	this->setFrames(SLUG_ATK_START_FRAME, SLUG_ATK_END_FRAME);
	this->setCurrentFrame(SLUG_ATK_START_FRAME);
}