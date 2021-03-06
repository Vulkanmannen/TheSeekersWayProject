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
	EntityManager::getInstance()->updatePrimaryCharacter();
	EntityManager::getInstance()->update();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			LevelManager::getInstance()->LoadLevel(0);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			LevelManager::getInstance()->LoadLevel(1);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			LevelManager::getInstance()->LoadLevel(2);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			LevelManager::getInstance()->LoadLevel(3);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			LevelManager::getInstance()->LoadLevel(4);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		{
			LevelManager::getInstance()->LoadLevel(5);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
		{
			LevelManager::getInstance()->LoadLevel(6);
		}
	}
}

void GameMenu::render()
{
	//EntityManager::getInstance()->updateView();
	EntityManager::getInstance()->render();
}