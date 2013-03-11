#include "DarkBinding.h"
#include "ImageManager.h"
#include "Sounds.h"

static const float HEIGHT = 24;
static const float WIDTH = 24;

static const float SPRITEHEIGHT = 64;
static const float SPRITEWIDTH = 64;

DarkBinding::DarkBinding(sf::Vector2f &position, bool dirLeft):
	mDirLeft(dirLeft),
	mMovementSpeed(8),
	mAnimation("darkbinding.png", 60, 4, SPRITEHEIGHT, SPRITEWIDTH)
	{
		mEntityKind = DARKBINDING;
		mAlive = true;
		mHeight = HEIGHT;
		mWidth = WIDTH;
		mPosition = position;
		Sounds::getInstance()->Play("shadowbolt 1.3.wav", 100, mPosition);
	}


DarkBinding::~DarkBinding()
	{}

void DarkBinding::update(EntityKind &currentEntity)
{
	move();
}

void DarkBinding::render()
{
	mAnimation.update(mDirLeft);
	mAnimation.setPosition(mPosition - sf::Vector2f(32, 32));
	ImageManager::render(&mAnimation.getSprite());	
}

void DarkBinding::interact(Entity* e)
{
	if(((*e) == BLOCK && (*e) != VINE) || *e == MAGICSWITCH)
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