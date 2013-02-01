#include "Shield.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 128;

Shield::Shield(sf::Vector2f &position, bool dirLeft):
	mAnimation("shield.png", 60, 1, HEIGHT, WIDTH),
<<<<<<< HEAD
	mShieldCount(0)
=======
	ShieldCount(5),
	mDirLeft(dirLeft)
>>>>>>> 88feaf0560902fbf06e8a8fa37a0bdedf431bcce
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
	ShieldLife();
}

void Shield::render()
{
	mAnimation.update(5 - ShieldCount + mDirLeft);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&mAnimation.getSprite());
}

void Shield::interact(Entity* e)
{
<<<<<<< HEAD
	if(e->getEntityKind() == ARROW)
=======
	if(ShieldCount <= 0)
>>>>>>> 88feaf0560902fbf06e8a8fa37a0bdedf431bcce
	{
		mShieldCount++;
	}
}

int Shield::GetShieldCount()const
{
	return mShieldCount;
}