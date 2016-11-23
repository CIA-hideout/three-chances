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

	// Initialize image
	input = gamePtr->getInput();
	return(Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

void Entity::update(float frameTime) {
	// Call the base image update func to update the screen
	Image::update(frameTime);
}

void Entity::ai(float frameTime, Entity &ent) {}
