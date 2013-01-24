#include "Door.h"

static const float WIDTH = 64;
static const float HEIGHT = 128;

Door::Door(sf::Vector2f &position)
{
	mPosition = position;
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = DOOR;

	mTexture.loadFromFile("Door.png");
	mSprite.setTexture(mTexture);
	mSprite.setPosition(position);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
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