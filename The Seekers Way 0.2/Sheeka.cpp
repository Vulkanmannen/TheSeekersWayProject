#include "Sheeka.h"
#include "Animation.h"
#include "Entity.h"
#include "ImageManager.h"

const static float HEIGHT	= 64;
const static float WIDTH	= 128;

Sheeka::Sheeka(sf::Vector2f &position):
	mDash(0.0),
	mDashAcc(5),
	mMaxDashDist(20),
	mDashCount(1),
	mAnimation("Sheekabebad.png", 60, 7, 128, 128)
	{
		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = SHEEKA;
		mPosition = position;
	}

Sheeka::~Sheeka()
	{}

void Sheeka::update()
{
	move();
	walk();
	jump();
	falling();
	SheekaDash();

}

void Sheeka::render()
{
	ImageManager::render(&getSprite());
	mAnimation.update(mStatus * 2 + mDirLeft);
	mAnimation.setPosition(sf::Vector2f(mPosition.x -64, mPosition.y -96));
}

sf::Sprite Sheeka::getSprite()
{
	return mAnimation.getSprite();
}

void Sheeka::SheekaDash()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		mMovementSpeed.x += mDashAcc;
		mDashAcc += mDashCount;
		if(mDashCount = mMaxDashDist)
		{
			mDashCount = 0;
		}
	}
}