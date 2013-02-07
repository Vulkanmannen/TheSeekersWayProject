#include "Shield.h"
#include "ImageManager.h"
#include "Charlotte.h"

static const float WIDTH = 20;
static const float HEIGHT = 120;
static const float SPRITEWIDTH = 64;
static const float SPRITEHEIGHT = 128;

Shield::Shield(sf::Vector2f &position, bool dirLeft):
	mAnimation("shield.png", 60, 0, SPRITEHEIGHT, SPRITEWIDTH),
	mShieldCount(0),
	mDirLeft(dirLeft)
{
	mPosition = position;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = SHIELD;
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
}


Shield::~Shield()
{
}

void Shield::update(EntityKind &currentEntity)
{
	
}

void Shield::render()
{
	mAnimation.update(mShieldCount * 2 + mDirLeft);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH / 2, mPosition.y - HEIGHT / 2));
	ImageManager::render(&mAnimation.getSprite());
}

void Shield::interact(Entity* e)
{
	if(e->getEntityKind() == ARROW)
	{
		mShieldCount++;
	}
	if(e->getBaseKind() == BLOCK)
	{
		mShieldCount = 5;
	}
}

int Shield::GetShieldCount()const
{
	return mShieldCount;
}