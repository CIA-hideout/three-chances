#include "entity.h"

Entity::Entity() : Image() {}

Entity::~Entity() {}

bool Entity::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM, EntityData ed) {
	health = ed.health;
	damage = ed.damage;
	atkRange = ed.atkRange;
	moves = ed.moves;
	levels = ed.levels;
	abilities = ed.abilities;
	spriteData.scale = (float)SCALE;

	return(Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

void Entity::update(float frameTime) {
	// Call the base image update func to update the screen
	Image::update(frameTime);
}

void Entity::ai(float frameTime, Entity &ent) {}

void Entity::rotateEntity(std::string direction) {
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
	}

	this->setSpriteDataRect(sampleRect);
}

void Entity::setRect() {
	spriteData.rect.left = currentFrame * spriteData.width;
	spriteData.rect.right = spriteData.rect.left + spriteData.width;
}
