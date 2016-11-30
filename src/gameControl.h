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
	GAME_STATE gameState;
	int turnsElapsed;
	bool enemyAnimating;
	std::vector<Entity*> monsterVec;

public:
	GameControl();
	~GameControl();

	GAME_STATE getGameState() { return gameState; }
	void setGameState(GAME_STATE gs) { turnsElapsed++;  gameState = gs; }
	bool getEnemyAnimating() { return enemyAnimating; }
	void setEnemyAnimating(bool ea) { enemyAnimating = ea; }
	std::vector<Entity*> getMonsterVec() { return monsterVec; }
	void setMonsterVec(std::vector<Entity*> mv) { monsterVec = mv; }
};

#endif