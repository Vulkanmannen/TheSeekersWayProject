#include "WoodenWall.h"
#include "ImageManager.h"

static const float WIDTH = 32;
static const float HEIGHT = 128;

static const float SPRITEWIDTH = 128;
static const float SPRITEHEIGHT = 128;

WoodenWall::WoodenWall(sf::Vector2f &position):
	mAnimation("woodenwall.png", 60, 12, SPRITEHEIGHT, SPRITEWIDTH),
	mHit(false)
	{
		mPosition = position + sf::Vector2f(WIDTH/2 - 32, HEIGHT/2 - 32);
		mAlive = true;
		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = WOODENWALL;
	} 


WoodenWall::~WoodenWall()
	{}

void WoodenWall::update(EntityKind &currentCharacter)
{
	mAnimation.update(mHit);
	if(mAnimation.getEndOfAnimation() && mHit && mAnimationClock.getElapsedTime().asMilliseconds() > 300)
	{
		destroy();
	}
}

void WoodenWall::render()
{
	mAnimation.setPosition(sf::Vector2f(mPosition.x - SPRITEWIDTH / 2, mPosition.y - SPRITEHEIGHT / 2));
	ImageManager::render(&mAnimation.getSprite());
}

// om en darkbinding åker in i switchen så öppnas dörren
void WoodenWall::interact(Entity *e)
{
	if(e->getEntityKind() == SLASH)
	{
		Activate();
	}
}

// öppnar dörren
void WoodenWall::Activate()
{
	if(!mHit)
	{
		mAnimationClock.restart();
	}
	mHit = true;
}