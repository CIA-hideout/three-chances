#include "gameControl.h"

GameControl::GameControl() {
	gameState = GAME_STATE::player;
	turnsElapsed = 0;
	enemyAnimating = false;
}