#include "gameControl.h"

GameControl::GameControl() {

}

GameControl::~GameControl() {

}

bool GameControl::initialize(Player *p, std::vector<Entity> ev) {
	player = p;
	enemyVector = ev;
	return true;
}