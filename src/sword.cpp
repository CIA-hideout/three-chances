#include "sword.h"

Sword::Sword() : Image() {
	this->setCurrentFrame(1);
}

Sword::~Sword() {}

bool Sword::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	this->setVisible(false);
	this->setX(TILE_SIZE * SCALE * 3);
	this->setY(TILE_SIZE * SCALE * 4);
	this->setScale((float)0.5);
	return (Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

void Sword::setRect() {
	spriteData.rect.left = currentFrame * spriteData.width;
	spriteData.rect.right = spriteData.rect.left + spriteData.width;
}

void Sword::setDirection(int direction, float playerX, float playerY) {
	this->setDegrees(0.0);

	switch (direction) {
	case LEFT:
		this->setCurrentFrame(2);
		this->setX(playerX - TILE_SIZE * SCALE);
		this->setY(playerY);
		break;
	case RIGHT:
		this->setCurrentFrame(3);
		this->setX(playerX + TILE_SIZE * SCALE);
		this->setY(playerY);
		break;
	case UP:
		this->setCurrentFrame(0);
		this->setX(playerX);
		this->setY(playerY - TILE_SIZE * SCALE);
		break;
	case DOWN:
		this->setCurrentFrame(1);
		this->setX(playerX);
		this->setY(playerY + TILE_SIZE * SCALE);
		break;
	}
}

bool Sword::attack(float frameTime) {
	
	this->setDegrees(this->getDegrees() + frameTime * ROTATION_RATE);

	if (this->getDegrees() > 360.0) {
		return true;
	}
	return false;
}

void Sword::finishAnimating(Player *p) {
	p->setAnimating(false);
	p->moveExecuted();
	p->setFrameDelay(PLAYER_ANIMATION_DELAY);
	this->setVisible(false);
}