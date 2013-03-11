#include "IntroScreen.h"
#include "ImageManager.h"
#include "EntityManager.h"


IntroScreen::IntroScreen()
{
	mMovie.openFromFile("INTRO.ogg");
	mMovie.play();
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
}