#include "Fenrir.h"
#include "Animation.h"

const static float HEIGHT = 64;
const static float WIDTH = 128;

Fenrir::Fenrir(sf::Vector2f &position):
	mAnimation("fenrirspring.png", 70, 7, 128, 128)
	{
		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = KIBA;
		mPosition = position;
	}


Fenrir::~Fenrir()
	{}

void Fenrir::update()
{
	move();
	walk();
	mAnimation.update(0);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y -96));
}

sf::Sprite Fenrir::getSprite()
{
	return mAnimation.getSprite();
}