#include "IntroScreen.h"
#include "ImageManager.h"
#include "EntityManager.h"


IntroScreen::IntroScreen()
{
	mMovie.openFromFile("IntroMovie.wmv");
	mMovie.setPosition(400, 300);
	mMovie.play();
	/*mAnimation.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(256, 220));*/
}


IntroScreen::~IntroScreen()
{
}

void IntroScreen::update()
{

}

void IntroScreen::render()
{
	ImageManager::render(&mMovie);
	//mAnimation.update(0);
	//ImageManager::render(&mAnimation.getSprite());
}