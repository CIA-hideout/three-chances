#include "level.h"

bool operator==(const Coordinates& lhs, const Coordinates& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

Level::Level() : Image() {
	pathBlocked = false;
}

Level::~Level() {}

bool Level::initialize(Game *gamePtr, int width, int height, int ncols, 
	TextureManager *textureM, Coordinates startTile) {
	// Set map position based off startTile
	float x = -(TILE_SIZE * SCALE * ((float)startTile.x - 3));
	float y = -(TILE_SIZE * SCALE * ((float)startTile.y - 3));

	spriteData.x = x;
	spriteData.y = y;

	startX = x;
	startY = y;

	this->setScale((float)SCALE);
	return(Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

void Level::finishAnimating(LevelGrid *lg, Player *p) {
	// Updates player and levelGrid once the levelGrid sprite has finished moving
	p->setAnimating(false);
	p->moveExecuted();
}

bool Level::moveInDirection(float frameTime, int direction, float endPoint) {
	bool reachedEndPoint = false;
	switch (direction) {
	case LEFT:
		// Keep moving sprite until it reaches end point
		if (this->getX() > endPoint) {
			this->setX(this->getX() - VELOCITY * frameTime);
		}
		// Once it reaches, set sprite to exact end point location for precision
		else {
			this->setX(endPoint);
			reachedEndPoint = true;
		}
		break;

	case RIGHT:
		if (this->getX() < endPoint) {
			this->setX(this->getX() + VELOCITY * frameTime);
		}
		else {
			this->setX(endPoint);
			reachedEndPoint = true;
		}
		break;

	case UP:
		if (this->getY() > endPoint) {
			this->setY(this->getY() - VELOCITY * frameTime);
		}
		else {
			this->setY(endPoint);
			reachedEndPoint = true;
		}
		break;
	case DOWN:
		if (this->getY() < endPoint) {
			this->setY(this->getY() + VELOCITY * frameTime);
		}
		else {
			this->setY(endPoint);
			reachedEndPoint = true;
		}
		break;
	}

	return reachedEndPoint;
}

void Level::removeBlockage() {
	printf("Blockage removed\n");
	this->setPathBlocked(false);
	this->setCurrentFrame(1);
}
