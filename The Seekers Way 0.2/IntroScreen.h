#ifndef INCLUDED_INTROSCREEN
#define INCLUDED_INTROSCREEN

#include "State.h"
#include "Animation.h"

//#include "sfeMovie-1.0-windows-vs2010\include\sfeMovie\Movie.hpp"

class IntroScreen
{
public:
	IntroScreen();
	~IntroScreen();

	void render();
	void update();

private:

	//sfe::Movie mMovie;

	sf::Texture mIntroText;
	sf::Sprite mIntroSprite;
}; 
#endif