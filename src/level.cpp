#include "level.h"

Level::Level() : Image() {}

Level::~Level() {}

bool Level::initialize(Game *gamePtr, TextureManager *textureM) {
	this->setScale((float)SCALE);
	return(Image::initialize(gamePtr->getGraphics(), 0, 0, 0, textureM));
}

void Level::update(float frameTime, LevelGrid *lg, Player *p, GameControl* gc, int direction) {
	//std::cout << direction << std::endl;

	switch (p->getDirection()) {
		case LEFT:
			if (this->getX() < p->getEndPoint()) {
				this->setX(this->getX() + VELOCITY * frameTime);
			}
			else {
				this->setX(p->getEndPoint());
				p->setAnimating(false);
				p->moveExecuted();
				lg->moveCurrentTile(LEFT);
				lg->logTile(this->getX(), this->getY());
			}
			break;

		case RIGHT:
			if (this->getX() > p->getEndPoint()) {
				this->setX(this->getX() - VELOCITY * frameTime);
			}
			else {
				this->setX(p->getEndPoint());
				p->setAnimating(false);
				p->moveExecuted();
				lg->moveCurrentTile(RIGHT);
				lg->logTile(this->getX(), this->getY());
			}
			break;

		case UP:
			if (this->getY() < p->getEndPoint()) {
				this->setY(this->getY() + VELOCITY * frameTime);
			}
			else {
				this->setY(p->getEndPoint());
				p->setAnimating(false);
				p->moveExecuted();
				lg->moveCurrentTile(UP);
				lg->logTile(this->getX(), this->getY());
			}
			break;

		case DOWN:
			if (this->getY() > p->getEndPoint()) {
				this->setY(this->getY() - VELOCITY * frameTime);
			}
			else { 
				this->setY(p->getEndPoint());	// for precision
				p->setAnimating(false);
				p->moveExecuted();
				lg->moveCurrentTile(DOWN);
				lg->logTile(this->getX(), this->getY());
			}
		}

	if (p->getMovesLeft() == 0) {
		gc->setGameState(GAME_STATE::enemy);
	}
}
