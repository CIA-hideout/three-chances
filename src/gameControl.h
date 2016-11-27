#ifndef _GAMECONTROL_H
#define _GAMECONTROL_H

#include <vector>

#include "entity.h"

enum class GAME_STATE : char {
	player = 'p',
	enemy = 'e',
};

class GameControl {
private:
	int turnsElapsed;
	std::vector<Entity> enemyVector;
	GAME_STATE gameState;

public:
	GameControl();
	~GameControl();

	// getters
	int getTurnsElapsed() const { return turnsElapsed; }
	GAME_STATE getGameState() const { return gameState; }

	// setters
	void setGameState(GAME_STATE gs) { gameState = gs; }

	bool initialize(std::vector<Entity> enemyVector);
	GAME_STATE changeState();
};


#endif