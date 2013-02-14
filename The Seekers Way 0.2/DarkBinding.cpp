#include "DarkBinding.h"
#include "ImageManager.h"

static const float HEIGHT = 24;
static const float WIDTH = 24;

static const float SPRITEHEIGHT = 64;
static const float SPRITEWIDTH = 64;

DarkBinding::DarkBinding(sf::Vector2f &position, bool dirLeft):
	mDirLeft(dirLeft),
	mMovementSpeed(8),
	mAnimation(/*"darkbinding*/"FireBall.png", 60, 4, SPRITEHEIGHT, SPRITEWIDTH)
	{
		mEntityKind = DARKBINDING;
		mAlive = true;
		mHeight = HEIGHT;
		mWidth = WIDTH;
		mPosition = position;
	}


DarkBinding::~DarkBinding()
	{}

void DarkBinding::update(EntityKind &currentEntity)
{
	move();
}

void DarkBinding::render()
{
	mAnimation.update(0);
	mAnimation.setPosition(mPosition - sf::Vector2f(32, 32));
	ImageManager::render(&mAnimation.getSprite());	
}

void DarkBinding::interact(Entity* e)
{
	if(e->getBaseKind() == BLOCK)
	{
		destroy();
	}
}

// flyttar projektilen
void DarkBinding::move()
{
	if(mDirLeft)
	{
		mPosition.x -= mMovementSpeed;
	}
	else
	{
		mPosition.x += mMovementSpeed;
	}
}