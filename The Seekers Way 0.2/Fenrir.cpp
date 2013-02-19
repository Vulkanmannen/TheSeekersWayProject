#include "Fenrir.h"
#include "Animation.h"
#include "Entity.h"
#include "ImageManager.h"
#include <iostream>
#include "Spiketrap.h"

const static float HEIGHT = 64;
const static float WIDTH = 110;

Fenrir::Fenrir(sf::Vector2f &position):
	mWallJumping(false),
	mCanPressWallJump(true),
	mHitWall(false),
	mFenrirCanJump(true),
	mWallJumpCount(0),
	mWallJumpTime(20),
	mLastJumpDir(GROUND),
	mVerticalHitbox(false),
	mCanPressSnowMist(true),
	mInSnowMist(false),
	mMoveSpeedInMist(0.5),
	mMaxMoveSpeedInMist(2),
	mCanSnowMist(true)
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
	updateHitbox();
	snowMistCountdown();

	if(!mWallJumping && mCanMove)
	{
		canWallJump();
	
		if(currentEntity == mEntityKind)
		{
			if(mInSnowMist)
			{
				moveInSnowMist();
			}
			else
			{
				walk();

				if(mFenrirCanJump)
				{
					jump();
				}
			}
			
			snowMist();
		}

		if(!mInSnowMist)
		{
			wallJump();	
		}	
		dontWalk(currentEntity);
	}

	if(!mInSnowMist)
	{
		if(mCanMove)
		{	
			jumping();
			falling();
			fall();
		}

		canMoveTime();
		hurtTime();
		slowdownPushBack();
	}

	mHitVine = false;
}

void Fenrir::render()
{
	mAnimation.update(mStatus * 2 + mDirLeft);
	if(!mVerticalHitbox)
	{
		mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y -96));
	}
	else 
	{
		mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y -64));
	}
	ImageManager::render(&mAnimation.getSprite());
}

void Fenrir::interact(Entity *e)
{
	EntityKind entityKind = e->getEntityKind();

	// kollar om vi �r i snowmist mode
	if(mInSnowMist)
	{
		if(entityKind == VINE)
		{
			mHitVine = true;
		}
		if(entityKind == VINE || entityKind == ARROW || entityKind == SPIKETRAP)
		{
			return;
		}
	}


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
			if(std::abs(yDif) < yRadius - 10) // kollar s� blocket inte ligger snett under
			{	
				if(xDif > 0)
				{
					mWallJumpDirLeft = false;

					if(hitWall()) // kollar om karakt�ren �r h�ger eller v�nster
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

					if(hitWall()) // kollar om karakt�ren �r h�ger eller v�nster
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
	
	if(e->getEntityKind() == Entity::ARROW)
	{
		mIsHit = true;
		e->destroy();
	}
	if(e->getEntityKind() == Entity::VINE)
	{
		mIsHit = true;
	}
	if(e->getEntityKind() == Entity::LAVA)
	{
		// die
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
//
//-----------------------------------------------------------omdefinitioner
//

void Fenrir::onblock()
{
	Character::onblock();
	
	// walljump
	mLastJumpDir = GROUND;
	mFenrirCanJump = true;
	mHitWall = false;		
	mVerticalHitbox = false;
	mCanHitWallClock.restart();

	// snowmist
	mCanSnowMist = true;

	if(mStatus == ACTION2 || mStatus == ACTION1 || (mStatus == JUMP && !mJumping))
	{
		mStatus = IDLE;
	}
}

// omdefinerar movefunktion
void Fenrir::move()
{
	mPosition	+= mMovementSpeed;
	
	if(!mInSnowMist)
	{
		mPosition.y	+= mGravity;
	}
}

// omdefinerar takeDamage
void Fenrir::takeDamage()
{
	Character::takeDamage();
	mInSnowMist = false;
}

// omdefinerar fall
void Fenrir::fall()
{
	if(!mIsJumping)
	{
		if(mFalling && !mWallJumping)
		{
			if(mStatus != ACTION1 || mAnimation.getEndOfAnimation())
			{
  				mStatus = INAIR;
			}
		}
		mFalling = true;
	}
}

//
//--------------------------------------------------------------------------walljump
//

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

// ser till att hitboxen �r som den ska
void Fenrir::updateHitbox()
{
	if(!mVerticalHitbox || mInSnowMist)
	{
		mHeight = HEIGHT;
		mWidth = WIDTH;
	}
}

// s�tter ig�ng walljumpen
void Fenrir::wallJump() 
{
	if(!mWallJumping && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mCanPressWallJump)
	{  
		mCanPressWallJump = false;
		
		if(mHitWall)
		{
			if(mDirLeft == mLastJumpDir || mLastJumpDir == GROUND)
			{
  				mWallJumping = true;
				mJumping = false;
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
// reglerar om karakt�ren har r�tt hastighet f�r att f� walljumpa
void Fenrir::canWallJump()
{
	if(mMovementSpeed.y > 2)
	{
		mHitWall = false;
	}
}

// kollar om fenrir tr�ffat en v�gg
bool Fenrir::hitWall()
{
	if(mStatus != WALK && mStatus != IDLE&& mCanHitWallClock.getElapsedTime().asSeconds() > 0.1 && !mInSnowMist)
	{
		mFalling = false;
		mFenrirCanJump = false;

		if(!mWallJumping)
		{
			if(!mIsJumping && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
			{
				mMovementSpeed.y = 0.3;
				mStatus = ACTION2;

				mHeight = WIDTH;
				mWidth = HEIGHT;

				mVerticalHitbox = true;
			}
			mWallJumping = false;
			mHitWall = true;
		}
		return true;
	}
	return false;
}

//
// ------------------------------------------------------------------snowmist
//

// kollar om man activerar snowmist
void Fenrir::snowMist()
{
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && mCanPressSnowMist && !mInSnowMist && mCanSnowMist)
	{
		mCanPressSnowMist = false;
		mInSnowMist = true;
		mSnowMistTime.restart();
		mFenrirCanJump = false;
		mCanSnowMist = false;
		
		mStatus = ACTION3;
		mMovementSpeed = sf::Vector2f(0, 0);
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		mCanPressSnowMist = true;
	}
	else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && mCanPressSnowMist && mInSnowMist && !mHitVine)
	{
		mInSnowMist = false;
		mCanPressSnowMist = false;
		mStatus = IDLE;
	}
}

// n�r tiden g�tt s� tar misten slut
void Fenrir::snowMistCountdown()
{
	if(mSnowMistTime.getElapsedTime().asSeconds() > 3 && mInSnowMist && !mHitVine)
	{
		mInSnowMist = false;	
		mFenrirCanJump = true;
		mStatus = IDLE;
	}
}

// flyttar p� fenrir i snomistmode
void Fenrir::moveInSnowMist()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && mMovementSpeed.y > -mMaxMoveSpeedInMist)
	{
		mMovementSpeed.y -= mMoveSpeedInMist;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mMovementSpeed.y < mMaxMoveSpeedInMist)
	{
		mMovementSpeed.y += mMoveSpeedInMist;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mMovementSpeed.x < mMaxMoveSpeedInMist)
	{
		mMovementSpeed.x += mMoveSpeedInMist;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mMovementSpeed.x > -mMaxMoveSpeedInMist)
	{
		mMovementSpeed.x -= mMoveSpeedInMist;
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && 
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && 
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mMovementSpeed = sf::Vector2f(0, 0);
	}
}