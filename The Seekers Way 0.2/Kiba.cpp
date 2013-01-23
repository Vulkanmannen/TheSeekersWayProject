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
		mAnimation = Animation("fenrirspring.png", 10, 7, 128, 128);
	}


Kiba::~Kiba()
	{}

void Kiba::update()
{
	move();
	walk();
	mAnimation.update(mStatus, mDirLeft);
	mSprite = mAnimation.getSprite();
}


