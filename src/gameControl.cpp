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

GAME_STATE GameControl::changeState() {
	if (this->getGameState() == GAME_STATE::player) {
		this->setGameState(GAME_STATE::enemy);
		//std::cout << static_cast<char>(this->getGameState()) << std::endl;
	}

	if (this->getGameState() == GAME_STATE::enemy) {
		this->setGameState(GAME_STATE::player);
	}


	return this->getGameState();
}
