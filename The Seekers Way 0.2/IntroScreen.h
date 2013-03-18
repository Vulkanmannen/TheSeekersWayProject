#ifndef INCLUDED_INTROSCREEN
#define INCLUDED_INTROSCREEN

#include "State.h"
#include "Animation.h"
#include "sfeMovie\Movie.hpp"


class IntroScreen
{
public:
	IntroScreen();
	~IntroScreen();

	void render();
	void update();

private:

	sfe::Movie mMovie;

	sf::Texture mIntroText;
	sf::Sprite mIntroSprite;
};
#endif