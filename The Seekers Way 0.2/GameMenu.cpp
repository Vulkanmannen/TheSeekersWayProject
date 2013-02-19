#include "GameMenu.h"
#include "EntityManager.h"


GameMenu::GameMenu()
{
}


GameMenu::~GameMenu()
{
}

void GameMenu::update()
{
	EntityManager::getInstance()->update();
	EntityManager::getInstance()->updatePrimaryCharacter();
}

void GameMenu::render()
{
	EntityManager::getInstance()->updateView();
	EntityManager::getInstance()->render();
}