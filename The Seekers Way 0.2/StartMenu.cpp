#include "StartMenu.h"
#include "ImageManager.h"
#include "SFML\Graphics.hpp"


StartMenu::StartMenu():
	mContinue(false)
{
	mStartText.loadFromFile("StartMenurelease.PNG");
	mStartSprite.setTexture(mStartText);
}


StartMenu::~StartMenu()
{
}

void StartMenu::update()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		mContinue = true;
	}
}

void StartMenu::render()
{
	mStartSprite.setPosition(0, 0);
	ImageManager::render(&mStartSprite);
}

bool StartMenu::GetContinue()
{
	return mContinue;
}