#ifndef INCLUDED_STARTMENU
#define INCLUDED_STARTMENU
#include "State.h"
#include <vector>
#include "Animation.h"


class StartMenu
{
public:
	StartMenu();
	~StartMenu();

	void update();
	void render();
	void SetCanPressToFalse();
	bool getExit();

private:

	void updateButtons();
	void generateButtons();
	void changeButton();
	void renderButtons();
	void updateCurrentButton();
	void buttonActivate();

	int currentButton;
	bool canPressReturn;
	bool canPress;
	bool exit;
	bool HowToPlay;

	sf::Texture mStartText;
	sf::Sprite mStartSprite;	
	sf::Texture mHowToPlay;
	sf::Sprite mHowToPlaySprite;

	std::vector<Animation> mButtons;
};

#endif