#include "Shield.h"
#include "ImageManager.h"
#include "Sounds.h"
#include "Charlotte.h"

static const float WIDTH = 20;
static const float HEIGHT = 120;
static const float SPRITEWIDTH = 64;
static const float SPRITEHEIGHT = 128;

Shield::Shield(sf::Vector2f &position, bool dirLeft):
	mAnimation("shield.png", 60, 7, SPRITEHEIGHT, SPRITEWIDTH),
	mShieldCount(0),
	mDirLeft(dirLeft),
	mOpen(false),
	mDead(false)
{
	mPosition = position;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = SHIELD;
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	mAnimation.update(mDirLeft);
	Sounds::getInstance()->Play("shield.wav", 40);
}


Shield::~Shield()
{
}

void Shield::update(EntityKind &currentEntity)
{
	mAnimation.update(mOpen * 2 + mShieldCount * 2 + mDirLeft);

	if(!mOpen && mAnimation.getEndOfAnimation())
	{
		mOpen = true;
	}
	if(mDead && mAnimation.getEndOfAnimation() && mClock.getElapsedTime().asMilliseconds() > 300)
	{
		destroy();
	}
}

void Shield::render()
{
	
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH / 2, mPosition.y - HEIGHT / 2));
	ImageManager::render(&mAnimation.getSprite());
}

void Shield::interact(Entity* e)
{
	if((*e) == ARROW)
	{
		if(mOpen)
		{
			mShieldCount++;
		}
		if(mShieldCount > 5)
		{
			mShieldCount = 5;
		}
	}
	if((*e) == BLOCK || (*e) == FIREBALL)
	{
		mShieldCount = 5;
	}
}

int Shield::GetShieldCount()const
{
	return mShieldCount;
}

bool Shield::getEndOfAnimation()const
{
	return mAnimation.getEndOfAnimation();
}

void Shield::setToDead()
{
	mDead = true;
	mClock.restart();
	Sounds::getInstance()->Play("shieldbreak.wav", 40);
}