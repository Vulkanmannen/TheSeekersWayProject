#include "Arrow.h"
#include "ImageManager.h"

Arrow::Arrow(sf::Vector2f &position, bool dirleft):
	mDirLeft(dirleft),
	mMovementSpeed(10*((0.5-dirleft)*2),0)
{
	mPosition = position;
	mTexture.loadFromImage(*ImageManager::getImage("arrow.png"));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(position);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.scale((-(0.5-dirleft)*2),1);
}

Arrow::~Arrow()
{

}

void Arrow::update()
{
	if(mShottingTime.getElapsedTime().asSeconds() > 2)
	{
		destroy();
	}
	
	mPosition	+= mMovementSpeed;
	mSprite.setPosition(mPosition);
}