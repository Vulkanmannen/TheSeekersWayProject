#include "Character.h"
#include "Entity.h"
#include <cmath>

Character::Character():
	mMovementSpeed(0, 0),
	mAcceleration(0.3),
	mDecrease(0.6),
	mGravity(5.0),
	mStatus(IDLE),
	mDirLeft(false),
	mJump(14.5),
	mRun(6.0),
	mMaxRun(6.0),
	mMaxJump(14.5),
	mJumpTime(1.0),
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
	else
	{
		mMovementSpeed.x = 0;
	}
}

// aktiverar så att man kan hoppa
void Character::jump()
{
	if(mStatus == JUMPING)
	{
		mMovementSpeed.y += mAcceleration; // om mStatus är JUMPING trycks char ner med värdet på mAcceleration
		mJumping += mJumpTime;
		if(mJumping >= mMaxJump)
		{
			mJumping = 0;
			mStatus = FALLING;
		}
	}
	else if(mStatus != FALLING)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mMovementSpeed.y < mMaxJump)
		{
			mMovementSpeed.y -= mJump;
			mStatus = JUMPING;
		}
	}
}


void Character::falling()
{
	if(mStatus == FALLING)
	{
		mMovementSpeed.y += mDecrease;
	}
}

void Character::onblock()
{
	if(mStatus == FALLING)
	{
		mStatus = LANDING;
		mMovementSpeed.y = 0;
	}
}