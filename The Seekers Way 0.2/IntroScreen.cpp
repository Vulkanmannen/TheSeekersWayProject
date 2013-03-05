#include "IntroScreen.h"
#include "ImageManager.h"
#include "EntityManager.h"


IntroScreen::IntroScreen()
//mAnimation("intro.png", 150, 24, 512, 512)
{
	mMovie.openFromFile("Intro.mp4");
	mMovie.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(256, 220));
	mMovie.play();
	/*mAnimation.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(256, 220));*/
}


IntroScreen::~IntroScreen()
{
}

void IntroScreen::render()
{
	//mAnimation.update(0);
	//ImageManager::render(&mAnimation.getSprite());
}