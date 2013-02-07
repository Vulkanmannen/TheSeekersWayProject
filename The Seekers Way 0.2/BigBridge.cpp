#include "BigBridge.h"
#include "ImageManager.h"

static const float WIDTH = 320;
static const float HEIGHT = 64;

BigBridge::BigBridge(sf::Vector2f &position, bool closed):
	mAnimation("Door2.png", 60, 1, HEIGHT, WIDTH),
	isitclosed(closed)
{
	isitclosed? mBaseKind = BLOCK : mBaseKind = OBJECT; 
	mPosition = position + sf::Vector2f(WIDTH/2 - 32, 0);
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = BIGBRIDGE;	
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));

}

BigBridge::~BigBridge()
{

}

void BigBridge::Activate()
{
	!isitclosed? mBaseKind = BLOCK : mBaseKind = OBJECT; 
}

void BigBridge::DisActivate()
{
	isitclosed? mBaseKind = BLOCK : mBaseKind = OBJECT; 
}

void BigBridge::update(EntityKind &currentEntity)
{

}

void BigBridge::render()
{
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&mAnimation.getSprite());
}