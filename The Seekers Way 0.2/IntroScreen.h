#ifndef INCLUDED_INTROSCREEN
#define INCLUDED_INTROSCREEN
#include "State.h"
#include "Animation.h"


class IntroScreen
{
public:
	IntroScreen();
	~IntroScreen();

	void render();

private:

	sf::Texture mIntroText;
	sf::Sprite mIntroSprite;

	Animation mAnimation;
};
#endif
