#include "Sheeka.h"
#include "Animation.h"
#include "Entity.h"
#include "ImageManager.h"

const static float HEIGHT	= 64;
const static float WIDTH	= 128;

Sheeka::Sheeka(sf::Vector2f &position):
	mDashPressed(false),
	mDash(false),
<<<<<<< HEAD
	mDashTimer(15),
	mDashAcc(20),
	mMaxDashDist(0),
	mDashCount(0),
	mAnimation("Sheekabebad.png", 60, 7, 128, 128)
=======
	mDashTimer(0.0),
	mDashAcc(5),
	mMaxDashDist(1),
	mDashCount(1)
>>>>>>> 122f0e386436bec4658342c37eb4b612875357fc
	{
		mAnimation.init("Sheekabebad.png", 60, 7);
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

	if(mDash == false)
	{
		walk();
		jump();
		falling();
	}

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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !mDash && !mDashPressed && mClock.getElapsedTime().asSeconds() >=2)
	{
		mClock.restart();
		mMovementSpeed.y = 0;
		mMovementSpeed.x = 0;
		mGravity = 0;
		if(mDirLeft)
		{
			mMovementSpeed.x -= mDashAcc;
		}
		else if(mDirLeft == false)
		{
			mMovementSpeed.x += mDashAcc;
		}
		mDash = true;
		mDashPressed = true;
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		mDashPressed = false;
	}

	if(mDash)
	{
		mDashCount++;
		if(mDashCount >= mDashTimer)
		{
			mDash = false;
			mDashCount = 0;
			mMovementSpeed.y = 0;
			mMovementSpeed.x = 0;
			mGravity = 5;
		}
	}
}