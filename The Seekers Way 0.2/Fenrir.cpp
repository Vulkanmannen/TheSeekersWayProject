#include "Fenrir.h"
#include "Animation.h"
#include "Entity.h"
#include "ImageManager.h"


const static float HEIGHT = 64;
const static float WIDTH = 128;

Fenrir::Fenrir(sf::Vector2f &position):
	mWallJumping(false),
	mWallJumpCount(0),
	mWallJumpTime(15),
	mLastJumpDir(GROUND)
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

	if(!mWallJumping)
	{
		if(currentEntity == mEntityKind)
		{
			walk();
			jump();
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
	mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y -96));
	ImageManager::render(&getSprite());
}

sf::Sprite Fenrir::getSprite()
{
	return mAnimation.getSprite();
}

void Fenrir::interact(Entity *e)
{
	if(e->getBaseKind() == Entity::BLOCK)
	{
		// räknar ut objektens radier och lägger ihop dem
		float xRadius = mWidth / 2 + e->getWidth() / 2;
		float yRadius = mHeight / 2 + e->getHeight() / 2;

		// beräknar differansen mellan två objekt
		float xDif = mPosition.x - e->getPosition().x;
		float yDif = mPosition.y - e->getPosition().y;

		// fråga vilken sida caraktären finns på.
		if(std::abs(xDif / xRadius) > std::abs(yDif / yRadius)) // är karaktären höger/vänster eller över/under om blocket
		{
			if(std::abs(yDif) < yRadius - 20) // kollar så blocket inte ligger snett under
			{
				if(xDif > 0) // kollar om karaktären är höger eller vänster
				{
					mPosition = sf::Vector2f(e->getPosition().x + xRadius + 2, mPosition.y);
				}
				else
				{
					mPosition = sf::Vector2f(e->getPosition().x - (xRadius + 2), mPosition.y);
				}	

				mFalling = false;
				mMovementSpeed.y = 0.3;

				wallJump();
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
				}
			}
		}
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
}

// sätter igång walljumpen
void Fenrir::wallJump() 
{
	if(!mWallJumping && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{  
		if(mDirLeft == mLastJumpDir || mLastJumpDir == GROUND && mMovementSpeed.y < 0.4)
		{
			mWallJumping = true;
			mWallJumpCount = 0;
		
			mDirLeft = !mDirLeft;

			if(mDirLeft)
			{
				mMovementSpeed.x = -6;
				mLastJumpDir = LEFT;
			}
			else
			{
				mMovementSpeed.x = +6;
				mLastJumpDir = RIGHT;
			}
			mIsJumping = true;
			mMovementSpeed.y = -(mJump);
		}
	}
}