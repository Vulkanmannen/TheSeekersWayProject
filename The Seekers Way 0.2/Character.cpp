#include "Character.h"
#include "Entity.h"


Character::Character():
	mMovementSpeed(0, 0),
	mAcceleration(0.5),
	mDecrease(0.5),
	mGravity(5.0),
	mStatus(IDLE),
	mDirLeft(false),
	mJump(10.0),
	mRun(0.5)
{
	mAlive = true;
	mBaseKind = CHARACTER;
}

Character::~Character()
	{}

// Flyttar Character
void Character::move()
{
	mPosition	+= mMovementSpeed;
	mPosition.y	+= mGravity;
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
	mStatus = JUMPING;
	mMovementSpeed.y -= mJump;
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
	else if(mStatus != JUMPING && mStatus != FALLING)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			jump();
		}
	}
}

// Gör så att man faller vid aktivition av fall
/*void Character::falling()
{
	if(mStatus != JUMPING)
	{
		if(mStatus = FALLING)
		{
			mMovementSpeed.y -= mDecrease;
		}
		else if(mStatus = WALK)
		{
			mMovementSpeed.y = 0;
		}
	}
}*/
