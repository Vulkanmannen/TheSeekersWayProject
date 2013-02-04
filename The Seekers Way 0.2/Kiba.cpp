#include "Kiba.h"
#include "Animation.h"
#include "ImageManager.h"

const static float HEIGHT = 128;
const static float WIDTH = 64;

Kiba::Kiba(sf::Vector2f &position)
	{
		mAnimation.init("fenrir.png", 60, 7);
		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = KIBA;
		mPosition = position;
	}


Kiba::~Kiba()
	{}

void Kiba::update(EntityKind &currentEntity)
{
	if(currentEntity == mEntityKind)
	{
		walk();
		jump();
	}
	dontWalk(currentEntity);
	move();
	jumping();
	falling();
	fall();
}


void Kiba::render()
{
	mAnimation.update(mStatus * 2 + mDirLeft);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y -64));
	ImageManager::render(&mAnimation.getSprite());
}

void Kiba::telekinesis()
{

}