#include "gameControl.h"

GameControl::GameControl() {
	generalState = GENERAL_STATE::game;
	gameState = GAME_STATE::player;
	turnsElapsed = 0;
	enemyAnimating = false;
}

void GameControl::damageEnemy() {
	Entity* entityPtr = this->getPtrToEntity(this->getEnemyAttackedId());
	float newHealth = entityPtr->getHealth() - player->getDamage();

	entityPtr->startHurtAnimation();
	entityPtr->setHealth(newHealth);
}

void GameControl::damagePlayer(int id) {
	Entity* entityPtr = this->getPtrToEntity(id);
	float newHealth = player->getHealth() - entityPtr->getDamage();

	player->setHealth(newHealth);
	printf("Health: %f", player->getHealth());
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
