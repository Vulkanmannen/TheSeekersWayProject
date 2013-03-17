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
	mDashTimer(30),
	mDashAcc(10),
	mDashCount(0),
	mCanPressDarkBinding(true),
	mCanDashCount(60),
	mCanDashTime(60),
	mDarkBinding(false),
	mDarkBindingTime(false)
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
	darkBindingTime();

	if(mCanMove)
	{
		if(!mDash && !mDarkBindingTime)
		{
			if(currentEntity == mEntityKind)
			{
				walk();
				jump();
				darkBinding();
			}
		}
		if(currentEntity == mEntityKind&& !mDarkBindingTime)
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
	sf::RenderStates states;
	if(mHurtShow)
		states.shader = &mHurtShader;
	ImageManager::render(&getSprite(), states);
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
	mCanDashCount++;
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) 
		&& !mDash 
		&& !mDashPressed 
		&& mCanDashCount >= mCanDashTime)
	{
		mCanDashCount = 0;
		mStatus = ACTION1;
		mAnimationClock.restart();
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
	if(((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) && !mDarkBinding)
		&& mCanPressDarkBinding 
		&& mDarkBindingClock.getElapsedTime().asSeconds() >= 1
		&& !mJumping
		&& !mFalling)
	{
		mDarkBindingClock.restart();
		mCanPressDarkBinding = false;
		mDarkBinding = true;
		mDarkBindingTime = true;
		mDarkClock.restart();
		mMovementSpeed.x = 0;
		mStatus = ACTION2;
		mAnimationClock.restart();
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		mCanPressDarkBinding = true;
	}
}

void Sheeka::darkBindingTime()
{
	if(mDarkBinding && mDarkClock.getElapsedTime().asMilliseconds() > 270)
	{
		EntityManager::getInstance()->addEntity(new DarkBinding(sf::Vector2f(mPosition.x + (35 * (mDirLeft? -1 : 1)), mPosition.y - 7), mDirLeft));
		mDarkBinding = false;
	}
	
	if(mDarkBindingTime && mDarkClock.getElapsedTime().asMilliseconds() > 550)
	{
		mDarkBindingTime = false;
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