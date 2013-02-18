#ifndef INCLUDED_STATE
#define INCLUDED_STATE
#include "Entity.h"

class IntroScreen;
class StartMenu;

class State
{
public:
	State();

	void render();
	void update();

	~State();

private:

	enum MenuStates
	{
		Intro,
		StartState,
		PauseState,
		DialogState,
		GameState
	};

	MenuStates mMenuStates;

	IntroScreen *IntroSplash;
	StartMenu *mStartMenu;

	sf::Clock mIntroClock;
};
#endif