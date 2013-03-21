#include "Fenrir.h"
#include "Animation.h"
#include "Entity.h"
#include "ImageManager.h"
#include <iostream>
#include "Spiketrap.h"
#include "Sounds.h"

const static float HEIGHT = 64;
const static float WIDTH = 110;

const static float WALLHEIGHT = 110;
const static float WALLWIDTH = 59;

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
		mAnimation.init("fenrir.png", 60, 8);

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
	snowMistCountdown(currentEntity);
	updateSatatus();
	hurtTime();
	
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

			if(!mInSnowMist)
			{
				wallJump();	
			}
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
	sf::RenderStates states;
	if(mHurtShow)
	{
		states.shader = &mHurtShader;
	}
	ImageManager::render(&mAnimation.getSprite(), states);
}

void Fenrir::interact(Entity *e)
{
	EntityKind entityKind = e->getEntityKind();

	// kollar om vi är i snowmist mode
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
			if(std::abs(yDif) < yRadius - 10) // kollar så blocket inte ligger snett under
			{	
				if(xDif > 0)// kollar om karaktären är höger eller vänster
				{
					mWallJumpDirLeft = false;

					if(hitWall()) // kollar om karaktären kan gå in i walljump
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

					if(hitWall())
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
					mPosition = sf::Vector2f(mPosition.x, e->getPosition().y + (yRadius + mInSnowMist * 0.1)); // sista fixar så målnet inte fastnar i tak.
					hitBlockFromBelow();
				}
			}
			else
			{
				if(std::abs(xDif) < xRadius - 10)
				{
					mPosition = sf::Vector2f(mPosition.x, e->getPosition().y - (yRadius + mInSnowMist * 0.1));
					onblock();
				}
			}
		}
	}
	
	if(e->getEntityKind() == Entity::ARROW)
	{
		takeDamageFromArrow();
		e->destroy();
	}
	if(e->getEntityKind() == Entity::LAVA)
	{
		takeLavaDamage();
	}

	if((*e) == SPIKETRAP || (*e) == FIREBALL || (*e) == VINE)
	{
		if((*e) == VINE && yDif < 0)
		{
			if(std::abs(xDif) > xRadius - 10)
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

	if(mAnimationClock.getElapsedTime().asMilliseconds() > 300)
	{
		if(mStatus == ACTION2 || mStatus == ACTION1 || (mStatus == ACTION5 && mAnimation.getEndOfAnimation()) || (mStatus == JUMP && !mJumping))
		{
			mStatus = IDLE;
		}
	}
}

// omdefinerar movefunktion
void Fenrir::move()
{
	mPosition += mMovementSpeed;
	
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
			if(mAnimationClock.getElapsedTime().asMilliseconds() > 300)
			{
				if(mStatus != ACTION1 && mStatus != ACTION5 || mAnimation.getEndOfAnimation())
				{
  					mStatus = INAIR;	
				}
			}
		}
		mFalling = true;
	}
}

//
//--------------------------------------------------------------------------walljump
//

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

// ser till att hitboxen är som den ska
void Fenrir::updateHitbox()
{
	if(!mVerticalHitbox || mInSnowMist)
	{
		mHeight = HEIGHT;
		mWidth = WIDTH;
	}
}

// sätter igång walljumpen
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
				
				playJumpSound();

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

   				if(mHeight == HEIGHT && mWidth == WIDTH)
				{
					mPosition.y -= 5;
				}

				mHeight = WALLHEIGHT;
				mWidth = WALLWIDTH;

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

		Sounds::getInstance()->Play("snowmist.wav",60);
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		mCanPressSnowMist = true;
	}
	else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && mCanPressSnowMist && mInSnowMist && !mHitVine)
	{
		notInSnowMist();
		mCanPressSnowMist = false;
	}
}

// när tiden gått så tar misten slut
void Fenrir::snowMistCountdown(EntityKind &currentEntity)
{
	if(mSnowMistTime.getElapsedTime().asSeconds() > 1 && mInSnowMist && !mHitVine && 
		(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) 
		|| currentEntity != mEntityKind 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
	{
		notInSnowMist();
	}
}

// körs när man går ur snowmist
void Fenrir::notInSnowMist()
{
	mInSnowMist = false;	
	//mFenrirCanJump = true;
	mStatus = ACTION5;
	mAnimationClock.restart();
}

// flyttar på fenrir i snomistmode
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

void Fenrir::updateSatatus()
{
	if(mStatus == ACTION3 && mAnimation.getEndOfAnimation())
	{
		mStatus = ACTION4;
	}
}