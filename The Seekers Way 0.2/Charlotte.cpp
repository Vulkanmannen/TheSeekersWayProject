#include "Charlotte.h"
#include "Animation.h"
#include "ImageManager.h"
#include "EntityManager.h"

#include "Sounds.h"

const static float HEIGHT = 115;
const static float WIDTH = 60;


Charlotte::Charlotte(sf::Vector2f &position):
	mIsShield(false),
	mActiveCharacter(false),
	mTimeToTeleport(0.5),
	mTeleporting(false),
	mActivatingShield(false),
	mPlayCantTeleport(false),
	mCanPressTeleport(true)
	{
		mAnimation.init("charlotte.png", 60, 12);

		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = CHARLOTTE;
		mPosition = position + sf::Vector2f(0, 38);
	}

Charlotte::~Charlotte()
	{}

void Charlotte::update(EntityKind &currentEntity)
{
	move();

	if(mCanMove && !mTeleporting && !mActivatingShield)
	{
		if(currentEntity == mEntityKind)
		{
			walk();
			jump();
			SetShield();

			if(mPlayCantTeleport)
			{
				Sounds::getInstance()->Play("errorsound.wav",30);
				mPlayCantTeleport = false;
			}
			else if(!mTeleporting && (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::X)) && mCanPressTeleport)
			{
				mPlayCantTeleport = true;
				mCanPressTeleport = false;
			}
			else if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::X)))
			{
				mCanPressTeleport = true;
			}
		}
	}
	else if(mTeleporting)
	{
		teleporting();
	}

	GetShieldLife();
	shieldTime();

	if(mEntityKind == currentEntity)
	{
		mActiveCharacter = true;
	}
	else
	{
		mActiveCharacter = false;
	}


	Character::update(currentEntity);
}

void Charlotte::render()
{
	sf::RenderStates states;
	if(mHurtShow)
	{
		states.shader = &mHurtShader;
	}
	mAnimation.update(mStatus * 2 + mDirLeft);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y - 69));
	ImageManager::render(&getSprite(), states);
}

sf::Sprite Charlotte::getSprite()
{
	return mAnimation.getSprite();
}

void Charlotte::GetShieldLife()
{
	if(mIsShield)
	{
		if(mShield->GetShieldCount() >= 5)
		{
			mShield->destroy();
			mIsShield = false;
		}
	}
}

void Charlotte::SetShield()
{
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && mClock.getElapsedTime().asSeconds() >=1) // tryck "Q" för att aktivera en sköld (1 sec cd)
	{	
		if(mIsShield == true)
		{
			mShield->destroy();	
		}
		mClock.restart();
		mShield = new Shield(sf::Vector2f(mPosition.x + (mDirLeft? -1 : 1) * 100, mPosition.y - 13), mDirLeft);
		
		if(!mJumping && !mFalling)
		{
			mStatus = ACTION2;
		}
		mShieldClock.restart();
		mMovementSpeed.x = 0;

		EntityManager::getInstance()->addEntity(mShield);

		mActivatingShield = true;
		mIsShield = true;
	}
}

void Charlotte::interact(Entity* e)
{
	Character::interact(e);
	if(e->getEntityKind() == PORTAL && mActiveCharacter)
	{
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::X)) && mClock.getElapsedTime().asSeconds() >=1) // tryck "Q" för att aktivera en sköld (1 sec cd)
		{	
			mClock.restart();
			mTeleporting = true;
			mTeleportClock.restart();
			mPortal = static_cast<Portal*>(e);
			mStatus = ACTION1;

			Sounds::getInstance()->Play("teleport.wav");
			mPlayCantTeleport = false;
		}
	}
}

void Charlotte::teleporting()
{
	if(mTeleporting && mTeleportClock.getElapsedTime().asSeconds() > mTimeToTeleport)
	{
		if(mPortal != NULL)
		{
			mPosition = mPortal->getDestination();
			EntityManager::getInstance()->setCameraSpeedToChangePos();
			mPortal = NULL;		
		}
		else if(mAnimation.getEndOfAnimation())
		{
			mTeleporting = false;
		}
	}
}

void Charlotte::shieldTime()
{
	if(mShieldClock.getElapsedTime().asSeconds() > 0.6 && mActivatingShield)
	{
		mActivatingShield = false;
	}
}