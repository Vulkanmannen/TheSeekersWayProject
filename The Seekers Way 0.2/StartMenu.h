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

	sf::Vector2f HowToPlayCount(sf::Sprite);

	sf::Texture mHowToPlayKiba;
	sf::Sprite mHowToPlaySpriteKiba;
	sf::Texture mHowToPlayCharlotte;
	sf::Sprite mHowToPlaySpriteCharlotte;
	sf::Texture mHowToPlayFenrir;
	sf::Sprite mHowToPlaySpriteFenrir;
	sf::Texture mHowToPlaySheeka;
	sf::Sprite mHowToPlaySpriteSheeka;

	std::vector<Animation> mButtons;
};

#endif