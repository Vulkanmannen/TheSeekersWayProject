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

private:

	void generateButtons();
	void changeButton();
	void renderButtons();
	void updateCurrentButton();
	void buttonActivate();


	int currentButton;
	bool canPressReturn;
	bool canPress;

	sf::Texture mPauseText;
	sf::Sprite mPauseSprite;

	std::vector<Animation> mButtons;
};

#endif