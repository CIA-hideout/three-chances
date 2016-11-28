#include "sword.h"

Sword::Sword() : Image() {
	this->setCurrentFrame(1);
}

Sword::~Sword() {}

bool Sword::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	this->setScale((float)0.4);
	return (Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

void Sword::setRect() {
	spriteData.rect.left = currentFrame * spriteData.width;
	spriteData.rect.right = spriteData.rect.left + spriteData.width;
}

void Sword::setDirection(int direction) {
	switch (direction) {
	case LEFT:
		this->setCurrentFrame(2);
		break;
	case RIGHT:
		this->setCurrentFrame(3);
		break;
	case UP:
		this->setCurrentFrame(0);
		break;
	case DOWN:
		this->setCurrentFrame(1);
		break;
	}
}

void Sword::rotateSwordCW(float frameTime) {
	if (this->getDegrees() < 45.0)
		this->setDegrees(this->getDegrees() + ROTATION_RATE * frameTime);
}

void Sword::rotateSwordACW(float frameTime) {
	if (this->getDegrees() > -45.0)
		this->setDegrees(this->getDegrees() - ROTATION_RATE * frameTime);
}

void Sword::attack(float frameTime) {
	this->rotateSwordCW(frameTime);
}