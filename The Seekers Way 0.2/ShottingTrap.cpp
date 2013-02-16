#include "ShottingTrap.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 64;

ShottingTrap::ShottingTrap(sf::Vector2f &position, int time, bool shot, bool dirleft):
	mDirLeft(dirleft),
	mShotting(shot),
	mTimeToShot(time * 100),
	mAnimation("spikerune.png", 100, 10, HEIGHT, WIDTH)
{
	mEntityKind = SHOTTINGTRAP;
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	//mTexture.loadFromImage(*ImageManager::getImage("spikerune.png"));
	//mSprite.setTexture(mTexture);
	//mSprite.setPosition(position);
	//mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mPosition = position;
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
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

	mAnimation.update(0);
}

void ShottingTrap::render()
{
	ImageManager::render(&mAnimation.getSprite());
}

void ShottingTrap::Activate()
{
	mShotting = true;
}

void ShottingTrap::DisActivate()
{
	mShotting = false;
}