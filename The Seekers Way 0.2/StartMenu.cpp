#include "StartMenu.h"
#include "ImageManager.h"
#include "SFML\Graphics.hpp"
#include "LevelManager.h"
#include "State.h"
#include "Sounds.h"
#include "EntityManager.h"


StartMenu::StartMenu():
	canPress(true),
	canPressReturn(false),
	exit(false),
	HowToPlay(false),
	Resumedraw(true),
	currentButton(1)
{	
	mStartText.loadFromImage(*ImageManager::getImage("StartMenurelease.PNG"));
	mStartSprite.setTexture(mStartText);
	mHowToPlay.loadFromImage(*ImageManager::getImage("HowToPlayinst.png"));
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

	updateButtons();
	buttonActivate();
}

void StartMenu::render()
{ 	
	mStartSprite.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(512, 360));
	ImageManager::render(&mStartSprite);
	renderButtons();
	updateButtons();
	if(HowToPlay == true)
	{
		mHowToPlaySprite.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(400, 300));
		ImageManager::render(&mHowToPlaySprite);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			HowToPlay = false;
		}
	} 
}


void StartMenu::generateButtons()
{
		Animation animation("StartResume.PNG", 80, 1, 64, 192);
		updateButtons();
		mButtons.push_back(animation);

		Animation animation2("StartNewGame.PNG", 80, 1, 64, 192);
		updateButtons();
		mButtons.push_back(animation2);

		Animation animation3("StartHowtoPlay.PNG", 80, 1, 64, 192);
		updateButtons();
		mButtons.push_back(animation3);

		//Animation animation4("StartAudio.png", 80, 1, 64, 192);
		//updateButtons();
		//mButtons.push_back(animation4);

		Animation animation5("StartQuit.PNG", 80, 1, 64, 192);
		updateButtons();
		mButtons.push_back(animation5);
}

void StartMenu::updateButtons()
{
	for(std::vector<Animation>::size_type i = 0 + Resumedraw; i < mButtons.size(); i++)
	{
		mButtons[i].setPosition(mStartSprite.getPosition() + sf::Vector2f(420, 180 + i*70));
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
		currentButton = 0 + Resumedraw;
	}
	else if(currentButton < 0 + Resumedraw)
	{
		currentButton = static_cast<int>(mButtons.size()) -1;
	}
}

void StartMenu::renderButtons()
{
	for(auto i = mButtons.begin() + Resumedraw; i != mButtons.end(); i++)
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
				if(Resumedraw == false)
				{
					Sounds::getInstance()->setMasterVolume(Sounds::getInstance()->getMasterVolume() - 1);
					LevelManager::getInstance()->LoadLevel();
					Sounds::getInstance()->StopAll();
					State::getInstance()->setState(State::GameState);
				}
				break;

			case 1:
				Sounds::getInstance()->setMasterVolume(Sounds::getInstance()->getMasterVolume() - 1);
				LevelManager::getInstance()->LoadLevel(0);
				Sounds::getInstance()->StopAll();
				//State::getInstance()->setState(State::MyVideoState);
				State::getInstance()->setState(State::DialogueState);
				Resumedraw = false;
				break;

			case 2:
				HowToPlay = !HowToPlay;
				break; 

			//case 3:
			//	break;

			case 3:
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