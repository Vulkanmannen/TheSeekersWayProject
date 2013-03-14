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
	bool mEndOfDialouge;
	bool mFadedIn;
	bool mFadedThisTime;
	float mFadeCount;

	void fade();
	void reset();

	sf::Texture mTexture;
	sf::Sprite mSprite;
};

#endif