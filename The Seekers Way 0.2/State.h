#ifndef INCLUDED_STATE
#define INCLUDED_STATE
#include "Entity.h"

class IntroScreen;
class StartMenu;
class GameMenu;
class PauseMenu;
class DialogState;
class VideoState;

class State
{
public:

	enum MenuStates
	{
		Intro,
		StartState,
		PauseState,
		DialogueState,
		GameState,
		MyVideoState
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

	MenuStates mLastState;
	MenuStates mCommingState;

	IntroScreen *IntroSplash;
	StartMenu *mStartMenu;
	GameMenu *mGameMenu;
	PauseMenu *mPauseMenu;
	DialogState *mDialogState;
	VideoState *mVideoState;

	sf::Clock mIntroClock;

	bool mEsc;

	void changeState();
	float mMusicCount;
};
#endif