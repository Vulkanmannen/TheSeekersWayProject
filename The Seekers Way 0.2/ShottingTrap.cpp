#include "ShottingTrap.h"
#include "ImageManager.h"

ShottingTrap::ShottingTrap(sf::Vector2f &position, bool shot, bool dirleft):
	mDirLeft(dirleft),
	mShotting(shot)
{
	mTexture.loadFromImage(*ImageManager::getImage("ShottingTrap.png"));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(position);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mShottingTimer.restart();
	mPosition = position;
}

ShottingTrap::~ShottingTrap()
{

}

void ShottingTrap::update()
{
	if(mShotting)
	{
		if(mShottingTimer.getElapsedTime().asSeconds() > 5)
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