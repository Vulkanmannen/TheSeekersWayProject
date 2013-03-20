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

	void restartClock();
	void reset();
	void setToBlack();
	bool getStartDialogue();
private:
	bool mEndOfDialouge;
	bool mFadedIn;
	bool mFadedThisTime;
	float mFadeCount;
	sf::Clock mTimeToFadeIn;

	void fade();


	sf::Texture mTexture;
	sf::Sprite mSprite;
};

#endif