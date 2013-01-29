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
	mJumping(0.0),
	mFalling(false),
	mIsJumping(false),
	mAnimation(128, 128)
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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if(mMovementSpeed.x > -mMaxRun)
		{
			mMovementSpeed.x -= mRun;
		}
		if(mStatus == IDLE)
		{
			mStatus = WALK;
		}
		mDirLeft = true;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if(mMovementSpeed.x < mMaxRun)
		{
			mMovementSpeed.x += mRun;
		}
		if(mStatus == IDLE)
		{
			mStatus = WALK;
		}

		mDirLeft = false;

	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mMovementSpeed.x = 0;
		if(mStatus == WALK)
		{
			mStatus = IDLE;
		}
	}
}

// aktiverar så att man kan hoppa
void Character::jump()
{
	if(mStatus == JUMP && mAnimation.getEndOfAnimation())
	{
		mStatus = JUMPING;
		mMovementSpeed.y -= mJump;
		mIsJumping = true;
	}

	if(mIsJumping && mStatus == JUMPING)
	{
		mMovementSpeed.y += mAcceleration; // om mStatus är JUMPING trycks char ner med värdet på mAcceleration
		mJumping += mJumpTime;
		if(mJumping >= mMaxJump)
		{
			mJumping = 0;
			mFalling = true;
			mIsJumping = false;
		}
	}
	else if(!mFalling && !mIsJumping)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mMovementSpeed.y < mMaxJump)
		{
			mStatus = JUMP;
		}
	}
}


void Character::falling()
{
	if(mFalling)
	{
		mMovementSpeed.y += mDecrease;
	}
}

void Character::onblock()
{
	if(mFalling)
	{
		mFalling = false;
		mStatus = IDLE;
		mMovementSpeed.y = 0;
	}
}

void Character::fall()
{
	if(!mIsJumping)
	{
		mFalling = true;
	}
}