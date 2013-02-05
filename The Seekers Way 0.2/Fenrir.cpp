#include "Fenrir.h"
#include "Animation.h"
#include "Entity.h"
#include "ImageManager.h"


const static float HEIGHT = 64;
const static float WIDTH = 128;

Fenrir::Fenrir(sf::Vector2f &position):
	mWallJumping(false),
	mCanPressWallJump(true),
	mCanWallJump(true),
	mHitWall(false),
	mFenrirCanJump(true),
	mWallJumpCount(0),
	mWallJumpTime(20),
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
		canWallJump();
		
		if(currentEntity == mEntityKind)
		{
			walk();
			wallJump();

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
		// r�knar ut objektens radier och l�gger ihop dem
		float xRadius = mWidth / 2 + e->getWidth() / 2;
		float yRadius = mHeight / 2 + e->getHeight() / 2;

		// ber�knar differansen mellan tv� objekt
		float xDif = mPosition.x - e->getPosition().x;
		float yDif = mPosition.y - e->getPosition().y;

		// fr�ga vilken sida carakt�ren finns p�.
		if(std::abs(xDif / xRadius) > std::abs(yDif / yRadius)) // �r karakt�ren h�ger/v�nster eller �ver/under om blocket
		{
			if(std::abs(yDif) < yRadius - 10) // kollar s� blocket inte ligger snett under
			{
				if(xDif > 0) // kollar om karakt�ren �r h�ger eller v�nster
				{
					mPosition = sf::Vector2f(e->getPosition().x + xRadius + 2, mPosition.y);
				}
				else
				{
					mPosition = sf::Vector2f(e->getPosition().x - (xRadius + 2), mPosition.y);
				}	

				hitWall();
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
					mLastJumpDir = GROUND;
					mFenrirCanJump = true;
					mCanWallJump = false;
					mHitWall = false;
				}
			}
		}
	}
}

// k�rs n�r walljumpen �r ig�ng, och st�nger av den n�r den �r klar 
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

// s�tter ig�ng walljumpen
void Fenrir::wallJump() 
{
	if(mStatus == ACTION1 && mAnimation.getEndOfAnimation())
	{
		mStatus = INAIR;
	}

	if(!mWallJumping && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mCanPressWallJump)
	{  
		mCanPressWallJump = false;
		
		if(mCanWallJump && mHitWall)
		{
			if(mDirLeft == mLastJumpDir || mLastJumpDir == GROUND)
			{
  				mWallJumping = true;
				mHitWall = false;
				mWallJumpCount = 0;

				mStatus = IDLE;
		
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
				//mIsJumping = true;
				mMovementSpeed.y = -(mJump);
			}
		}
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		mCanPressWallJump = true;
	}
}
// reglerar om karakt�ren har r�tt hastighet f�r att f� walljumpa
void Fenrir::canWallJump()
{
	if(mMovementSpeed.y < 32 && mMovementSpeed.y > -22.3)
	{
		mCanWallJump = true;
	}
	else
	{
		mCanWallJump = false;
	}
}

// kollar om fenrir tr�ffat en v�gg
void Fenrir::hitWall()
{
	if(mStatus != WALK)
	{
		mFalling = false;
		mFenrirCanJump = false;

		if(!mWallJumping)
		{
			if(!mIsJumping)
			{
				mMovementSpeed.y = 0.3;
			}
			mHitWall = true;
		}
	}
}
