#include "Door.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 128;

Door::Door(sf::Vector2f &position):
	mAnimation("Door1.png", 60, 1, HEIGHT, WIDTH)
{
	
	mPosition = position + sf::Vector2f(0,32);
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = DOOR;	
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));

}

Door::~Door()
{

}

void Door::Activate()
{
	mBaseKind = OBJECT;
}

void Door::DisActivate()
{
	mBaseKind = BLOCK;
}

void Door::update()
{

}

void Door::render()
{
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&mAnimation.getSprite());
}