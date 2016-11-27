#include "player.h"

Player::Player() : Entity() {
	this->setFrameDelay(PLAYER_ANIMATION_DELAY);
	this->setLoop(false);
}

Player::~Player() {}

void Player::update(float frameTime, LevelGrid *levelGrid, Input *input,
	std::map<std::string, bool> *keysPressed, GameControl *gameControl) {

	if (gameControl->getGameState() == GAME_STATE::player) {
		if (input->isKeyDown(LEFT_KEY) && !(*keysPressed)["LEFT"]) {
			this->rotateEntity("LEFT", this->isValidMove(levelGrid, LEFT));
		}

		if (input->isKeyDown(RIGHT_KEY) && !(*keysPressed)["RIGHT"]) {
			this->rotateEntity("RIGHT", this->isValidMove(levelGrid, RIGHT));
		}

		if (input->isKeyDown(UP_KEY) && !(*keysPressed)["UP"]) {
			this->rotateEntity("UP", this->isValidMove(levelGrid, UP));
		}

		if (input->isKeyDown(DOWN_KEY) && !(*keysPressed)["DOWN"]) {
			this->rotateEntity("DOWN", this->isValidMove(levelGrid, DOWN));
		}
	}

	if (this->getAnimationComplete()) {
		// Clean up
		this->setFrames(0, 0);
		this->setCurrentFrame(PLAYER_STANDING_FRAME);
	}

	Entity::update(frameTime);
}

void Player::rotateEntity(std::string direction, bool moveValid) {
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

void Player::startWalkAnimation() {
	this->setFrames(PLAYER_WALK_START_FRAME, PLAYER_WALK_END_FRAME);
	this->setCurrentFrame(PLAYER_WALK_START_FRAME);
}

void Player::startAttackAnimation() {}

bool Player::isValidMove(LevelGrid *levelGrid, int direction) {
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
