#include "Shield.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 128;

Shield::Shield(sf::Vector2f &position, bool dirLeft):
	mAnimation("shield.png", 60, 0, HEIGHT, WIDTH),
	mShieldCount(0),
	mDirLeft(mDirLeft)
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
	mAnimation.update(/*mShieldCount * 2 + mDirLeft*/0);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&mAnimation.getSprite());
}

void Shield::interact(Entity* e)
{
	if(e->getEntityKind() == ARROW)
	{
		mShieldCount++;
	}
}

int Shield::GetShieldCount()const
{
	return mShieldCount;
}