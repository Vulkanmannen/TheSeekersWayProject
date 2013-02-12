#include "ShottingTrap.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 64;

ShottingTrap::ShottingTrap(sf::Vector2f &position, int time, bool shot, bool dirleft):
	mDirLeft(dirleft),
	mShotting(shot),
	mTimeToShot(time * 100)
{
	mEntityKind = SHOTTINGTRAP;
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mTexture.loadFromImage(*ImageManager::getImage("ShottingTrap.png"));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(position);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mPosition = position;
}

ShottingTrap::~ShottingTrap()
{

}

void ShottingTrap::update(EntityKind &currentEntity)
{
	if(mShotting)
	{
		if(mShottingTimer.getElapsedTime().asMilliseconds() > mTimeToShot)
		{
			EntityManager::getInstance()->addEntity(new Arrow(mPosition, mDirLeft));
			mShottingTimer.restart();
		}
	}
}

void ShottingTrap::Activate()
{
	mShotting = true;
}

void ShottingTrap::DisActivate()
{
	mShotting = false;
}