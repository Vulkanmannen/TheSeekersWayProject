#include "State.h"
#include "IntroScreen.h"
#include "StartMenu.h"
#include "GameMenu.h"
#include "PauseMenu.h"


State::State():
	mMenuStates(Intro),
	mEsc()
{
	IntroSplash = new IntroScreen();
	mStartMenu = new StartMenu();
	mGameMenu = new GameMenu();
	mPauseMenu = new PauseMenu();
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
			if(mIntroClock.getElapsedTime().asSeconds() > 5)
			{
				mMenuStates = StartState;
			}
			break;

	//The StartMenu State
		case StartState:
			mStartMenu->render();
			mStartMenu->update();
			if(mStartMenu->GetContinue())
			{
				mMenuStates = GameState;
			}
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

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && mEsc == true)
			{
				mMenuStates = GameState;
				mEsc = false;
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