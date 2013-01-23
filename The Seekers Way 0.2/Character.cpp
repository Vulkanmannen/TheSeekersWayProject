#include "Character.h"
#include "Entity.h"


Character::Character():
	mMovementSpeed(2, 0),
	mAcceleration(-0.5),
	mDecrease(0.5),
	mGravity(5.0),
	mStatus(IDLE),
	mDirLeft(false),
	mJump(10.0),
	mRun(1.0)
{
	mAlive = true;
	mBaseKind = CHARACTER;
}

Character::~Character()
	{}

// returnerer spriten i animationen
sf::Sprite Character::getSprite()
{
	return mAnimation.getSprite();
}

// Flyttar Character
void Character::move()
{
	//mPosition	+= mMovementSpeed;
	//mPosition.y	+= mGravity;
}

// Knapptryck tas in och movementspeed ändras
void Character::walk()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mMovementSpeed.x -= mRun;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mMovementSpeed.x += mRun;
	}
}

// aktiverar så att man kan hoppa
void Character::jump()
{
	//if(mStatus != FALLING)
	//{
		mMovementSpeed.y += mJump;
		//mStatus = JUMPING;
	//}
}

// aktiverar så att man faller
void Character::fall()
{

}

// gör så att man hoppar med knapptryck
void Character::jumping()
{
	if(mStatus = JUMPING)
	{
		mMovementSpeed.y += mAcceleration;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		jump();
	}
}

// Gör så att man faller vid aktivition av fall
void Character::falling()
{
	if(mStatus != JUMPING)
	{
		if(mStatus = FALLING)
		{
			mMovementSpeed.y += mDecrease;
		}
		else if(mStatus = WALK)
		{
			mMovementSpeed.y = 0;
		}
	}
}
