#ifndef INCLUDED_INTROSCREEN
#define INCLUDED_INTROSCREEN
#include "State.h"


class IntroScreen
{
public:
	IntroScreen();
	~IntroScreen();

protected:

	void Splash();
	sf::Texture mIntroText;
	sf::Sprite mIntroSprite;
	sf::RenderWindow mIntroRender;
	
};
#endif
