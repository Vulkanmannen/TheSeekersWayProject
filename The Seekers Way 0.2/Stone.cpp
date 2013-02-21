#include "Stone.h"
#include "ImageManager.h"
#include <math.h>

static const float WIDTH = 128;
static const float HEIGHT = 128;

static const float SPRITEWIDTH = 141;
static const float SPRITEHEIGHT = 141;

Stone::Stone(sf::Vector2f Position):
	mMovementSpeed(0,0),
	mGravity(5),
	mDecrease(0.6),
	mFalling(false),
	mtelekinesis(false),
	mtelemove(false),
	mOnBlock(false),
	mCanMove(true),
	mAnimation("stone.png", 80, 6, SPRITEHEIGHT, SPRITEWIDTH)
{
	mPosition = Position + sf::Vector2f(WIDTH/2 - 32, HEIGHT/2 - 32);
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = STONE;
	mLayer = FORGROUND;

	mAnimation.setPosition(sf::Vector2f(mPosition.x - SPRITEWIDTH / 2, mPosition.y - SPRITEHEIGHT / 2));
}

Stone::~Stone()
{

}

void Stone::update(EntityKind &currentEntity)
{
	move();

	if(mtelekinesis)
	{
		telekinesis();
	}

	else 
	{
		falling();
	}

	if(mtelemove && mtelekinesis && mCanMove)
	{
		mBaseKind = OBJECT;
	}
	else
	{
		mBaseKind = BLOCK;
	}

	attraction();
	mFalling = true;
	mCanMove = true;

	mAnimation.update(mtelekinesis);
}

void Stone::render()
{
	mAnimation.setPosition(sf::Vector2f(mPosition.x - SPRITEWIDTH / 2, mPosition.y - SPRITEHEIGHT / 2));
	ImageManager::render(&mAnimation.getSprite());
}

void Stone::telekinesis()
{
	if(mMovementSpeed.x * mMovementSpeed.x + mMovementSpeed.y * mMovementSpeed.y < 10)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			mMovementSpeed.x -= 1;
			mOnBlock = false;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			mMovementSpeed.x += 1;
			mOnBlock = false;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			mMovementSpeed.y -= 1;
			mOnBlock = false;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			mMovementSpeed.y += 1;
			mOnBlock = false;
		}
	}
}

void Stone::move()	   
{
	mRblock ? (mMovementSpeed.x > 0 ? mMovementSpeed.x = 0 : NULL ) : NULL;
	mLblock ? (mMovementSpeed.x < 0 ? mMovementSpeed.x = 0 : NULL ) : NULL;
	mUblock ? (mMovementSpeed.y < 0 ? mMovementSpeed.y = 0 : NULL ) : NULL;
	mDblock ? (mMovementSpeed.y > 0 ? mMovementSpeed.y = 0 : NULL ) : NULL;

	if(mtelemove && mCanMove)
	{
		mPosition	+= mMovementSpeed;
	}
	mMovementSpeed -= sf::Vector2f( 0.1*mMovementSpeed.x, 0.1*mMovementSpeed.y);

	mRblock	= false;
	mLblock	= false;
	mUblock	= false;
	mDblock	= false;
}

void Stone::falling() 
{
	mPosition.y	+= mGravity;
	if(mFalling)
	{
		mMovementSpeed.y += mDecrease;
	}
}

void Stone::interact(Entity* e)
{
	// räknar ut objektens radier och lägger ihop dem
	float xRadius = mWidth / 2 + e->getWidth() / 2;
	float yRadius = mHeight / 2 + e->getHeight() / 2;

	// beräknar differansen mellan två objekt
	float xDif = mPosition.x - e->getPosition().x;
	float yDif = mPosition.y - e->getPosition().y;
	
	if((*e == CHARACTER) && yDif > yRadius - 20)
	{
		mCanMove = false;
	}

	if(e->getBaseKind() == Entity::BLOCK || (e->getBaseKind() == Entity::CHARACTER && mtelekinesis && mtelemove) && mCanMove)
	{
		// fråga vilken sida caraktären finns på.
		if(std::abs(xDif / xRadius) > std::abs(yDif / yRadius)) // är karaktären höger/vänster eller över/under om blocket
		{
			if(xDif > 0) // kollar om karaktären är höger eller vänster
			{
				if(std::abs(yDif) < yRadius - 10) // kollar så blocket inte ligger snett under
				{
					mPosition -= sf::Vector2f(mPosition.x - (e->getPosition().x + xRadius - 0), 0);
					mLblock = true;
				}
			}
			else
			{
				if(std::abs(yDif) < yRadius - 10)
				{
					mPosition -= sf::Vector2f(mPosition.x - (e->getPosition().x - (xRadius - 0)), 0);
					mRblock = true;
				}
			}
		}
		else
		{
			if(yDif > 0) // kollar om karaktären är under eller över
			{
				if(std::abs(xDif) < xRadius - 10) // kollar om blocket ligger snett över
				{
					mPosition -= sf::Vector2f( 0,mPosition.y - (e->getPosition().y + yRadius - 0));
					mUblock = true;
					if(e->getBaseKind() == CHARACTER || e->getEntityKind() == STONE)
					{
						mRblock = true; 
						mLblock = true;
					}
					//mJumping = 0;
					//mIsJumping = false;
				}
			}
			else
			{
				if(std::abs(xDif) < xRadius - 10)
				{
					mPosition -= sf::Vector2f(0, mPosition.y - (e->getPosition().y - (yRadius - 0)));
					mDblock = true;
					if(e->getBaseKind() == BLOCK)
					{
						mOnBlock = true;
					}
					//mMovementSpeed.y = 0;
					//onblock();
					mFalling = false;
				}
			}
		}
	}
}

void Stone::attraction()
{
	if(mtelekinesis == true && mtelemove == false)
	{
		if((mPosition.x - mKibaPos.x) * (mPosition.x - mKibaPos.x) + (mPosition.y - mKibaPos.y) * (mPosition.y - mKibaPos.y) > 160 * 160 + 192 * 192)
		{
			float r = sqrt(float(160 * 160 + 192 * 192))-0.1;
			mPosition = sf::Vector2f(	mKibaPos.x + r*cos(atan2(mPosition.y - mKibaPos.y, mPosition.x - mKibaPos.x)),	
										mKibaPos.y + r*sin(atan2(mPosition.y - mKibaPos.y, mPosition.x - mKibaPos.x)));
		}
	}
}

bool Stone::onblock()
{
	return mOnBlock;
}