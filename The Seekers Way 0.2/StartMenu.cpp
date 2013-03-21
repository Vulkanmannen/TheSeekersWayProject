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
	currentButton(1),
	mNewGame(false),
	mResume(false),
	mFadeCount(0)
{	
	mStartText.loadFromImage(*ImageManager::getImage("StartMenurelease.PNG"));
	mStartSprite.setTexture(mStartText);
	mHowToPlay.loadFromImage(*ImageManager::getImage("HowToPlayinst.png"));
	mHowToPlaySprite.setTexture(mHowToPlay);
	mBackgroundTexture.loadFromImage(*ImageManager::getImage("Mainmenujournal.png"));
	mBackgroundSprite.setTexture(mBackgroundTexture);
	mBlackTexture.loadFromImage(*ImageManager::getImage("Loading.png"));
	mBlackSprite.setTexture(mBlackTexture);


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

	if(LevelManager::getInstance()->getCurrentLevel() > 0)
	{
		Resumedraw = false;	
	}
	else
	{
		Resumedraw = true;
	}

	updateButtons();
	buttonActivate();
}

void StartMenu::render()
{ 	
	mStartSprite.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(512, 360));
	mBlackSprite.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(512, 360));
	ImageManager::render(&mStartSprite);
	renderButtons();
	updateButtons();
	if(HowToPlay == true)
	{
		mBackgroundSprite.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(512, 360));
		ImageManager::render(&mBackgroundSprite);
		mHowToPlaySprite.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(400, 300));
		ImageManager::render(&mHowToPlaySprite);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			HowToPlay = false;
		}
	} 

	if(mNewGame || mResume)
	{
		ImageManager::render(&mBlackSprite);
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
					mResume = true;
					//Sounds::getInstance()->setMasterVolume(Sounds::getInstance()->getMasterVolume() - 1);
					//LevelManager::getInstance()->LoadLevel();
					//Sounds::getInstance()->StopAll();
					//State::getInstance()->setState(State::GameState);
				}
				break;

			case 1:
				mNewGame = true;
				//Sounds::getInstance()->setMasterVolume(Sounds::getInstance()->getMasterVolume() - 1);
				//LevelManager::getInstance()->LoadLevel(0);
				//Sounds::getInstance()->StopAll();
				////State::getInstance()->setState(State::MyVideoState);
				//State::getInstance()->setState(State::DialogueState);
				////Resumedraw = false;
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

	if(mNewGame)
	{
		mFadeCount += 5;
		if(mFadeCount > 255)
		{
			State::getInstance()->setState(State::MyVideoState);
			mFadeCount = 0;
			Sounds::getInstance()->setMasterVolume(Sounds::getInstance()->getMasterVolume() - 1);
			LevelManager::getInstance()->LoadLevel(0);
			Sounds::getInstance()->StopAll();
			mBlackSprite.setColor(sf::Color(mBlackSprite.getColor().r, mBlackSprite.getColor().r, mBlackSprite.getColor().r, 255));
			
			mNewGame = false;
		}
		else 
		{
			mBlackSprite.setColor(sf::Color(mBlackSprite.getColor().r, mBlackSprite.getColor().r, mBlackSprite.getColor().r, mFadeCount));
		}
	}

	if(mResume)
	{
		mFadeCount +=5;
		if(mFadeCount > 255)
		{
			mFadeCount = 0;
			Sounds::getInstance()->setMasterVolume(Sounds::getInstance()->getMasterVolume() - 1);
			LevelManager::getInstance()->LoadLevel();
			Sounds::getInstance()->StopAll();
			State::getInstance()->setState(State::GameState);
			mBlackSprite.setColor(sf::Color(mBlackSprite.getColor().r, mBlackSprite.getColor().r, mBlackSprite.getColor().r, 255));

			mResume = false;
		}
		else
		{
			mBlackSprite.setColor(sf::Color(mBlackSprite.getColor().r, mBlackSprite.getColor().r, mBlackSprite.getColor().r, mFadeCount));
		}
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