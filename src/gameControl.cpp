#include "gameControl.h"

GameControl::GameControl() {
	gameState = GAME_STATE::player;
	turnsElapsed = 0;
	enemyAnimating = false;
}

void GameControl::damageEnemy(float dmgAmt) {
	Entity* entityPtr = this->getPtrToEntity(this->getEnemyAttackedId());
	int newHealth = entityPtr->getHealth() - dmgAmt;
	entityPtr->setHealth(newHealth);

	printf("damage: %f\n", entityPtr->getDamage());
	printf("animationComplete: %s\n", entityPtr->getAnimating());
}

Entity* GameControl::getPtrToEntity(int id) {
	std::vector<Entity*> monterVec = this->getMonsterVec();
	Entity* tempPtr = NULL; 

	for (size_t i = 0; i < monterVec.size(); i++) {
		if (monsterVec[i]->getId() == id) {
			tempPtr = monsterVec[i];
		}
	}

	return tempPtr;
}