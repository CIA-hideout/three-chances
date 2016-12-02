#include "entity.h"

int currentId = 0;

Entity::Entity() : Image() {
	timer = 0.0;
	animating = false;
	action = -1;
}

Entity::~Entity() {
}

bool Entity::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM, EntityData ed) {
	currentId++;

	health = ed.health;
	damage = ed.damage;
	atkRange = ed.atkRange;
	moves = ed.moves;
	movesLeft = ed.moves;
	levels = ed.levels;
	abilities = ed.abilities;
	id = currentId;
	action = -1;

	this->setScale((float)SCALE);

	return(Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

void Entity::update(float frameTime) {
	// Call the base image update func to update the screen
	Image::update(frameTime);
}

void Entity::ai(float frameTime, Entity &ent) {}

void Entity::rotateEntity(int direction) {
	RECT sampleRect = this->getSpriteDataRect();

	if (direction != -1) {
		sampleRect.left = 0;
		sampleRect.right = TILE_SIZE;

		if (direction == LEFT)
			sampleRect.top = 64;
		if (direction == RIGHT)
			sampleRect.top = 96;
		if (direction == UP)
			sampleRect.top = 32;
		if (direction == DOWN)
			sampleRect.top = 0;

		sampleRect.bottom = sampleRect.top + TILE_SIZE;
	}

	this->setSpriteDataRect(sampleRect);
}

void Entity::setRect() {
	spriteData.rect.left = currentFrame * spriteData.width;
	spriteData.rect.right = spriteData.rect.left + spriteData.width;
}

void Entity::moveExecuted() {
	this->setMovesLeft(this->getMovesLeft() - 1);
}

void Entity::resetMovesLeft() {
	this->setMovesLeft(this->getMoves());
}

bool Entity::moveInDirection(float frameTime, int direction, Position endPos) {
	bool reachedEndPoint = false;

	switch (direction) {
	case LEFT:
		if (this->getX() > endPos.x) {
			this->setX(this->getX() - VELOCITY * frameTime);
		}
		else {
			this->setX(endPos.x);
			reachedEndPoint = true;
		}
		break;
	case RIGHT:
		if (this->getX() < endPos.x) {
			this->setX(this->getX() + VELOCITY * frameTime);
		}
		else {
			this->setX(endPos.x);
			reachedEndPoint = true;
		}
		break;

	case UP:
		if (this->getY() > endPos.y) {
			this->setY(this->getY() - VELOCITY * frameTime);
		}
		else {
			this->setY(endPos.y);
			reachedEndPoint = true;
		}
		break;

	case DOWN:
		if (this->getY() < endPos.y) {
			this->setY(this->getY() + VELOCITY * frameTime);
		}
		else {
			this->setY(endPos.y);
			reachedEndPoint = true;
		}
		break;
	}

	return reachedEndPoint;
}

bool Entity::aiMoveInDirection(float frameTime, int direction, Position endPos) {
	if (!this->getAnimating())
		return false;
	else
		return moveInDirection(frameTime, direction, endPos);
}
