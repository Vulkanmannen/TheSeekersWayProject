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

void Character::onblock()
{
	if(mFalling)
	{
		mFalling = false;
		if(mStatus == INAIR)
		{
			mStatus = IDLE;
		}
		mMovementSpeed.y = 0;
	}
}

//void Character::characterUpdate(Character* character, EntityKind &entityKind)
//{
//	character->move(entityKind);
//	character->falling();
//	character->fall();
//}

// Flyttar Character
void Character::move()
{
	mPosition	+= mMovementSpeed;
	mPosition.y	+= mGravity;
}

// Knapptryck tas in och movementspeed �ndras
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
}

// stoppar en gubbe
void Character::dontWalk(EntityKind &currentEntity)
{
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || currentEntity != mEntityKind)
	{
		mMovementSpeed.x = 0;
		if(mStatus == WALK)
		{
			mStatus = IDLE;
		}
	}
}

// aktiverar s� att man kan hoppa
void Character::jump()
{
	if(!mFalling && !mIsJumping)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mMovementSpeed.y < mMaxJump)
		{
			mStatus = JUMP;
			mIsJumping = true;
			mMovementSpeed.y -= mJump;
		}
	}
}

// uppdaterar hoppet
void Character::jumping()
{
	if(mStatus == JUMP && mAnimation.getEndOfAnimation())
	{
		mStatus = INAIR;
	}

	if(mIsJumping)
	{
		mMovementSpeed.y += mAcceleration; // om mStatus �r JUMPING trycks char ner med v�rdet p� mAcceleration
		mJumping += mJumpTime;
		if(mJumping >= mMaxJump)
		{
			mJumping = 0;
			mFalling = true;
			mIsJumping = false;
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

void Character::fall()
{
	if(!mIsJumping)
	{
		if(mFalling)
		{
			mStatus = INAIR;
		}
		mFalling = true;
	}
}

void Character::interact(Entity* e)
{
	if(e->getBaseKind() == Entity::BLOCK)
	{
		// r�knar ut objektens radier och l�gger ihop dem
		float xRadius = mWidth / 2 + e->getWidth() / 2;
		float yRadius = mHeight / 2 + e->getHeight() / 2;

		// ber�knar differansen mellan tv� objekt
		float xDif = mPosition.x - e->getPosition().x;
		float yDif = mPosition.y - e->getPosition().y;

		// fr�ga vilken sida carakt�ren finns p�.
		if(std::abs(xDif / xRadius) > std::abs(yDif / yRadius)) // �r karakt�ren h�ger/v�nster eller �ver/under om blocket
		{
			if(xDif > 0) // kollar om karakt�ren �r h�ger eller v�nster
			{
				if(std::abs(yDif) < yRadius - 10) // kollar s� blocket inte ligger snett under
				{
					mPosition = sf::Vector2f(e->getPosition().x + xRadius - 3, mPosition.y);
				}
			}
			else
			{
				if(std::abs(yDif) < yRadius - 10)
				{
					mPosition = sf::Vector2f(e->getPosition().x - (xRadius - 3), mPosition.y);
				}
			}
		}
		else
		{
			if(yDif > 0) // kollar om karakt�ren �r under eller �ver
			{
				if(std::abs(xDif) < xRadius - 10) // kollar om blocket ligger snett �ver
				{
					mPosition = sf::Vector2f(mPosition.x, e->getPosition().y + yRadius);
					mJumping = 0;
					mFalling = true;
					mIsJumping = false;
					mMovementSpeed.y = 0;
				}
			}
			else
			{
				if(std::abs(xDif) < xRadius - 10)
				{
					mPosition = sf::Vector2f(mPosition.x, e->getPosition().y - yRadius);
					onblock();
				}
			}
		}
		
		if(e->getEntityKind() == Entity::ARROW)
		{
		
		}
	}
}