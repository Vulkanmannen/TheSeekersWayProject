#include "Charlotte.h"
#include "Animation.h"
#include "Entity.h"
#include "ImageManager.h"


const static float HEIGHT = 64;
const static float WIDTH = 128;

Charlotte::Charlotte(sf::Vector2f &position)
	{
		mAnimation.init("Sheekabebad.png", 60, 7);

		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = CHARLOTTE;
		mPosition = position;
	}

Charlotte::~Charlotte()
	{}

void Charlotte::update()
{
	walk();
	jump();
}

void Charlotte::render()
{
	mAnimation.update(mStatus * 2 + mDirLeft);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y -96));
	ImageManager::render(&getSprite());
}

sf::Sprite Charlotte::getSprite()
{
	return mAnimation.getSprite();
}