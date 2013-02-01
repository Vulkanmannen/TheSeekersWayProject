#include "Fenrir.h"
#include "Animation.h"
#include "Entity.h"
#include "ImageManager.h"


const static float HEIGHT = 64;
const static float WIDTH = 128;

Fenrir::Fenrir(sf::Vector2f &position)
	{
		mAnimation.init("fenrir.png", 60, 7);

		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = FENRIR;
		mPosition = position;
	}

Fenrir::~Fenrir()
	{}

void Fenrir::update(EntityKind &currentEntity)
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

void Fenrir::render()
{
	mAnimation.update(mStatus * 2 + mDirLeft);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y -96));
	ImageManager::render(&getSprite());
}

sf::Sprite Fenrir::getSprite()
{
	return mAnimation.getSprite();
}