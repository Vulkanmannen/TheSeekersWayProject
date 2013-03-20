#include "State.h"
#include "IntroScreen.h"
#include "StartMenu.h"
#include "GameMenu.h"
#include "PauseMenu.h"
#include "Sounds.h"
#include "DialogState.h"
#include "Dialogue.h"
#include "LevelManager.h"
#include "VideoState.h"

State* State::sInstance = 0;

State::State():
	mMenuStates(MyVideoState),
	mEsc()
{
	IntroSplash = new IntroScreen();
	mStartMenu = new StartMenu();
	mGameMenu = new GameMenu();
	mPauseMenu = new PauseMenu();
	mDialogState = new DialogState();
	mVideoState = new VideoState();
}


State::~State()
{
	delete IntroSplash;
	delete mStartMenu;
	delete mGameMenu;
	delete mPauseMenu;
	delete mDialogState;
	delete mVideoState;
}

void State::update()
{
	switch(mMenuStates)
	{
	//The Splashscreen
		case Intro:
			IntroSplash->render();
			IntroSplash->update();
			if(mIntroClock.getElapsedTime().asSeconds() > 10.7)
			{
				Sounds::getInstance()->setMasterVolume(Sounds::getInstance()->getMasterVolume() - 1);
			}
			if(mIntroClock.getElapsedTime().asSeconds() > 12 
				|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)))
			{
				mMenuStates = StartState;
				Sounds::getInstance()->StopAll();
				mEsc = false;
				Sounds::getInstance()->setMasterVolume(100);
				Sounds::getInstance()->Loop("Meny.wav");
			}
			break;

	//The StartMenu State
		case StartState:
			if(Sounds::getInstance()->getMasterVolume() < 100)
			{
				Sounds::getInstance()->setMasterVolume(Sounds::getInstance()->getMasterVolume() + 1);
			}
			mStartMenu->render();
			mStartMenu->update();
			break;

	//The Game state
		case GameState:
			mGameMenu->render();
			mGameMenu->update();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && mEsc == true)
			{
				mMenuStates = PauseState;
				mEsc = false;
			}
			break;

	//the PauseMenu State
		case PauseState:
			mPauseMenu->render();
			mPauseMenu->update();
			if(mPauseMenu->HowToPlayInst() == false && mEsc == true)
			{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && mEsc == true)
				{
					mMenuStates = GameState;
					mEsc = false;
					mPauseMenu->setCurrentButton();
				}
			}
			break;

	// dialogstate
		case DialogueState:
			//mGameMenu->render();

			mDialogState->render();
			mDialogState->update();

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && mEsc)
			{
				mEsc = false;
			}
			break;
		case MyVideoState:

			mVideoState->render();
			mVideoState->update();


			break;
	}

	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		mEsc = true;
	}
}

void State::render()
{

}

State* State::getInstance()
{
	if(sInstance == 0)
	{
		sInstance = new State();
	}
	return sInstance;
}

void State::setState(MenuStates menustate)
{
	MenuStates lastState = mMenuStates;
	mMenuStates = menustate;
	mStartMenu->SetCanPressToFalse();
	mPauseMenu->SetCanPressToFalse();

	if(menustate == MyVideoState)
	{
		if(lastState == StartState)
		{
			mVideoState->newMovie(1);
		}
		else
		{
			mVideoState->newMovie(LevelManager::getInstance()->getCurrentLevel() + 2);
		}
			//mVideoState->setVideo(LevelManager::getInstance()->getCurrentLevel());
	}

	if(menustate == DialogueState)
	{
		mDialogState->restartClock();
		if(mDialogState->getStartDialogue())
		{
			mDialogState->setToBlack();
			mDialogState->reset();
		}
	}
}

bool State::getExit()
{
	return mStartMenu->getExit();
}

void State::setmEsc(bool bol)
{
	mEsc = bol;
}