#include "gameControl.h"

GameControl::GameControl() {
	generalState = GENERAL_STATE::menu;
	//generalState = GENERAL_STATE::game;
	gameState = GAME_STATE::player;
	turnsElapsed = 0;
	enemyAnimating = false;
	enemyAiInitialized = false;
}

void GameControl::damageEnemy(int id) {
	Entity* entityPtr = this->getPtrToEntity(id);
	float newHealth = entityPtr->getHealth() - player->getDamage();

	entityPtr->startHurtAnimation();
	entityPtr->setHealth(newHealth);

	if (entityPtr->getHealth() > 0)
		PlaySound(HIT_SOUND, NULL, SND_ASYNC);
}

void GameControl::damagePlayer(int id) {
	Entity* entityPtr = this->getPtrToEntity(id);
	float newHealth = player->getHealth() - entityPtr->getDamage();

	player->setHealth(newHealth);

	if (newHealth <= 0)
	{
		generalState = GENERAL_STATE::gameOver;
		PlaySound(GAME_OVER_SOUND, NULL, SND_ASYNC);
	}		
}

void GameControl::cleanupEnemy(EntityGrid *entityGrid) {
	std::vector<Entity*> mv = this->getMonsterVec();
	std::vector<int> indexToRemove;

	for (size_t i = 0; i < mv.size(); i++) {
		if (mv[i]->getHealth() <= 0.0f) {
			mv[i]->setVisible(false);
			entityGrid->removeEntity(mv[i]->getId());
			indexToRemove.push_back(i);
			mv[i] = NULL;
			PlaySound(DIE_SOUND, NULL, SND_ASYNC);
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