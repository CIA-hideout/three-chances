#ifndef _GAMECONTROL_H
#define _GAMECONTROL_H

#include <queue>
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
	gameClear = 5,
};

class GameControl {
private:
	GENERAL_STATE generalState;
	GAME_STATE gameState;
	int turnsElapsed;
	bool enemyAnimating;
	std::vector<Entity*> monsterVec;
	std::queue<Entity*> animationQueue;
	//int enemyAttackedId;
	Entity* player;
	bool enemyAiInitialized;

public:
	GameControl();
	~GameControl();
	
	// getters
	GENERAL_STATE getGeneralState() { return generalState; }
	GAME_STATE getGameState() { return gameState; }
	bool getEnemyAnimating() { return enemyAnimating; }
	std::vector<Entity*> getMonsterVec() { return monsterVec; }
	std::queue<Entity*> getAnimationQueue() { return animationQueue; }
	bool getEnemyAiInitialized() { return enemyAiInitialized; }
	//int getEnemyAttackedId() { return enemyAttackedId; }
	Entity* getPlayer() { return player; }
	
	// setters
	void setGeneralState(GENERAL_STATE gens) { generalState = gens; }
	void setGameState(GAME_STATE gs) { turnsElapsed++;  gameState = gs; }
	void setEnemyAnimating(bool ea) { enemyAnimating = ea; }
	void setMonsterVec(std::vector<Entity*> mv) { monsterVec = mv; }
	void setAnimationQueue(std::queue<Entity*> aq) { animationQueue = aq; }
	void setEnemyAiInitialized(bool initialized) { enemyAiInitialized = initialized; }
	//void setEnemyAttackedId(int id) { enemyAttackedId = id; }
	void setPlayer(Entity* p) { player = p; }

	void damagePlayer(int id);
	void damageEnemy(int id);
	void cleanupEnemy(EntityGrid *entityGrid);

	// helpers
	Entity* getPtrToEntity(int id);
	bool checkMonstersMovesCompleted();
	int getMonstersLeft();
};

#endif