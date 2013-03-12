#include "Shield.h"
#include "ImageManager.h"
#include "Sounds.h"
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
	mAnimation.update(mShieldCount * 2 + mDirLeft);
	Sounds::getInstance()->Play("sheild.wav", 40);
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
	if((*e) == ARROW)
	{
		mShieldCount++;
		Sounds::getInstance()->Play("arrowtosheild.wav");
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