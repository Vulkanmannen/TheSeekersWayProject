#include "DialogState.h"
#include "Dialogue.h"
#include "State.h"
#include "EntityManager.h"
#include "LevelManager.h"
#include "ImageManager.h"

DialogState::DialogState():
mEndOfDialouge(false),
mFadeCount(0),
mFadedIn(false),
mFadedThisTime(false)
{
	mTexture.loadFromImage(*ImageManager::getImage("black.png"));
	mSprite.setTexture(mTexture);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
}


DialogState::~DialogState()
{
}

void DialogState::render()
{
	//if(mFadeCount > 10 || mFadedThisTime || !Dialogue::getInstance()->getStartDialogue())
	//{
		//EntityManager::getInstance()->updateView();
		EntityManager::getInstance()->render();
		Dialogue::getInstance()->render();
	//}
	
	fade();
}

void DialogState::fade()
{
	int timeTemp = 0;

	if(mEndOfDialouge)
	{
		if(timeTemp < 255)
		{
			timeTemp = 5 + mFadeCount * 5;
		}

		else
		{
			timeTemp = 255;
		}

		mSprite.setColor(sf::Color(0, 0, 0, timeTemp));
	}


	if(mTimeToFadeIn.getElapsedTime().asSeconds() > 3 && Dialogue::getInstance()->getStartDialogue()/* && !EntityManager::getInstance()->getMovingCamera()*/)
	{
		if(!mFadedIn && Dialogue::getInstance()->getStartDialogue())
		{
			timeTemp = mFadeCount * 5;

			if(timeTemp > 249)
			{
				timeTemp = 255;
				mFadedIn = true;
			}

			mSprite.setColor(sf::Color(0, 0, 0, 255 - timeTemp));
		}
	}
	//else if(Dialogue::getInstance()->getStartDialogue())
	//{
	//	mSprite.setColor(sf::Color(0, 0, 0, 255));
	//}

	mSprite.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(256, 120));
	ImageManager::render(&mSprite);
}

void DialogState::update()
{
	if(mFadedIn || !Dialogue::getInstance()->getStartDialogue())
	{
		Dialogue::getInstance()->update();
	}
	
	//EntityManager::getInstance()->updateView();

	if(Dialogue::getInstance()->getendofDialogue() && Dialogue::getInstance()->getStartDialogue())
	{
		EntityManager::getInstance()->updateCameraLastpos();
		reset();
		State::getInstance()->setState(State::GameState);
	}
	else if(Dialogue::getInstance()->getendofDialogue() && !Dialogue::getInstance()->getStartDialogue())
	{
		mEndOfDialouge = true;
	}

	if(mEndOfDialouge)
	{
		mFadeCount += 1;
		if(mFadeCount > 50)
		{
			State::getInstance()->setState(State::MyVideoState);
			LevelManager::getInstance()->LoadLevel(LevelManager::getInstance()->getCurrentLevel() + 1);
			
			//State::getInstance()->setState(State::DialogueState);
			reset();
		}
	}

	if(mTimeToFadeIn.getElapsedTime().asSeconds() > 3 && !mFadedIn && Dialogue::getInstance()->getStartDialogue()/* && !EntityManager::getInstance()->getMovingCamera()*/)
	{
		mFadeCount += 1;
		if(mFadeCount > 50)
		{
			mFadeCount = 0;	
			mFadedThisTime = true;
		}
 	}
}

void DialogState::reset()
{
	mFadedThisTime = false;
	mEndOfDialouge = false;
	mFadeCount = 0;
	mFadedIn = false;
}

void DialogState::restartClock()
{
	mTimeToFadeIn.restart();
}

void DialogState::setToBlack()
{
	mSprite.setColor(sf::Color(0, 0, 0, 255));
}

bool DialogState::getStartDialogue()
{
	return Dialogue::getInstance()->getStartDialogue();
}