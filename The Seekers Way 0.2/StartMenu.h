#ifndef INCLUDED_STARTMENU
#define INCLUDED_STARTMENU
#include "State.h"


class StartMenu: public State
{
public:
	StartMenu();
	~StartMenu();

	void update();
	void render();

	void LoadStartMenu();
};

#endif