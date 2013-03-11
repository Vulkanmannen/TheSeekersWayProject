#ifndef INCLUDED_INTROSCREEN
#define INCLUDED_INTROSCREEN
#include "State.h"
#include "Animation.h"
<<<<<<< HEAD
#include "sfeMovie\Movie.hpp"
=======
//#include <sfTheora\Video.h>
>>>>>>> origin/master


class IntroScreen
{
public:
	IntroScreen();
	~IntroScreen();

	void render();
	void update();

private:

<<<<<<< HEAD
	sfe::Movie mMovie;
=======
	sf::Clock mVideoClock;
	//sftheora::Video mVideo;
>>>>>>> origin/master

	sf::Texture mIntroText;
	sf::Sprite mIntroSprite;

	Animation mAnimation;
};
#endif
