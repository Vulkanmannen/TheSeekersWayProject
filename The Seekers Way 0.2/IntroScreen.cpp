#include "IntroScreen.h"
#include "ImageManager.h"

IntroScreen::IntroScreen()
{
	mIntroText.loadFromFile("StartMenu.PNG");
	mIntroSprite.setTexture(mIntroText);
}


IntroScreen::~IntroScreen()
{
}

void IntroScreen::render()
{
	mIntroSprite.setPosition(0, 0);
	ImageManager::render(&mIntroSprite);
}