#include "Fenrir.h"
#include "Animation.h"
#include "Entity.h"
#include "ImageManager.h"
#include <iostream>

const static float HEIGHT = 64;
const static float WIDTH = 128;

Fenrir::Fenrir(sf::Vector2f &position):
	mWallJumping(false),
	mCanPressWallJump(true),
	mHitWall(false),
	mFenrirCanJump(true),
	mWallJumpCount(0),
	mWallJumpTime(20),
	mLastJumpDir(GROUND),
	mSliding(false)
	{
		mAnimation.init("fenrir.png", 60, 7);

		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = FENRIR;
		mPosition = position;
	}

Fenrir::~Fenrir()
	{}

void Fenrir::update(EntityKind &currentEntity)
{
	move();
	isWallJumping();
	wallJump();
	
	if(!mWallJumping)
	{
		canWallJump();
		
		if(currentEntity == mEntityKind)
		{
			walk();

			

			if(mFenrirCanJump)
			{
				jump();
			}
		}

		dontWalk(currentEntity);
		jumping();
		falling();
		fall();
	}
}

void Fenrir::render()
{
	mAnimation.update(mStatus * 2 + mDirLeft);
	if(!mSliding)
	{
		mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y -96));
	}
	else 
	{
		mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y -64));
	}
	ImageManager::render(&getSprite());

	std::cout << mStatus << std::endl;
}

sf::Sprite Fenrir::getSprite()
{
	return mAnimation.getSprite();
}

void Fenrir::interact(Entity *e)
{
	// räknar ut objektens radier och lägger ihop dem
	float xRadius = mWidth / 2 + e->getWidth() / 2;
	float yRadius = mHeight / 2 + e->getHeight() / 2;

	// beräknar differansen mellan två objekt
	float xDif = mPosition.x - e->getPosition().x;
	float yDif = mPosition.y - e->getPosition().y;

	if(e->getBaseKind() == Entity::BLOCK)
	{


		// fråga vilken sida caraktären finns på.
		if(std::abs(xDif / xRadius) > std::abs(yDif / yRadius) || e->getEntityKind() == DOOR) // är karaktären höger/vänster eller över/under om blocket
		{
			if(std::abs(yDif) < yRadius - 10) // kollar så blocket inte ligger snett under
			{	
				if(xDif > 0)
				{
					mWallJumpDirLeft = false;

					if(hitWall()) // kollar om karaktären är höger eller vänster
					{
						mPosition = sf::Vector2f(e->getPosition().x + xRadius - 3, mPosition.y);
					}
					else
					{	
						mPosition = sf::Vector2f(e->getPosition().x + xRadius + 2, mPosition.y);
					}
				}
				else
				{
					mWallJumpDirLeft = true;

					if(hitWall()) // kollar om karaktären är höger eller vänster
					{
						mPosition = sf::Vector2f(e->getPosition().x - (xRadius - 3), mPosition.y);
					}
					else
					{
						mPosition = sf::Vector2f(e->getPosition().x - (xRadius + 2), mPosition.y);
					}
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
					mLastJumpDir = GROUND;
					mFenrirCanJump = true;
					mHitWall = false;		
					mSliding = false;
					mCanHitWallClock.restart();

					if(mStatus == ACTION2)
					{
						mStatus = IDLE;
					}
				}
			}
		}
	}
	
	if(e->getEntityKind() == Entity::ARROW)
	{
		mIsHit = true;
	}

	if(e->getEntityKind() == SPIKETRAP || e->getEntityKind() == FIREBALL)
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
		mIsHit = true;
	}
}

// körs när walljumpen är igång, och stänger av den när den är klar 
void Fenrir::isWallJumping()
{
	if(mWallJumping)
	{
		mWallJumpCount++;
		if(mWallJumpCount >= mWallJumpTime)
		{
			mWallJumping = false;
			mWallJumpCount = 0;
		}
	}

	if(!mSliding/* || mStatus == INAIR*/)
	{
		mHeight = 64;
		mWidth = 128;
	}
}

// sätter igång walljumpen
void Fenrir::wallJump() 
{
	if(mStatus == ACTION1 && mAnimation.getEndOfAnimation())
	{
		mStatus = INAIR;
	}

	if(!mWallJumping && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mCanPressWallJump)
	{  
		mCanPressWallJump = false;
		
		if(mHitWall)
		{
			if(mDirLeft == mLastJumpDir || mLastJumpDir == GROUND)
			{
  				mWallJumping = true;
				mHitWall = false;
				mWallJumpCount = 0;

				mStatus = ACTION1;

				mMovementSpeed = sf::Vector2f(0,0);
				
				mMovementSpeed.y = -(mJump);
				
				if(mWallJumpDirLeft)
				{
					mDirLeft = true;
					mMovementSpeed.x = -6;
					mLastJumpDir = LEFT;
				}
				else
				{
					mDirLeft = false;
					mMovementSpeed.x = 6;
					mLastJumpDir = RIGHT;
				}

				
			}
		}
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		mCanPressWallJump = true;
	}
}
// reglerar om karaktären har rätt hastighet för att få walljumpa
void Fenrir::canWallJump()
{
	if(mMovementSpeed.y > 2)
	{
		mHitWall = false;
	}
}

// kollar om fenrir träffat en vägg
bool Fenrir::hitWall()
{
	if(mStatus != WALK && mStatus != IDLE && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && mCanHitWallClock.getElapsedTime().asSeconds() > 0.1)
	{
		mFalling = false;
		mFenrirCanJump = false;

		if(!mWallJumping)
		{
			if(!mIsJumping)
			{
				mMovementSpeed.y = 0.3;
				mStatus = ACTION2;

				mHeight = 128;
				mWidth = 64;

				mSliding = true;
			}
			mHitWall = true;
		}
		return true;
	}
	return false;
}
