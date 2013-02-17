#ifndef INCLUDED_STARTMENU
#define INCLUDED_STARTMENU
#include "State.h"


class StartMenu: public State
{
public:
	StartMenu();
	~StartMenu();

	sf::Texture mStartMenuText;
};

#endif