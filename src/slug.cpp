#include "slug.h"

Slug::Slug() : Entity() {
	this->setFrameDelay(SLUG_ANIMATION_DELAY);
	this->setLoop(false);
}

Slug::~Slug() {}

void Slug::update(float frameTime, LevelGrid *levelGrid, Player player, Input *input, std::map<std::string, bool> *keysPressed) {
	Entity::update(frameTime);
}

void Slug::ai(float frameTime, Entity &ent) {
}

void Slug::rotateEntity(std::string direction, bool moveValid) {
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

		if (moveValid) {
			startWalkAnimation();
		}
	}

	this->setSpriteDataRect(sampleRect);
}

void Slug::startWalkAnimation() {
	this->setFrames(SLUG_WALK_START_FRAME, SLUG_WALK_END_FRAME);
	this->setCurrentFrame(SLUG_WALK_START_FRAME);
}

void Slug::startAttackAnimation() {
	this->setFrames(SLUG_ATK_START_FRAME, SLUG_ATK_END_FRAME);
	this->setCurrentFrame(SLUG_ATK_START_FRAME);
}