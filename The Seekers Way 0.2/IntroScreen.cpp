#include "IntroScreen.h"

IntroScreen::IntroScreen()
{
	
}


IntroScreen::~IntroScreen()
{
}

void IntroScreen::Splash()
{
	mIntroText.loadFromFile("Llama.JPEG");
	mIntroSprite.setPosition(512, 360);
	mIntroRender.draw(mIntroSprite);
}