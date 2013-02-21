#include "State.h"
#include "IntroScreen.h"
#include "StartMenu.h"
#include "GameMenu.h"
#include "PauseMenu.h"
#include "Sounds.h"

State* State::sInstance = 0;

State::State():
	mMenuStates(Intro),
	mEsc()
{
	IntroSplash = new IntroScreen();
	mStartMenu = new StartMenu();
	mGameMenu = new GameMenu();
	mPauseMenu = new PauseMenu();
	Sounds::getInstance()->Loop("crazykoncept.wav", 30);
}


State::~State()
{
}

void State::update()
{
	switch(mMenuStates)
	{
	//The Splashscreen
		case Intro: 
			IntroSplash->render();
			if(mIntroClock.getElapsedTime().asSeconds() > 6.7)
			{
				Sounds::getInstance()->setMasterVolume(Sounds::getInstance()->getMasterVolume() - 1);
			}
			if(mIntroClock.getElapsedTime().asSeconds() > 8 
				|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)))
			{
				mMenuStates = StartState;
				Sounds::getInstance()->StopAll();
				mEsc = false;
				Sounds::getInstance()->setMasterVolume(30);
				Sounds::getInstance()->Loop("fireball.wav", 30);
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
				}
			}
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
	mMenuStates = menustate;
	mStartMenu->SetCanPressToFalse();
	mPauseMenu->SetCanPressToFalse();
}

bool State::getExit()
{
	return mStartMenu->getExit();
}

void State::setmEsc(bool bol)
{
	mEsc = bol;
}