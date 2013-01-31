#include "Sheeka.h"
#include "Animation.h"
#include "Entity.h"
#include "ImageManager.h"
#include "Sounds.h"

const static float HEIGHT	= 64;
const static float WIDTH	= 128;

Sheeka::Sheeka(sf::Vector2f &position):
	mDashPressed(false),
	mDash(false),
	mDashTimer(15),
	mDashAcc(20),
	mDashCount(0)
	{
		mAnimation.init("sheeka.PNG", 60, 7);
		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = SHEEKA;
		mPosition = position;
	}

Sheeka::~Sheeka()
	{}

void Sheeka::update()
{
	if(mDash == false)
	{
		walk();
		jump();
	}
	SheekaDash();
}

void Sheeka::render()
{
	ImageManager::render(&getSprite());
	mAnimation.update(/*mStatus * 2 +*/mDirLeft);
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
		Sounds::getInstance()->Play("dash 1.1.wav");
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