#include "Kiba.h"
#include "Animation.h"

const static float HEIGHT = 128;
const static float WIDTH = 64;

Kiba::Kiba(sf::Vector2f &position)
	{
		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = KIBA;
		mPosition = position;
	}


Kiba::~Kiba()
	{}

void Kiba::update()
{
	walk();
	jump();
}

sf::Sprite Kiba::getSprite()
{
	mAnimation.update(0);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - 64, mPosition.y -96));
	return mAnimation.getSprite();
}

