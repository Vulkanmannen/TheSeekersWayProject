#include "State.h"
#include "IntroScreen.h"

State::State():
	mMenuStates(Intro)
{
	IntroSplash = new IntroScreen();
}


State::~State()
{
}

void State::update()
{
	switch(mMenuStates)
	{
		case Intro: 
			mIntroClock.restart();
			if(mIntroClock.getElapsedTime().asSeconds() >= 0)
			{
				IntroSplash->render();
				if(mIntroClock.getElapsedTime().asSeconds() > 5)
				{
					mMenuStates = StartMenu;
				}
			}
			break;

		case StartMenu:
			//StartMenu Class
			break;
	}
}

void State::render()
{

}