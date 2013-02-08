#include "Bridge.h"
#include "ImageManager.h"

static const float WIDTH = 128;
static const float HEIGHT = 64;

Bridge::Bridge(sf::Vector2f &position, bool closed):
	mAnimation("Door2.png", 60, 1, HEIGHT, WIDTH),
	isitclosed(closed)
{
	isitclosed? mBaseKind = BLOCK : mBaseKind = OBJECT; 
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
	!isitclosed? mBaseKind = BLOCK : mBaseKind = OBJECT; 
}

void Bridge::DisActivate()
{
	isitclosed? mBaseKind = BLOCK : mBaseKind = OBJECT; 
}

void Bridge::update(EntityKind &currentEntity)
{

}

void Bridge::render()
{
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&mAnimation.getSprite());
}