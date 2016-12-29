#ifndef _GAMECONTROL_H
#define _GAMECONTROL_H

#include <queue>
#include <vector>
#include "audio.h"
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
	Audio* audio;	// pointer to audio 
	int turnsElapsed;
	std::vector<Entity*> monsterVec;
	std::queue<Entity*> animationQueue;
	Entity* player;
	bool enemyAiInitialized;

public:
	GameControl(Audio* audio);
	~GameControl();
	
	// getters
	GENERAL_STATE getGeneralState() { return generalState; }
	GAME_STATE getGameState() { return gameState; }
	std::vector<Entity*> getMonsterVec() { return monsterVec; }
	std::queue<Entity*> getAnimationQueue() { return animationQueue; }
	bool getEnemyAiInitialized() { return enemyAiInitialized; }
	Entity* getPlayer() { return player; }
	
	// setters
	void setGeneralState(GENERAL_STATE gens) { generalState = gens; }
	void setGameState(GAME_STATE gs) { turnsElapsed++;  gameState = gs; }
	void setMonsterVec(std::vector<Entity*> mv) { monsterVec = mv; }
	void setAnimationQueue(std::queue<Entity*> aq) { animationQueue = aq; }
	void setEnemyAiInitialized(bool initialized) { enemyAiInitialized = initialized; }
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