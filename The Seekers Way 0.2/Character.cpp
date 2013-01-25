#include "Character.h"
#include "Entity.h"
#include <cmath>

Character::Character():
	mMovementSpeed(0, 0),
	mAcceleration(0.5),
	mDecrease(0.5),
	mGravity(5.0),
	mStatus(IDLE),
	mDirLeft(false),
	mJump(6.0),
	mRun(5.0),
	mMaxRun(6.0),
	mMaxJump(8.0),
	mJumpTime(6.0),
	mJumping(0.0)
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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mMovementSpeed.x > -mMaxRun)
	{
		mMovementSpeed.x -= mRun;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mMovementSpeed.x < mMaxRun)
	{
		mMovementSpeed.x += mRun;
	}
}

// aktiverar så att man kan hoppa
void Character::jump()
{
	if(mStatus == JUMPING)
	{
		mMovementSpeed.y += mAcceleration; // om mStatus är JUMPING trycks char ner med värdet på mAcceleration
		mJumping += mAcceleration;
		if(mJumping >= mJumpTime)
		{
			//mStatus = LANDING;
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mMovementSpeed.y < mMaxJump)
	{
		mMovementSpeed.y -= mJump;
		mStatus = JUMPING;
	}
}

// aktiverar så att man faller
/*void Character::fall()
{
	
}

// gör så att man hoppar med knapptryck
void Character::jumping()
{
	if(mStatus = JUMPING)
	{
		mMovementSpeed.y += mAcceleration; // om mStatus är JUMPING trycks char ner med värdet på mAcceleration
	}
	else if(mStatus != JUMPING && mStatus != FALLING)
	{

	}
}*/

// Gör så att man faller vid aktivition av fall
void Character::falling()
{
	if(mStatus != JUMPING)
	{
		if(mStatus == FALLING)
		{
			mMovementSpeed.y -= mDecrease;
		}
		else if(mStatus == WALK)
		{
			mMovementSpeed.y = 0;
		}
	}
}

/*void Character::onblock()
{
	mStatus = LANDING;
}*/

