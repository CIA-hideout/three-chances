#include "level.h"

Level::Level() : Image() {}

Level::~Level() {}

bool Level::initialize(Game *gamePtr, TextureManager *textureM) {
	this->setScale((float)SCALE);
	return(Image::initialize(gamePtr->getGraphics(), 0, 0, 0, textureM));
}

void Level::update(LevelGrid *levelGrid, Player *player, Input *input,
	std::map<int, bool> *keysPressed, GameControl *gc, MonsterGrid *mg) {
	if (gc->getGameState() == GAME_STATE::player) {
		if (input->isKeyDown(LEFT_KEY) && !(*keysPressed)[LEFT]) {
			if (player->isValidMove(levelGrid, LEFT)) {
				this->setX(this->getX() + TILE_SIZE * SCALE);
				levelGrid->moveCurrentTile(LEFT);
				mg->moveCamera(LEFT);
				player->moveExecuted();

				levelGrid->logTile(this->getX(), this->getY());
			}
		}

		if (input->isKeyDown(RIGHT_KEY) && !(*keysPressed)[RIGHT]) {
			if (player->isValidMove(levelGrid, RIGHT)) {
				this->setX(this->getX() - TILE_SIZE * SCALE);
				levelGrid->moveCurrentTile(RIGHT);
				mg->moveCamera(RIGHT);
				player->moveExecuted();

				levelGrid->logTile(this->getX(), this->getY());
			}
		}

		if (input->isKeyDown(UP_KEY) && !(*keysPressed)[UP]) {
			if (player->isValidMove(levelGrid, UP)) {
				this->setY(this->getY() + TILE_SIZE * SCALE);
				levelGrid->moveCurrentTile(UP);
				mg->moveCamera(UP);
				player->moveExecuted();

				levelGrid->logTile(this->getX(), this->getY());
			}
		}

		if (input->isKeyDown(DOWN_KEY) && !(*keysPressed)[DOWN]) {
			if (player->isValidMove(levelGrid, DOWN)) {
				this->setY(this->getY() - TILE_SIZE * SCALE);
				levelGrid->moveCurrentTile(DOWN);
				mg->moveCamera(DOWN);
				player->moveExecuted();

				levelGrid->logTile(this->getX(), this->getY());
			}
		}

		if (player->getMovesLeft() == 0) {
			gc->setGameState(GAME_STATE::enemy);
		}
	}
}