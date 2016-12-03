#include "player.h"

Player::Player() : Entity() {
	this->setFrameDelay(PLAYER_ANIMATION_DELAY);
	this->setLoop(false);
	animating = false;
	endPoint = 0.0f;

	// Place player in middle of screen
	spriteData.x = TILE_SIZE * SCALE * 3;
	spriteData.y = TILE_SIZE * SCALE * 3;
}

Player::~Player() {}

void Player::update(float frameTime, GameControl* gc) {
	if (this->getAnimationComplete()) {
		// Clean up
		this->setFrames(0, 0);
		this->setCurrentFrame(PLAYER_STANDING_FRAME);

		// Attack loop is done
		if (this->getAction() == ATTACK) {
			this->setAnimating(false);
			this->moveExecuted();
			gc->damageEnemy();
		}
	}

	if (this->getMovesLeft() == 0) {
		gc->setGameState(GAME_STATE::enemy);
	}

	Entity::update(frameTime);
}
 
void Player::rotateEntity(int direction) {
	if (this->getAction() != direction) {
		RECT sampleRect = this->getSpriteDataRect();

		if (direction != -1) {
			sampleRect.left = 0;
			sampleRect.right = TILE_SIZE;

			if (direction == LEFT)
				sampleRect.top = 32;
			if (direction == RIGHT)
				sampleRect.top = 96;
			if (direction == UP)
				sampleRect.top = 64;
			if (direction == DOWN)
				sampleRect.top = 0;

			sampleRect.bottom = sampleRect.top + TILE_SIZE;
		}

		this->setAction(direction);
		this->setSpriteDataRect(sampleRect);
	}
}

void Player::startWalkAnimation() {
	this->setFrames(PLAYER_WALK_START_FRAME, PLAYER_WALK_END_FRAME);
	this->setCurrentFrame(PLAYER_WALK_START_FRAME);
}

void Player::startAttackAnimation() {
	this->setFrames(PLAYER_ATK_START_FRAME, PLAYER_ATK_END_FRAME);
	this->setCurrentFrame(PLAYER_ATK_START_FRAME);
}

bool Player::isValidMove(LevelGrid *levelGrid, int direction) {
	int currentTileValue = levelGrid->getCurrentTileValue();
	int nextTileValue = levelGrid->getNextTileValue(direction);

	bool valid = false;

	if (currentTileValue == 1)								// 1st floor
		valid = nextTileValue == 1 || nextTileValue == 3;	// 1st floor or stairs
	else if (currentTileValue == 2)							// 2nd floor
		valid = nextTileValue == 2 || nextTileValue == 3;	// 2nd floor or stairs
	else if (currentTileValue == 3)							// Stairs
		valid = nextTileValue == 1 || nextTileValue == 2 || nextTileValue == 3;	// 1st floor or 2nd floor

	return valid;
}

void Player::moveInDirection(LevelGrid *levelGrid, MonsterGrid *monsterGrid, 
	int direction, float endPoint, GameControl* gc) {
	this->rotateEntity(direction);
	Coordinates nextCoord = levelGrid->getNextTileCoordinates(direction);
	int nextTileMonsterId = monsterGrid->getValueAtCoordinates(nextCoord);

	// Next tile is walkable
	if (this->isValidMove(levelGrid, direction) && nextTileMonsterId == 0) {
		levelGrid->moveCurrentTile(direction);
		this->startWalkAnimation();
		this->setAnimating(true);
		this->setEndPoint(endPoint);
	}

	// Next tile is monster
	if (nextTileMonsterId > 0) {
		this->setAction(ATTACK);
		this->startAttackAnimation();
		this->setAnimating(true);
		gc->setEnemyAttackedId(nextTileMonsterId);
		printf("next monster tile: %i\n", nextTileMonsterId);
	}
}