#ifndef INCLUDE_PAUSEMENU
#define INCLUDE_PAUSEMENU
#include "State.h"
#include "Animation.h"


class PauseMenu
{
public:
	PauseMenu();
	~PauseMenu();

	void render();
	void update();
	void SetCanPressToFalse();
	bool HowToPlayInst();

private:

	void generateButtons();
	void changeButton();
	void renderButtons();
	void updateCurrentButton();
	void buttonActivate();


	int currentButton;
	bool canPressReturn;
	bool canPress;

	bool HowToPlay;

	sf::Texture mPauseText;
	sf::Texture mHowToPlay;
	sf::Sprite mPauseSprite;
	sf::Sprite mHowToPlaySprite;

	std::vector<Animation> mButtons;
};

#endif