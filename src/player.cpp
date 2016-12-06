#include "player.h"

Player::Player() : Entity() {
	this->setFrameDelay(PLAYER_ANIMATION_DELAY);
	this->setLoop(false);
	animating = false;
	endPoint = 0.0f;

	spriteData.x = playerNS::X;
	spriteData.y = playerNS::Y;
}

Player::~Player() {}

void Player::update(float frameTime, GameControl* gc) {
	if (this->getAnimationComplete()) {
		// Clean up
		this->setFrames(0, 0);
		this->setCurrentFrame(PLAYER_STANDING_FRAME);

		// Attack loop is done
		if (this->getAction() == ATTACK) {
			gc->damageEnemy();
		}
	}

	if (this->getMovesLeft() == 0) {
		gc->setGameState(GAME_STATE::enemy);
	}

	Entity::update(frameTime);
}

void Player::startWalkAnimation() {
	this->setFrames(PLAYER_WALK_START_FRAME, PLAYER_WALK_END_FRAME);
	this->setCurrentFrame(PLAYER_WALK_START_FRAME);
}

void Player::startAttackAnimation() {
	this->setFrameDelay(1.0);
	this->setFrames(PLAYER_ATK_START_FRAME, PLAYER_ATK_END_FRAME);
	this->setCurrentFrame(PLAYER_ATK_START_FRAME);
}

bool Player::isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction) {
	int currTileValue = levelGrid->getTileValueAtCoordinates(currCoord);
	int nextTileValue = levelGrid->getNextTileValue(currCoord, direction);

	bool valid = false;

	if (currTileValue == 1)									// 1st floor
		valid = nextTileValue == 1 || nextTileValue == 3;	// 1st floor or stairs
	else if (currTileValue == 2)							// 2nd floor
		valid = nextTileValue == 2 || nextTileValue == 3;	// 2nd floor or stairs
	else if (currTileValue == 3)							// Stairs
		valid = nextTileValue == 1 || nextTileValue == 2 || nextTileValue == 3;	// 1st floor or 2nd floor or stairs

	return valid;
}

void Player::moveInDirection(LevelGrid *levelGrid, EntityGrid *entityGrid, 
	int direction, float endPoint, GameControl* gc) {
	this->rotateEntity(direction);

	Coordinates currCoord = entityGrid->getPlayerCoordinates();
	Coordinates nextCoord = levelGrid->getNextTileCoordinates(currCoord, direction);
	int nextTileValue = entityGrid->getTileValueAtCoordinates(nextCoord);

	// Check if there is a mosnter on the next tile
	if (nextTileValue > PLAYER_ID) {
		this->setAction(ATTACK);
		this->startAttackAnimation();
		this->setAnimating(true);
		PlaySound(SLASH_SOUND, NULL, SND_ASYNC);
		gc->setEnemyAttackedId(nextTileValue);

		this->logAction();
		printf("Monster attacked: %i\n", nextTileValue);
	}

	// Check if player can move to next tile
	else if (this->isValidMove(levelGrid, currCoord, direction) && nextTileValue == 0) {
		entityGrid->moveEntity(currCoord, nextCoord);
		this->setAction(direction);
		this->startWalkAnimation();
		this->setAnimating(true);
		this->setEndPoint(endPoint);

		this->logAction();
	}
}