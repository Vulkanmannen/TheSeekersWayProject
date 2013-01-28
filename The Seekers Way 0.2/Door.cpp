#include "Door.h"

static const float WIDTH = 64;
static const float HEIGHT = 128;

Door::Door(sf::Vector2f &position):
	mAnimation("Door1.png", 60, 1, HEIGHT, WIDTH)
{
	
	mPosition = position - sf::Vector2f(0,32);
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = DOOR;	
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));

}

Door::~Door()
{

}

void Door::open()
{
	mBaseKind = OBJECT;
}
void Door::close()
{
	mBaseKind = BLOCK;
}

void Door::Activate()
{
	open();
}

void Door::DisActivate()
{
	close();
}

void Door::update()
{

}

sf::Sprite Door::getSprite()
{
	return mAnimation.getSprite();
}