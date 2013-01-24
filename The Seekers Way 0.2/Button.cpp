#include "Button.h"

static const float WIDTH = 64;
static const float HEIGHT = 64;

Button::Button(sf::Vector2f &position, int id)
{
	isitpressed = false;
	mPosition = position;
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = BUTTON;

	mTexture.loadFromFile("Button.png");
	mSprite.setTexture(mTexture);
	mSprite.setPosition(position);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
}

Button::~Button()
{

}

void Button::ButtonPressed()
{
	if(isitpressed == false)
	{
		mBlock->Activate();
	}
	isitpressed = true;
}

void Button::ButtonRelease()
{
	if(isitpressed == false)
	{
		mBlock->DisActivate();
	}
	isitpressed = false;
}