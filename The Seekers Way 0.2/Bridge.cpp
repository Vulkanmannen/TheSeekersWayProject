#include "Bridge.h"
#include "ImageManager.h"

static const float WIDTH = 128;
static const float HEIGHT = 64;

Bridge::Bridge(sf::Vector2f &position, bool closed):
	mAnimation("Door2.png", 60, 1, HEIGHT, WIDTH),
	isitclosed(closed)
{
	
	mPosition = position + sf::Vector2f(32, 0);
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = BRIDGE;	
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));

}

Bridge::~Bridge()
{

}

void Bridge::Activate()
{
	mBaseKind = OBJECT;
}

void Bridge::DisActivate()
{
	mBaseKind = BLOCK;
}

void Bridge::update(EntityKind &currentEntity)
{

}

void Bridge::render()
{
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&mAnimation.getSprite());
}