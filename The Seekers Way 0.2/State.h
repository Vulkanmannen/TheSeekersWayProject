#ifndef INCLUDED_STATE
#define INCLUDED_STATE
#include "Entity.h"

class IntroScreen;
class StartMenu;
class GameMenu;
class PauseMenu;

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
	GameMenu *mGameMenu;
	PauseMenu *mPauseMenu;

	sf::Clock mIntroClock;

	bool mEsc;
};
#endif