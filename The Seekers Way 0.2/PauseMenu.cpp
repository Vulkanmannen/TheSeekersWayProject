#include "PauseMenu.h"
#include "ImageManager.h"


PauseMenu::PauseMenu()
{
	mPauseText.loadFromFile("PauseMenu.PNG");
	mPauseSprite.setTexture(mPauseText);
}


PauseMenu::~PauseMenu()
{
}

void PauseMenu::update()
{

}

void PauseMenu::render()
{
	mPauseSprite.setPosition(0, 0);
	ImageManager::render(&mPauseSprite);
}