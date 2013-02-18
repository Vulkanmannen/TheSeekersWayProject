#ifndef INCLUDED_STATE
#define INCLUDED_STATE
#include "Entity.h"

class IntroScreen;


class State
{
public:
	State();

	void render();
	void update();

	~State();

protected:

	enum MenuStates
	{
		Intro,
		StartMenu,
		PauseMenu,
		DialogState,
		GameState
	};

	MenuStates mMenuStates;
	IntroScreen *IntroSplash;

	sf::Clock mIntroClock;
};
#endif