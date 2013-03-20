#ifndef INCLUDED_INTROSCREEN
#define INCLUDED_INTROSCREEN

#include "State.h"
#include "Animation.h"
#include "sfTheora.h"

class IntroScreen
{
public:
	IntroScreen();
	~IntroScreen();

	void render();
	void update();

private:

	sf::Clock mVideoClock;
	sftheora::Video	mSplashVid;
	
	sf::Texture mIntroText;
	sf::Sprite mIntroSprite;
}; 
#endif