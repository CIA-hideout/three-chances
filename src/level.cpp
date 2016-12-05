#include "level.h"

Level::Level() : Image() {
	// Set map position based off startTile
	spriteData.x = levelNS::X;
	spriteData.y = levelNS::Y;
}

Level::~Level() {}

bool Level::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	pathBlocked = true;
	this->setScale((float)SCALE);
	return(Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

void Level::finishAnimating(LevelGrid *lg, Player *p) {
	// Updates player and levelGrid once the levelGrid sprite has finished moving
	p->setAnimating(false);
	p->moveExecuted();
	lg->logTile(this->getX(), this->getY());
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
