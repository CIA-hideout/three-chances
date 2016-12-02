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
}

void GameControl::cleanupEnemy(MonsterGrid *mg) {
	std::vector<Entity*> mv = this->getMonsterVec();
	std::vector<int> indexToRemove;

	for (size_t i = 0; i < mv.size(); i++) {
		if (mv[i]->getHealth() <= 0.0f) {
			mv[i]->setVisible(false);
			mg->removeMonster(mv[i]->getId());
			indexToRemove.push_back(i);
			mv[i] = NULL;
		}
	}

	for (size_t i = 0; i < indexToRemove.size(); i++) {
		mv.erase(mv.begin() + indexToRemove[i]);
	}

	this->setMonsterVec(mv);
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

bool GameControl::checkMonstersMovesCompleted() {
	std::vector<Entity*> monterVec = this->getMonsterVec();

	for (size_t i = 0; i < monsterVec.size(); i++) {
		if (monsterVec[i]->getMovesLeft() > 0) {
			return false;
		}
	}

	return true;
}

int GameControl::getMonstersLeft() {
	std::vector<Entity*> monterVec = this->getMonsterVec();
	return monsterVec.size();
}