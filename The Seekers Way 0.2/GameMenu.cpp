#include "GameMenu.h"
#include "EntityManager.h"
#include "LevelManager.h"


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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
	{
		LevelManager::getInstance()->LoadLevel(0);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
	{
		LevelManager::getInstance()->LoadLevel(1);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
	{
		LevelManager::getInstance()->LoadLevel(2);
	}
}

void GameMenu::render()
{
	EntityManager::getInstance()->updateView();
	EntityManager::getInstance()->render();
}