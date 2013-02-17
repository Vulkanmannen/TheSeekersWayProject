#include "State.h"


State::State():
	mMenuStates(Intro)
{
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
				IntroSplash->Splash();
				if(mIntroClock.getElapsedTime().asSeconds() > 4)
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