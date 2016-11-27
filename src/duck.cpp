#include "duck.h"

Duck::Duck() : Entity() {
	this->setFrameDelay(DUCK_ANIMATION_DELAY);
	/*this->setStartFrame(3);
	this->setEndFrame(5);*/
	this->setCurrentFrame(2);
	this->setLoop(false);
}

Duck::~Duck() {}

void Duck::update(float frameTime, LevelGrid *levelGrid, Player player, Input *input, std::map<std::string, bool> *keysPressed) {
	Entity::update(frameTime);

	if (this->getAnimationComplete()) {
		// Clean up
		this->setFrames(0, 0);
		this->setCurrentFrame(DUCK_STANDING_FRAME);
	}
	if (input->isKeyDown(LEFT_KEY) && !(*keysPressed)["LEFT"]) {
		if (player.isValidMove(levelGrid, LEFT)) {
			printf("GET: %f SET: %f", this->getX(), this->getX() + TILE_SIZE * SCALE);
			this->setX(this->getX() + TILE_SIZE * SCALE);
		}
	}

	if (input->isKeyDown(RIGHT_KEY) && !(*keysPressed)["RIGHT"]) {
		if (player.isValidMove(levelGrid, RIGHT)) {
			printf("GET: %f SET: %f", this->getX(), this->getX() + TILE_SIZE * SCALE);
			this->setX(this->getX() - TILE_SIZE * SCALE);
		}
	}

	if (input->isKeyDown(UP_KEY) && !(*keysPressed)["UP"]) {
		if (player.isValidMove(levelGrid, UP)) {
			printf("GET: %f SET: %f", this->getX(), this->getX() + TILE_SIZE * SCALE); 
			this->setY(this->getY() + TILE_SIZE * SCALE);
		}
	}

	if (input->isKeyDown(DOWN_KEY) && !(*keysPressed)["DOWN"]) {
		if (player.isValidMove(levelGrid, DOWN)) {
			printf("GET: %f SET: %f", this->getX(), this->getX() + TILE_SIZE * SCALE); 
			this->setY(this->getY() - TILE_SIZE * SCALE);
		}
	}
}

void Duck::ai(float frameTime, Entity &ent) {
}

void Duck::rotateEntity(std::string direction, bool moveValid) {
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

void Duck::startWalkAnimation() {
	this->setFrames(DUCK_WALK_START_FRAME, DUCK_WALK_END_FRAME);
	this->setCurrentFrame(DUCK_WALK_START_FRAME);
}

void Duck::startAttackAnimation() {
	this->setFrames(DUCK_ATK_START_FRAME, DUCK_ATK_END_FRAME);
	this->setCurrentFrame(DUCK_ATK_START_FRAME);
}