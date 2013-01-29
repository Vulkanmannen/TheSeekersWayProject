#include "ShottingTrap.h"
#include "ImageManager.h"

ShottingTrap::ShottingTrap(sf::Vector2f &position, bool dirleft):
	mDirLeft(dirleft),
	Shotting()
{
	mTexture.loadFromImage(*ImageManager::getImage("Block.png"));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(position);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
}

ShottingTrap::~ShottingTrap()
{

}

void ShottingTrap::update()
{

}

void ShottingTrap::Activate()
{
	Shotting = true;
}

void ShottingTrap::DisActivate()
{
	Shotting = false;
}