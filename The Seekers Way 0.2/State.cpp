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
	mLastState(MyVideoState),
	mCommingState(MyVideoState),
	mEsc(),
	mMusicCount(100)
{
	IntroSplash = new IntroScreen();
	mStartMenu = new StartMenu();
	mGameMenu = new GameMenu();
	mPauseMenu = new PauseMenu();
	mDialogState = new DialogState();
	mVideoState = new VideoState();

	Sounds::getInstance()->setMasterVolume(0);
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
			}
			break;

	//The StartMenu State
		case StartState:
			if(Sounds::getInstance()->getMasterVolume() < 100 && mCommingState == mMenuStates)
			{
				Sounds::getInstance()->setMasterVolume(Sounds::getInstance()->getMasterVolume() + 1);
			}

			mStartMenu->render();
			mStartMenu->update();
			break;

	//The Game state
		case GameState:
			if(Sounds::getInstance()->getMasterVolume() < 100)
			{
				Sounds::getInstance()->setMasterVolume(Sounds::getInstance()->getMasterVolume() + 1);
			}

			mGameMenu->render();
			mGameMenu->update();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && mEsc == true)
			{
				//mMenuStates = PauseState;
				setState(PauseState);
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
					//mMenuStates = GameState;
					setState(GameState);
					mEsc = false;
					mPauseMenu->setCurrentButton();
				}
			}
			break;

	// dialogstate
		case DialogueState:
			//mGameMenu->render();
			if(Sounds::getInstance()->getMasterVolume() < 100)
			{
				Sounds::getInstance()->setMasterVolume(Sounds::getInstance()->getMasterVolume() + 1);
			}

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

	changeState();
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
	mLastState = mMenuStates;
	mCommingState = menustate;

	mStartMenu->SetCanPressToFalse();
	mPauseMenu->SetCanPressToFalse();

	if(mLastState == PauseState || mCommingState == PauseState)
	{
		mMenuStates = mCommingState;
	}
	changeState();
}

bool State::getExit()
{
	return mStartMenu->getExit();
}

void State::setmEsc(bool bol)
{
	mEsc = bol;
}

void State::changeState()
{
	if(mCommingState != mMenuStates)
	{
		//if(Sounds::getInstance()->getMasterVolume() > 0)
		//{
		//	Sounds::getInstance()->setMasterVolume(Sounds::getInstance()->getMasterVolume() - 1);
		//	if(Sounds::getInstance()->getMasterVolume() < 0)
		//	{
		//		Sounds::getInstance()->setMasterVolume(0);
		//	}
		//}
		//while(mMusicCount > 0)
		//{
		//	mMusicCount -= 0.001;
		//	Sounds::getInstance()->setMasterVolume(mMusicCount);
		//}
		if(/*mMusicCount <= 0*/true)
		{
			mMusicCount = 100;
			Sounds::getInstance()->StopAll();
			Sounds::getInstance()->setMasterVolume(0);

			mMenuStates = mCommingState;

			if(mMenuStates == MyVideoState)
			{
				if(mLastState == StartState)
				{
					mVideoState->newMovie(1);
				}
				else
				{
					mVideoState->newMovie(LevelManager::getInstance()->getCurrentLevel() + 2);
				}
			}

			if(mMenuStates == DialogueState)
			{
				Sounds::getInstance()->Loop("Dialog.ogg");
				mDialogState->restartClock();
				if(mDialogState->getStartDialogue())
				{
					mDialogState->setToBlack();
					mDialogState->reset();
				}
			}

			if(mMenuStates == StartState)
			{
				Sounds::getInstance()->Loop("Meny.ogg");
			}

			if(mMenuStates == GameState)
			{
				Sounds::getInstance()->Loop(LevelManager::getInstance()->getMusic());
			}
		}
	}
}