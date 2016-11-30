#ifndef _GAMECONTROL_H
#define _GAMECONTROL_H

enum class GAME_STATE : char {
	player = 'p',
	enemy = 'e',
};

class GameControl {
private:
	GAME_STATE gameState;
	int turnsElapsed;
	bool enemyAnimating;

public:
	GameControl();
	~GameControl();

	GAME_STATE getGameState() { return gameState; }
	void setGameState(GAME_STATE gs) { turnsElapsed++;  gameState = gs; }

	bool getEnemyAnimating() { return enemyAnimating; }
	void setEnemyAnimating(bool ea) { enemyAnimating = ea; }
};

#endif