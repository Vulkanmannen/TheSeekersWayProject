#include "Lever.h"

static const float WIDTH = 64;
static const float HEIGHT = 64;

Lever::Lever(sf::Vector2f &position, int id)
{
	mDrawn = false;
	mPosition = position;
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = LEVER;

	mTexture.loadFromFile("Lever.png");
	mSprite.setTexture(mTexture);
	mSprite.setPosition(position);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
}

Lever::~Lever()
{

}

void Lever::Activate()
{
	mDrawn = !mDrawn;

	if(mDrawn == true)	
	{
		mBlock->Activate();
	}

	else		
	{
		mBlock->DisActivate();
	}
}