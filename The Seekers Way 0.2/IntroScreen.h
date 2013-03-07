#ifndef INCLUDED_INTROSCREEN
#define INCLUDED_INTROSCREEN
#include "State.h"
#include "Animation.h"
#include <sfTheora\Video.h>


class IntroScreen
{
public:
	IntroScreen();
	~IntroScreen();

	void render();
	void update();

private:

	sf::Clock mVideoClock;
	sftheora::Video mVideo;

	sf::Texture mIntroText;
	sf::Sprite mIntroSprite;

	Animation mAnimation;
};
#endif
