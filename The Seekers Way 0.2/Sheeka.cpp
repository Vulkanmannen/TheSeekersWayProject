#include "Sheeka.h"
#include "Animation.h"
#include "Entity.h"
#include "ImageManager.h"
#include "Sounds.h"
#include "DarkBinding.h"
#include "EntityManager.h"
#include "SFML\System\Clock.hpp"

const static float HEIGHT	= 64;
const static float WIDTH	= 110;

Sheeka::Sheeka(sf::Vector2f &position):
	mDashPressed(false),
	mDash(false),
	mDashTimer(38),
	mDashAcc(10),
	mDashCount(0),
	mCanPressDarkBinding(true),
	mCanDashCount(60),
	mCanDashTime(60)
	{
		mAnimation.init("sheeka.PNG", 60, 8);
		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = SHEEKA;
		mPosition = position;
	}

Sheeka::~Sheeka()
	{}

void Sheeka::update(EntityKind &currentEntity)
{
	move();

	if(mCanMove)
	{
		if(mDash == false)
		{
			if(currentEntity == mEntityKind)
			{
				walk();
				jump();
				darkBinding();
			}
	
		}
		if(currentEntity == mEntityKind)
		{
			SheekaDash();
		}
		dashTime();
	}

	if(mDash == false)
	{
		Character::update(currentEntity);
	}
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

// s�tter ig�ng dashen
void Sheeka::SheekaDash()
{
	mCanDashCount++;
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) 
		&& !mDash 
		&& !mDashPressed 
		&& mCanDashCount >= mCanDashTime)
	{
		mCanDashCount = 0;
		mStatus = ACTION1;
		Sounds::getInstance()->Play("dash.wav");
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
}

// sheeka skjuter en projektil
void Sheeka::darkBinding()
{
	if(((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::X)))
		&& mCanPressDarkBinding 
		&& mDarkBindingClock.getElapsedTime().asSeconds() >= 0.3
		&& !mJumping
		&& !mFalling)
	{
		mDarkBindingClock.restart();
		mCanPressDarkBinding = false;
		EntityManager::getInstance()->addEntity(new DarkBinding(sf::Vector2f(mPosition.x + (35 * (mDirLeft? -1 : 1)), mPosition.y - 7), mDirLeft));
		mStatus = ACTION2;
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		mCanPressDarkBinding = true;
	}
}

// l�gger till att dash = false i takedamage
void Sheeka::takeDamage()
{
	Character::takeDamage();
	notDashing();
}

// reglerar hur l�nge dashen p�g�r
void Sheeka::dashTime()
{
	if(mDash)
	{
		mDashCount++;
		if(mDashCount >= mDashTimer)
		{
			notDashing();
			mMovementSpeed.y = 0;
			mMovementSpeed.x = 0;
			mStatus = IDLE;
		}
	}
}

// k�rs n�r sheeka g�r ur sin dash
void Sheeka::notDashing()
{
	mDash = false;
	mDashCount = 0;
	mGravity = 5;
}