#include "Kiba.h"

sf::Texture Kiba::sTexture;

const static float HEIGHT = 128;
const static float WIDTH = 64;

Kiba::Kiba(sf::Vector2f &position)
	{
		mAlive = true;
		mPosition = position;
		mHeight = HEIGHT;
		mWidth = WIDTH;
		mEntityKind = KIBA;
		mBaseKind = CHARACTER;

		mTexture.loadFromFile("Block.png");
		mSprite.setTexture(mTexture);
		mSprite.setPosition(position);
		mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	}


Kiba::~Kiba()
	{}

void Kiba::update()
{

}

void Kiba::render()
{

}

