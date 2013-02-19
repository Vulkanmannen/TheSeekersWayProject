#ifndef INCLUDE_PAUSEMENU
#define INCLUDE_PAUSEMENU
#include "State.h"


class PauseMenu
{
public:
	PauseMenu();
	~PauseMenu();

	void render();
	void update();

private:

	sf::Texture mPauseText;
	sf::Sprite mPauseSprite;
};

#endif