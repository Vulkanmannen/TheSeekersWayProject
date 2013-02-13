#include "Charlotte.h"
#include "Animation.h"
#include "ImageManager.h"
#include "EntityManager.h"

#include "Sounds.h"

const static float HEIGHT = 115;
const static float WIDTH = 60;


Charlotte::Charlotte(sf::Vector2f &position):
	mIsShield(false)
	{
		mAnimation.init("Charlotte Sprite1_1.png", 60, 12);

		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = CHARLOTTE;
		mPosition = position;
	}

Charlotte::~Charlotte()
	{}

void Charlotte::update(EntityKind &currentEntity)
{
	if(currentEntity == mEntityKind)
	{
		walk();
		jump();
		SetShield();
	}
	dontWalk(currentEntity);
	move();
	jumping();
	falling();
	fall();
	GetShieldLife();
}

void Charlotte::render()
{
	mAnimation.update(/*mStatus * 2 + !mDirLeft*/0);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y - 71));
	ImageManager::render(&getSprite());
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
		mShield = new Shield(sf::Vector2f(mPosition.x + (mDirLeft? -1 : 1) * 100, mPosition.y - 7), mDirLeft);
			
		EntityManager::getInstance()->addEntity(mShield);

		mIsShield = true;
	}
}

void Charlotte::interact(Entity* e)
{
	Character::interact(e);
	if(e->getEntityKind() == PORTAL)
	{
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::X)) && mClock.getElapsedTime().asSeconds() >=1) // tryck "Q" för att aktivera en sköld (1 sec cd)
		{	
			mClock.restart();
			mPosition = static_cast<Portal*>(e)->getDestination();
		}
	}
}