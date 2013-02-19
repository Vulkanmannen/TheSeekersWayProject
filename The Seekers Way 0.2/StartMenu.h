#ifndef INCLUDED_STARTMENU
#define INCLUDED_STARTMENU
#include "State.h"


class StartMenu
{
public:
	StartMenu();
	~StartMenu();

	void update();
	void render();
	bool GetContinue();


private:

		bool mContinue;

	sf::Texture mStartText;
	sf::Sprite mStartSprite;
};

#endif