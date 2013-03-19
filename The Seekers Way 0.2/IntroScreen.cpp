#include "IntroScreen.h"
#include "ImageManager.h"
#include "EntityManager.h"
#include <cassert>
#include <iostream>

IntroScreen::IntroScreen()
{
	/*mAnimation.setPosition(EntityManager::getInstance()->getView()->getCenter() - sf::Vector2f(256, 220));*/
	//mMovie = new sfe::Movie();

	//mMovie->openFromFile("Intro.wmv");


	//mMovie->setPosition(400, 300);
	//mMovie->play();
} 

IntroScreen::~IntroScreen()
{
}

void IntroScreen::update()
{

}

void IntroScreen::render()
{
	//ImageManager::render(mMovie);

	//mAnimation.update(0);
	//ImageManager::render(&mAnimation.getSprite());
}