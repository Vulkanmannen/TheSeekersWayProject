#include "Shield.h"
#include "ImageManager.h"


static const float WIDTH = 64;
static const float HEIGHT = 128;

Shield::Shield(sf::Vector2f &position):
	mAnimation("shield.png", 60, 1, HEIGHT, WIDTH)
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

void Shield::update()
{

}

void Shield::render()
{
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&mAnimation.getSprite());
}