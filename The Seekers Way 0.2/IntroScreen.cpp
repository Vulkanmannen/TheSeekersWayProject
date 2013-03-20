#include "IntroScreen.h"
#include "ImageManager.h"
#include "EntityManager.h"


IntroScreen::IntroScreen()
{
	/*mAnimation.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(256, 220));*/
	mSplashVid.load("INTRO.ogg");
	mSplashVid.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(512, 360));
	mSplashVid.play();
} 

IntroScreen::~IntroScreen()
{
}

void IntroScreen::update()
{
	mSplashVid.update(sf::seconds(1.0f / 25.0f));
}

void IntroScreen::render()
{
	ImageManager::render(&mSplashVid);

	//mAnimation.update(0);
	//ImageManager::render(&mAnimation.getSprite());
}