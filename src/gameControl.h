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
	int enemyAttackedId;
	Entity* player;

public:
	GameControl();
	~GameControl();
	
	// getters
	GAME_STATE getGameState() { return gameState; }
	bool getEnemyAnimating() { return enemyAnimating; }
	std::vector<Entity*> getMonsterVec() { return monsterVec; }
	int getEnemyAttackedId() { return enemyAttackedId; }
	Entity* getPlayer() { return player; }
	
	// setters
	void setGameState(GAME_STATE gs) { turnsElapsed++;  gameState = gs; }
	void setEnemyAnimating(bool ea) { enemyAnimating = ea; }
	void setMonsterVec(std::vector<Entity*> mv) { monsterVec = mv; }
	void setEnemyAttackedId(int id) { enemyAttackedId = id; }
	void setPlayer(Entity* p) { player = p; }

	void damagePlayer(int id);
	void damageEnemy();

	// helpers
	Entity* getPtrToEntity(int id);
};

#endif