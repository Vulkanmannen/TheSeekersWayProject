#include "Character.h"
#include "Entity.h"
#include <cmath>

Character::Character():
	mMovementSpeed(0, 0),
	mAcceleration(0.33),
	mDecrease(0.4),
	mGravity(5.0),
	mStatus(IDLE),
	mDirLeft(false),
	mJump(14.5),
	mRun(6.0),
	mMaxRun(6.0),
	mMaxJump(30),
	mJumpTime(1.0),
	mJumping(0.0),
	mFalling(false),
	mIsJumping(false),
	mAnimation(128, 128),
	mIsHit(false),
	mMaxSpeed(20),
	mHurt(false),
	mHurtCount(0),
	mHurtTime(20),
	mCanWalk(true),
	mCanWalkCount(0),
	mCanWalkTime(30)
{
	mAlive = true;
	mBaseKind = CHARACTER;
}

Character::~Character()
	{}

void Character::update()
{
	canWalkTime();
	hurtTime();
	dontMoveToFast();
}

// detta h�nder n�r en krakt�r st�r p� ett block
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

// detta h�nder n�r man tr�ffar ett block underifr�n
void Character::hitBlockFromBelow()
{
	mJumping = 0;
	mFalling = true;
	mIsJumping = false;
	mMovementSpeed.y = 0;
}


// Flyttar Character
void Character::move()
{
	mPosition	+= mMovementSpeed;
	mPosition.y	+= mGravity;
}

// Knapptryck tas in och movementspeed �ndras
void Character::walk()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mCanWalk)
	{
		mMovementSpeed.x -= mRun;
		
		if(mMovementSpeed.x < -mMaxRun)
		{
			mMovementSpeed.x = -mMaxRun;	
		}
		
		if(mStatus == IDLE)
		{
			mStatus = WALK;
		}
		mDirLeft = true;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mCanWalk)
	{
		mMovementSpeed.x += mRun;
		
		if(mMovementSpeed.x > mMaxRun)
		{
			mMovementSpeed.x = mMaxRun;
		}
		
		if(mStatus == IDLE)
		{
			mStatus = WALK;
		}
		mDirLeft = false;
	}
}

// reglerar hur l�nge en karakt�r �r skadad
void Character::hurtTime()
{
	mHurtCount++;
	if(mHurtCount >= mHurtTime)
	{
		mHurt = false;
	}
}

// reglerar n�r karakt�ren kan g� igen efter att han blivit skadad
void Character::canWalkTime()
{
	mCanWalkCount++;
	if(mCanWalkCount >= mCanWalkTime)
	{
		mCanWalk = true;
	}
}

// stoppar en gubbe
void Character::dontWalk(EntityKind &currentEntity)
{
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || currentEntity != mEntityKind)
	{
		mMovementSpeed.x *= 0.7;

		if(std::abs(mMovementSpeed.x) < 0.1)
		{
			mMovementSpeed.x = 0;
		}

		if(mStatus == WALK)
		{
			mStatus = IDLE;
		}
	}
}

// ser till att karakt�rerna inte r�r sig f�r fort
void Character::dontMoveToFast()
{
	if(std::abs(mMovementSpeed.x) > mMaxSpeed)
	{
		if(mMaxSpeed > 0)
		{
			mMovementSpeed.x = -mMaxSpeed;
		}
		else
		{
			mMovementSpeed.x = mMaxSpeed;
		}
	}

	if(mMovementSpeed.y > mJump)
	{
		mMovementSpeed.y = mJump;
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
			mMovementSpeed.y = -mJump;
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
			mMovementSpeed.y = 0;
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

	// r�knar ut objektens radier och l�gger ihop dem
	float xRadius = mWidth / 2 + e->getWidth() / 2;
	float yRadius = mHeight / 2 + e->getHeight() / 2;

	// ber�knar differansen mellan tv� objekt
	float xDif = mPosition.x - e->getPosition().x;
	float yDif = mPosition.y - e->getPosition().y;


	if((*e) == BLOCK && (*e) != DOOR && (*e) != BRIDGE && (*e) != BIGBRIDGE)
	{


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
					hitBlockFromBelow();
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
	}
		
	if(e->getEntityKind() == ARROW || e->getEntityKind() == Entity::VINE/* || (*e) == SPIKETRAP || (*e) == FIREBALL*/)
	{
		takeDamage();
	}
	
	if(e->getEntityKind() == LAVA)
	{
		// die
	}

	if(e->getEntityKind() == SPIKETRAP || e->getEntityKind() == FIREBALL)
	{
		sf::Vector2f dirVector = mPosition - e->getPosition();

		mMovementSpeed += sf::Vector2f(dirVector.x * 0.3, dirVector.y * 0.3);

		takeDamage();
	}
}

// funktion som s�tter is hit till false
void Character::setIsHitToFalse()
{
	mIsHit = false;
}

// returnerar ishit status
bool Character::getIsHit()const
{
	return mIsHit;
}

void Character::takeDamage()
{
	mIsHit = true;
	mHurt = true;
	mCanWalk = false;
}