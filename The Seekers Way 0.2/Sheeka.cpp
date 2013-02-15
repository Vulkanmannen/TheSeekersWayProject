#include "Sheeka.h"
#include "Animation.h"
#include "Entity.h"
#include "ImageManager.h"
#include "Sounds.h"
#include "DarkBinding.h"
#include "EntityManager.h"

const static float HEIGHT	= 64;
const static float WIDTH	= 110;

Sheeka::Sheeka(sf::Vector2f &position):
	mDashPressed(false),
	mDash(false),
	mDashTimer(38),
	mDashAcc(10),
	mDashCount(0),
	mCanPressDarkBinding(true)
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

// sätter igång dashen
void Sheeka::SheekaDash()
{
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && !mDash && !mDashPressed && mDashClock.getElapsedTime().asSeconds() >=2)
	{
		mStatus = ACTION1;
		Sounds::getInstance()->Play("dash.wav");
		mDashClock.restart();
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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mCanPressDarkBinding && mDarkBindingClock.getElapsedTime().asSeconds() >= 0.3)
	{
		mDarkBindingClock.restart();
		mCanPressDarkBinding = false;
		EntityManager::getInstance()->addEntity(new DarkBinding(mPosition, mDirLeft));
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		mCanPressDarkBinding = true;
	}
}

// lägger till att dash = false i takedamage
void Sheeka::takeDamage()
{
	Character::takeDamage();
	notDashing();
}

// reglerar hur länge dashen pågår
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

// körs när sheeka går ur sin dash
void Sheeka::notDashing()
{
	mDash = false;
	mDashCount = 0;
	mGravity = 5;
}