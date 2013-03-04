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
	int setCurrentButton();
	bool HowToPlayInst();

private:

	void updateButtons();
	void generateButtons();
	void changeButton();
	void renderButtons();
	void updateCurrentButton();
	void buttonActivate();
	void changeJournalFrame();

	int currentJournalFrame;
	int currentButton;
	bool canPressReturn;
	bool canPressMenu;
	bool canPressJournal;

	bool HowToPlay;


	sf::Texture mPauseText;
	sf::Sprite mPauseSprite;

	sf::Texture mHowToPlayKiba;
	sf::Sprite mHowToPlaySpriteKiba;
	sf::Texture mHowToPlayCharlotte;
	sf::Sprite mHowToPlaySpriteCharlotte;
	sf::Texture mHowToPlayFenrir;
	sf::Sprite mHowToPlaySpriteFenrir;
	sf::Texture mHowToPlaySheeka;
	sf::Sprite mHowToPlaySpriteSheeka;

	std::vector<sf::Sprite*> mSpriteVector;

	std::vector<Animation> mButtons;
};

#endif