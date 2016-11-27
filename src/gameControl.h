#ifndef _GAMECONTROL_H
#define _GAMECONTROL_H

#include <vector>

#include "player.h"
#include "entity.h"

enum class GAME_STATE : char {
	player = 'p',
	enemy = 'e',
};

class GameControl {
private:
	int turnsElapsed;
	Player *player;
	std::vector<Entity> enemyVector;
	GAME_STATE gameState;

	// internal turn phase
	int pMovesLeft;
	int eMovesLeft;

public:
	GameControl();
	~GameControl();

	// getters
	int getTurnsElapsed() const { return turnsElapsed; }
	GAME_STATE getGameState() const { return gameState; }
	int getPMovesLeft() const { return pMovesLeft; }
	int getEMovesLeft() const { return eMovesLeft; }

	// setters

	bool initialize(Player *player, std::vector<Entity> enemyVector);
};


#endif