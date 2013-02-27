#include "StartMenu.h"
#include "ImageManager.h"
#include "SFML\Graphics.hpp"
#include "LevelManager.h"
#include "State.h"
#include "Sounds.h"


StartMenu::StartMenu():
	canPress(true),
	canPressReturn(false),
	exit(false),
	HowToPlay(false),
	currentButton(0)
{
	mStartText.loadFromFile("StartMenurelease.PNG");
	mStartSprite.setTexture(mStartText);
	mHowToPlay.loadFromFile("HowToPlayinst.png");
	mHowToPlaySprite.setTexture(mHowToPlay);
	generateButtons();
}


StartMenu::~StartMenu()
{
}

void StartMenu::update()
{
	if(HowToPlay == false)
	{
		updateCurrentButton();
		changeButton();
		
	}
	buttonActivate();
}

void StartMenu::render()
{
	mStartSprite.setPosition(0, 0);
	ImageManager::render(&mStartSprite);
	renderButtons();
	if(HowToPlay == true)
	{
		mHowToPlaySprite.setPosition(0, 0);
		ImageManager::render(&mHowToPlaySprite);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			HowToPlay = false;
		}
	}

}

void StartMenu::generateButtons()
{
		Animation animation("Resume.PNG", 80, 1, 64, 192);
		animation.setPosition(sf::Vector2f(450, 100 + 1*70));
		mButtons.push_back(animation);

		Animation animation2("NewGame.PNG", 80, 1, 64, 192);
		animation2.setPosition(sf::Vector2f(450, 100 + 2*70));
		mButtons.push_back(animation2);

		Animation animation3("HowToPlay.PNG", 80, 1, 64, 192);
		animation3.setPosition(sf::Vector2f(450, 100 + 3*70));
		mButtons.push_back(animation3);

		Animation animation4("Audio.png", 80, 1, 64, 192);
		animation4.setPosition(sf::Vector2f(450, 100 + 4*70));
		mButtons.push_back(animation4);

		Animation animation5("Exit.PNG", 80, 1, 64, 192);
		animation5.setPosition(sf::Vector2f(450, 100 + 5*70));
		mButtons.push_back(animation5);
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
		canPressReturn = false;
		switch(currentButton)
		{
			case 0:
				LevelManager::getInstance()->LoadLevel();
				State::getInstance()->setState(State::DialogueState);
				break;

			case 1:
				LevelManager::getInstance()->LoadLevel(0);
				State::getInstance()->setState(State::DialogueState);
				break;

			case 2:
				HowToPlay = !HowToPlay;
				break; 

			case 3:
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