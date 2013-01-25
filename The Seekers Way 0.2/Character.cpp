#include "Character.h"
#include "Entity.h"
#include <cmath>

Character::Character():
	mMovementSpeed(0, 0),
	mAcceleration(0.8),
	mDecrease(0.5),
	mGravity(5.0),
	mStatus(IDLE),
	mDirLeft(false),
	mJump(12.0),
	mRun(5.0),
	mMaxRun(3.0),
	mMaxJump(12.0),
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
			falling();
		}
	}
	else if(mStatus != JUMPING && mStatus != FALLING)
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
		if(Character::onblock)
		{
			onblock();
			mStatus = LANDING;
		}
	}
}

void Character::onblock()
{
	mStatus != FALLING;
	mStatus != JUMPING;
}