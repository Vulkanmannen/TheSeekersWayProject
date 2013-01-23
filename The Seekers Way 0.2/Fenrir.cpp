#include "Fenrir.h"
#include "Animation.h"

const static float HEIGHT = 128;
const static float WIDTH = 64;

Fenrir::Fenrir(sf::Vector2f &position)
	{
		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = KIBA;
		mPosition = position;
		mAnimation = Animation("fenrirspring.png", 10, 7, 128, 128);
		mAnimation.setPosition(position);
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
