#ifndef INCLUDE_DIALOGSTATE
#define INCLUDE_DIALOGSTATE

#include "State.h"
#include "SFML\Graphics.hpp"

class DialogState
{
public:
	DialogState();
	~DialogState();
	void update();
	void render();
private:
	bool mPlayMovie;
	float mTimeToMovie;

	sf::Texture mTexture;
	sf::Sprite mSprite;
};

#endif