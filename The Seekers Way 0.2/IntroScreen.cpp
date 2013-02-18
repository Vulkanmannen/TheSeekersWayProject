#include "IntroScreen.h"

IntroScreen::IntroScreen()
{
	mIntroText.loadFromFile("Llama.JPEG");
	mIntroSprite.setTexture(mIntroText);
}


IntroScreen::~IntroScreen()
{
}

void IntroScreen::render()
{
	mIntroSprite.setPosition(512, 360);
	mIntroRender.draw(mIntroSprite);
	
}