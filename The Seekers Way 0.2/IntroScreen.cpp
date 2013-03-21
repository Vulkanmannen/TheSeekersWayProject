#include "IntroScreen.h"
#include "ImageManager.h"
#include "EntityManager.h"


IntroScreen::IntroScreen()
{
	mSplashVid.load("Intro.ogv");
	mSplashVid.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(640, 360));
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
}