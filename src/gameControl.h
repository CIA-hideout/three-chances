#ifndef _GAMECONTROL_H
#define _GAMECONTROL_H

#include <vector>
#include "entity.h"
#include "entityGrid.h"

enum class GAME_STATE : char {
	player = 'p',
	enemy = 'e',
};

enum class GENERAL_STATE : int {
	menu = 1,
	game = 2,
	paused = 3,
	gameOver = 4,
};

class GameControl {
private:
	GENERAL_STATE generalState;
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
	GENERAL_STATE getGeneralState() { return generalState; }
	GAME_STATE getGameState() { return gameState; }
	bool getEnemyAnimating() { return enemyAnimating; }
	std::vector<Entity*> getMonsterVec() { return monsterVec; }
	int getEnemyAttackedId() { return enemyAttackedId; }
	Entity* getPlayer() { return player; }
	
	// setters
	void setGeneralState(GENERAL_STATE gens) { generalState = gens; }
	void setGameState(GAME_STATE gs) { turnsElapsed++;  gameState = gs; }
	void setEnemyAnimating(bool ea) { enemyAnimating = ea; }
	void setMonsterVec(std::vector<Entity*> mv) { monsterVec = mv; }
	void setEnemyAttackedId(int id) { enemyAttackedId = id; }
	void setPlayer(Entity* p) { player = p; }

	void damagePlayer(int id);
	void damageEnemy();
	void cleanupEnemy(EntityGrid *entityGrid);

	// helpers
	Entity* getPtrToEntity(int id);
	bool checkMonstersMovesCompleted();
	int getMonstersLeft();
};

#endif