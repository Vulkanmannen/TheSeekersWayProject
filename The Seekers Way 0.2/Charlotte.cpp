#include "Charlotte.h"
#include "Animation.h"
#include "ImageManager.h"
#include "EntityManager.h"

#include "Sounds.h"

const static float HEIGHT = 64;
const static float WIDTH = 128;

Charlotte::Charlotte(sf::Vector2f &position):
	mIsShield(false)
	{
		mAnimation.init("Sheekabebad.png", 60, 7);

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
}

void Charlotte::render()
{
	mAnimation.update(mStatus * 2 + mDirLeft);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y -96));
	ImageManager::render(&getSprite());
}

sf::Sprite Charlotte::getSprite()
{
	return mAnimation.getSprite();

}

void Charlotte::GetShieldLife()
{
	if(mShield->GetShieldCount() <= 0)
	{
		mShield->destroy();
		mIsShield = false;
	}
}

void Charlotte::SetShield()
{
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && mClock.getElapsedTime().asSeconds() >=1) // tryck "Q" för att aktivera en sköld (1 sec cd)
	{	
		mClock.restart();
		mShield = new Shield(sf::Vector2f(mPosition.x + (mDirLeft? -1 : 1) * 100, mPosition.y - 20), mDirLeft);
		mIsShield = true;
		if(mIsShield == true)
		{
			mShield->destroy();
			EntityManager::getInstance()->addEntity(new Shield(sf::Vector2f(mPosition.x - 100, mPosition.y - 20), mDirLeft));
		}
	}
}