#include "StartMenu.h"
#include "ImageManager.h"
#include "SFML\Graphics.hpp"
#include "LevelManager.h"
#include "State.h"


StartMenu::StartMenu():
	canPress(true),
	canPressReturn(false),
	exit(false),
	currentButton(0)
{
	mStartText.loadFromFile("StartMenurelease.PNG");
	mStartSprite.setTexture(mStartText);
	generateButtons();
}


StartMenu::~StartMenu()
{
}

void StartMenu::update()
{
	updateCurrentButton();
	changeButton();
	buttonActivate();
}

void StartMenu::render()
{
	mStartSprite.setPosition(0, 0);
	ImageManager::render(&mStartSprite);
	renderButtons();
}

void StartMenu::generateButtons()
{
	for(int i = 0; i < 5; ++i)
	{
		Animation animation("KNAPP.PNG", 80, 1, 46, 123);
		animation.setPosition(sf::Vector2f(450, 200 + i*70));
		mButtons.push_back(animation);
	}
}

void StartMenu::changeButton()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && canPress)
	{
		currentButton++;
		canPress = false;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && canPress)
	{
		currentButton--;
		canPress = false;
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		canPress = true;	
	}


	if(currentButton >= static_cast<int>(mButtons.size()))
	{
		currentButton = 0;
	}
	else if(currentButton < 0)
	{
		currentButton = static_cast<int>(mButtons.size()) -1;
	}
}

void StartMenu::renderButtons()
{
	for(auto i = mButtons.begin(); i != mButtons.end(); i++)
	{
		ImageManager::render(&i->getSprite());
	}
}

void StartMenu::updateCurrentButton()
{
	for(std::vector<Animation>::size_type i = 0; i < mButtons.size(); i++)
	{
		mButtons[i].update(i == currentButton);
	}
}

void StartMenu::buttonActivate()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && canPressReturn)
	{
		switch(currentButton)
		{
			case 0:
				LevelManager::getInstance()->LoadLevel(1);
				State::getInstance()->setState(State::GameState);
				break;

			case 1:
				LevelManager::getInstance()->LoadLevel(2);
				State::getInstance()->setState(State::GameState);
				break;

			case 2:
				LevelManager::getInstance()->LoadLevel(3);
				State::getInstance()->setState(State::GameState);
				break;

			case 3:
				LevelManager::getInstance()->LoadLevel(4);
				State::getInstance()->setState(State::GameState);
				break;

			case 4:
				exit = true;
				break;
		}
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		canPressReturn = true;
	}
}

bool StartMenu::getExit()
{
	return exit;
}

void StartMenu::SetCanPressToFalse()
{
	canPressReturn = false;
}