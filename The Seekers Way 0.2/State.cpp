#include "State.h"
#include "IntroScreen.h"

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
		case Intro: 
				IntroSplash->render();
				if(mIntroClock.getElapsedTime().asSeconds() > 5)
				{
					mMenuStates = StartState;
				}
			break;

		case StartState:
				
			break;
	}
}

void State::render()
{

}