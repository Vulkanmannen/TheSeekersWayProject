#include "IntroScreen.h"
#include "ImageManager.h"

IntroScreen::IntroScreen():
mAnimation("intro.png", 150, 24, 512, 512)
{
	mAnimation.setPosition(sf::Vector2f(256, 64));
}


IntroScreen::~IntroScreen()
{
}

void IntroScreen::render()
{

	mAnimation.update(0);
	ImageManager::render(&mAnimation.getSprite());

}