#include "State.h"
#include "IntroScreen.h"
#include "StartMenu.h"


State::State():
	mMenuStates(Intro)
{
	IntroSplash = new IntroScreen();
	mStartMenu = new StartMenu();
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

			break;
	}
}

void State::render()
{

}