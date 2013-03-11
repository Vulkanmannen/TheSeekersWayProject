#include "IntroScreen.h"
#include "ImageManager.h"
#include "EntityManager.h"


IntroScreen::IntroScreen()
//mAnimation("intro.png", 150, 24, 512, 512)
{
	//mVideo.load("IntroMovie2.OGV");
	//mVideo.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(256, 220));

	/*mAnimation.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(256, 220));*/
}


IntroScreen::~IntroScreen()
{
}

void IntroScreen::update()
{
	//mVideo.update(mVideoClock.restart());
}

void IntroScreen::render()
{

	//mAnimation.update(0);
	//ImageManager::render(&mAnimation.getSprite());
}