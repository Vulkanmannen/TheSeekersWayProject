#ifndef INCLUDED_STATE
#define INCLUDED_STATE
#include "Entity.h"

class IntroScreen;
class StartMenu;
class GameMenu;
class PauseMenu;
class DialogState;

class State
{
public:

	enum MenuStates
	{
		Intro,
		StartState,
		PauseState,
		DialogueState,
		GameState
	};

	void render();
	void update();
	bool getExit();
	void setmEsc(bool bol);
	void setState(MenuStates);
	static State* getInstance();

	~State();

private:

	State();
	State(const State&);
	void operator=(const State&);

	static State* sInstance;

	MenuStates mMenuStates;

	IntroScreen *IntroSplash;
	StartMenu *mStartMenu;
	GameMenu *mGameMenu;
	PauseMenu *mPauseMenu;
	DialogState *mDialogState;

	sf::Clock mIntroClock;

	bool mEsc;
};
#endif