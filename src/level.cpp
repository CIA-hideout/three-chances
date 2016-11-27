#include "level.h"

Level::Level() : Image() {}

Level::~Level() {}

bool Level::initialize(Game *gamePtr, TextureManager *textureM) {
	this->setScale((float)SCALE);
	return(Image::initialize(gamePtr->getGraphics(), 0, 0, 0, textureM));
}

void Level::update(LevelGrid *levelGrid, Player player, Input *input, std::map<std::string, bool> *keysPressed) {
	if (input->isKeyDown(LEFT_KEY) && !(*keysPressed)["LEFT"]) {
		//if (this->getX() < 0 && player.isValidMove(levelGrid, LEFT)) {
		if (player.isValidMove(levelGrid, LEFT)) {
			this->setX(this->getX() + TILE_SIZE * SCALE);
			levelGrid->moveCurrentTile(LEFT);
			levelGrid->logTile(this->getX(), this->getY());
		}
	}

	if (input->isKeyDown(RIGHT_KEY) && !(*keysPressed)["RIGHT"]) {
		//if (-this->getX() < this->getWidth() * SCALE - GAME_WIDTH && player.isValidMove(levelGrid, RIGHT)) {
			if (player.isValidMove(levelGrid, RIGHT)) {
			this->setX(this->getX() - TILE_SIZE * SCALE);
			levelGrid->moveCurrentTile(RIGHT);
			levelGrid->logTile(this->getX(), this->getY());
		}
	}

	if (input->isKeyDown(UP_KEY) && !(*keysPressed)["UP"]) {
		//if (this->getY() < 0 && player.isValidMove(levelGrid, UP)) {
		if (player.isValidMove(levelGrid, UP)) {
			this->setY(this->getY() + TILE_SIZE * SCALE);
			levelGrid->moveCurrentTile(UP);
			levelGrid->logTile(this->getX(), this->getY());
		}
	}

	if (input->isKeyDown(DOWN_KEY) && !(*keysPressed)["DOWN"]) {
		//if (-this->getY() < this->getHeight() * SCALE - GAME_HEIGHT && player.isValidMove(levelGrid, DOWN)) {
		if (player.isValidMove(levelGrid, DOWN)) {
			this->setY(this->getY() - TILE_SIZE * SCALE);
			levelGrid->moveCurrentTile(DOWN);
			levelGrid->logTile(this->getX(), this->getY());
		}
	}
}