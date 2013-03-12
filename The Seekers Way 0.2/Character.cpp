#include "Character.h"
#include "Entity.h"
#include <cmath>
#include <iostream>
#include "ImageManager.h"
#include "Spiketrap.h"
#include "EntityManager.h"
#include "Sounds.h"


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
	mHurtTime(90),
	mCanMove(true),
	mCanMoveCount(0),
	mCanMoveTime(30),
	mCanPressJump(true),
	mHurtShow(false),
	mJumpSound(0)
{
	mAlive = true;
	mBaseKind = CHARACTER;
	mLayer = CHARACTERS;
	mHurtShader.loadFromFile("hurt.frag", sf::Shader::Fragment);
	mHurtShader.setParameter("texture", sf::Shader::CurrentTexture);
}

Character::~Character()
	{
	}

void Character::update(EntityKind &currentEntity)
{
	if(mCanMove)
	{
		dontWalk(currentEntity);
		jumping();
		falling();
		fall();
	}

	canMoveTime();
	hurtTime();
	slowdownPushBack();
}

// detta händer när en kraktär står på ett block
void Character::onblock()
{
	if(mFalling)
	{
		mFalling = false;
		if(mStatus == INAIR)
		{
			mStatus = IDLE;

			if(mMovementSpeed.y > 1)
			{
				Sounds::getInstance()->Play("land.wav", 70);
			}
		}
		mMovementSpeed.y = 0;
	}

	if(mStatus == ACTION2 && mAnimation.getEndOfAnimation() || (mStatus == JUMP && !mJumping) || (mStatus == ACTION1 && mAnimation.getEndOfAnimation()))
	{
		mStatus = IDLE;
	}
}

// detta händer när man träffar ett block underifrån
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

// Knapptryck tas in och movementspeed ändras
void Character::walk()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
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

// reglerar hur länge en karaktär är skadad
void Character::hurtTime()
{
	if(mHurt)
	{
		//std::cout << "hurt" << std::endl;
		if(mHurtClock.getElapsedTime().asMilliseconds() > 100)
		{
			mHurtClock.restart();
			mHurtShow = !mHurtShow;
		}
	}

	mHurtCount++;
	if(mHurtCount >= mHurtTime)
	{
		mHurt = false;
		mHurtShow = false;
		mHurtCount = 0;
	}
}

// reglerar när karaktären kan gå igen efter att han blivit skadad
void Character::canMoveTime()
{
	if(!mCanMove)
	{
		std::cout << "cantMove" << std::endl;
	}

	mCanMoveCount++;
	if(mCanMoveCount >= mCanMoveTime)
	{
		mCanMove = true;
		mCanMoveCount = 0;
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

// ser till att karaktärerna inte rör sig för fort
void Character::slowdownPushBack()
{
	if(!mCanMove)
	{
		mMovementSpeed.x *= 0.95;
		mMovementSpeed.y *= 0.9;

		if(mMovementSpeed.x < 0.01)
		{
			mMovementSpeed.x = 0;
		}
	}
}

// aktiverar så att man kan hoppa
void Character::jump()
{
	if(!mFalling && !mIsJumping)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mMovementSpeed.y < mMaxJump && mCanPressJump)
		{
			mCanPressJump = false;
			mStatus = JUMP;
			mIsJumping = true;
			mMovementSpeed.y = -mJump;


			playJumpSound();

		}
		else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			mCanPressJump = true;
		}
	}
}

void Character::playJumpSound()
{
	if(mJumpSound == 0)
	{
		Sounds::getInstance()->Play("jump1.wav", 80);
	}
	else if(mJumpSound == 1)
	{
		Sounds::getInstance()->Play("jump2.wav", 50);
	}
	else if(mJumpSound == 2)
	{
		Sounds::getInstance()->Play("jump3.wav", 80);
	}


	mJumpSound++;
	
	if(mJumpSound > 2)
	{
		mJumpSound = 0;
	}
}


// uppdaterar hoppet
void Character::jumping()
{
	if(mIsJumping)
	{
		mMovementSpeed.y += mAcceleration; // om mStatus är JUMPING trycks char ner med värdet på mAcceleration
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

	// räknar ut objektens radier och lägger ihop dem
	float xRadius = mWidth / 2 + e->getWidth() / 2;
	float yRadius = mHeight / 2 + e->getHeight() / 2;

	// beräknar differansen mellan två objekt
	float xDif = mPosition.x - e->getPosition().x;
	float yDif = mPosition.y - e->getPosition().y;


	if((*e) == BLOCK && (*e) != DOOR && (*e) != BRIDGE && (*e) != BIGBRIDGE)
	{


		// fråga vilken sida caraktären finns på.
		if(std::abs(xDif / xRadius) > std::abs(yDif / yRadius)) // är karaktären höger/vänster eller över/under om blocket
		{
			if(xDif > 0) // kollar om karaktären är höger eller vänster
			{
				if(std::abs(yDif) < yRadius - 10) // kollar så blocket inte ligger snett under
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
			if(yDif > 0) // kollar om karaktären är under eller över
			{
				if(std::abs(xDif) < xRadius - 10) // kollar om blocket ligger snett över
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
		
	if((*e) == ARROW)
	{
		takeDamageFromArrow();
	}
	
	if((*e) == LAVA)
	{
		takeLavaDamage();
	}

	if((*e) == SPIKETRAP || (*e) == FIREBALL || (*e) == VINE)
	{
		if((*e) == VINE && yDif < 0)
		{
			if(std::abs(xDif) > yRadius - 10)
			{
				return;
			}
		}

		if((*e) == SPIKETRAP)
		{
			if(!static_cast<Spiketrap*>(e)->getHurting())
			{
				return;
			}
		}

		sf::Vector2f dirVector = mPosition - e->getPosition();
		float length2 = dirVector.x * dirVector.x + dirVector.y * dirVector.y;

		dirVector.x *= (1 / std::sqrt(length2));
		dirVector.y *= (1 / std::sqrt(length2));

		dirVector.x *= 10;
		dirVector.y *= 30;

		mMovementSpeed = sf::Vector2f(0, 0);

		mMovementSpeed = dirVector;

		takeDamage();
	}
}

// funktion som sätter is hit till false
void Character::setIsHitToFalse()
{
	mIsHit = false;
}

// returnerar ishit status
bool Character::getIsHit()const
{
	return mIsHit; 
}

// skada som knuffar
void Character::takeDamage()
{
	if(!mHurt)
	{
		mIsHit = true;
		mHurt = true;
		mHurtClock.restart();
		mHurtShow = true;
		mHurtCount = 0;
	}

	mCanMove = false;
	mCanMoveCount = 0;

}

// skada som inte knuffar
void Character::takeDamageFromArrow()
{
	if(!mHurt)
	{
		mIsHit = true;
		mHurt = true;
		mHurtClock.restart();
		mHurtShow = true;
		mHurtCount = 0;
	}
}

// hämtar movementsped
sf::Vector2f Character::getMovementSpeed()const
{
	return mMovementSpeed;
}

void Character::takeLavaDamage()
{
	EntityManager::getInstance()->setPlayerLifeZero();
}