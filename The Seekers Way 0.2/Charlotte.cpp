#include "Charlotte.h"
#include "Animation.h"
#include "ImageManager.h"
#include "EntityManager.h"
#include "Shield.h"

const static float HEIGHT = 64;
const static float WIDTH = 128;

Charlotte::Charlotte(sf::Vector2f &position)
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
<<<<<<< HEAD
	walk();
	jump();
	SetShield();
=======
	if(currentEntity == mEntityKind)
	{
		walk();
		jump();
		Shield();
	}
	dontWalk(currentEntity);
	move();
	falling();
	fall();
>>>>>>> 1b171f5f25b860cdad9eaac767258f9fe1f8b960
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

void Charlotte::SetShield()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && mClock.getElapsedTime().asSeconds() >=1) // tryck "Q" för att aktivera en sköld (1 sec cd)
	{
		mClock.restart();
		if(mDirLeft)
		{
			EntityManager::getInstance()->addEntity(new Shield(sf::Vector2f(mPosition.x - 100, mPosition.y - 20)));
		}
		else if(mDirLeft == false)
		{
			EntityManager::getInstance()->addEntity(new Shield(sf::Vector2f(mPosition.x + 100, mPosition.y - 20)));
			
		}
	}
}