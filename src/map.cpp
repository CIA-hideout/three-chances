#include "map.h"

Map::Map() : Image() {}

Map::~Map() {}

bool Map::initialize(Game *gamePtr, TextureManager *textureM) {
	spriteData.scale = (float)SCALE;
	return(Image::initialize(gamePtr->getGraphics(), 0, 0, 0, textureM));
}

void Map::update(Stage *stage, Player player, Input *input, std::map<std::string, bool> *keysPressed) {
	if (input->isKeyDown(LEFT_KEY) && !(*keysPressed)["LEFT"]) {
		if (this->getX() < 0 && player.isValidMove(stage, LEFT)) {
			this->setX(this->getX() + TILE_SIZE * SCALE);
			stage->moveCurrentTile(LEFT);
			stage->logTile(this->getX(), this->getY());
		}
	}

	if (input->isKeyDown(RIGHT_KEY) && !(*keysPressed)["RIGHT"]) {
		if (-this->getX() < this->getWidth() * SCALE - GAME_WIDTH && player.isValidMove(stage, RIGHT)) {
			this->setX(this->getX() - TILE_SIZE * SCALE);
			stage->moveCurrentTile(RIGHT);
			stage->logTile(this->getX(), this->getY());
		}
	}

	if (input->isKeyDown(UP_KEY) && !(*keysPressed)["UP"]) {
		if (this->getY() < 0 && player.isValidMove(stage, UP)) {
			this->setY(this->getY() + TILE_SIZE * SCALE);
			stage->moveCurrentTile(UP);
			stage->logTile(this->getX(), this->getY());
		}
	}

	if (input->isKeyDown(DOWN_KEY) && !(*keysPressed)["DOWN"]) {
		if (-this->getY() < this->getHeight() * SCALE - GAME_HEIGHT && player.isValidMove(stage, DOWN)) {
			this->setY(this->getY() - TILE_SIZE * SCALE);
			stage->moveCurrentTile(DOWN);
			stage->logTile(this->getX(), this->getY());
		}
	}
}