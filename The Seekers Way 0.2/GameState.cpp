#include "GameState.h"
#include "EntityManager.h"


GameState::GameState()
{
}


GameState::~GameState()
{
}

void GameState::update()
{
	EntityManager::getInstance()->update();
	EntityManager::getInstance()->updatePrimaryCharacter();
}

void GameState::render()
{
	EntityManager::getInstance()->render();
	//view.setCenter(EntityManager::getInstance()->getCharacterPos());
}