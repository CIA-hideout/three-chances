#include "gameControl.h"

GameControl::GameControl() {

}

GameControl::~GameControl() {
}

bool GameControl::initialize(std::vector<Entity> ev) {
	gameState = GAME_STATE::player;
	enemyVector = ev;
	return true;
}