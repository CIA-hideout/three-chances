#ifndef _GHOST_H
#define _GHOST_H

#include <vector>
#include "entity.h"
#include "input.h"
#include "player.h"
#include "levelGrid.h"
#include "monsterGrid.h"
#include "gameControl.h"

class Ghost : public Entity {
public:
	Ghost();
	~Ghost();

	void update(float frameTime);
	
	// ai woes
	void initAi(MonsterGrid *mg, LevelGrid *levelGrid, GameControl *gc);
	bool animateAi(float frameTime, MonsterGrid *mg, Coordinates playerCoord);

	//int ai(float frameTime, MonsterGrid *monsterGrid, LevelGrid *levelGrid);
	void rotateEntity(int direction);
	void startAttackAnimation();
	void startWalkAnimation();
	void startHurtAnimation();
	void startDeathAnimation();

	void logAction();

	bool isValidMove(LevelGrid *levelGrid, Coordinates currCoord, int direction);
	bool isTileEmpty(MonsterGrid *monsterGrid, int direction);

	int getBestXmove(int monsterX, int playerX);
	int getBestYmove(int monsterY, int playerY);

	std::vector<int> getBestMoves(Coordinates monsterCoord, Coordinates playerCoord);
	std::vector<int> getAvailableMoves(MonsterGrid *monsterGrid, LevelGrid *levelGrid, Coordinates monsterCoord);
};
#endif