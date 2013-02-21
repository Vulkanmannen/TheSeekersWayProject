#include "Vine.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 64;

Vine::Vine(sf::Vector2f &position, unsigned char spriteNumber)
	{
	mPosition = position;
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = VINE;

	mTexture.loadFromImage(*ImageManager::getImage("vines.png"));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(position);
	mSprite.setOrigin(32, mSprite.getLocalBounds().height / 2);
	
	sf::IntRect textureRect(spriteNumber * 64, 0, mWidth, mHeight);
	mSprite.setTextureRect(textureRect);
	}


Vine::~Vine()
	{}

void Vine::update(EntityKind &currentEntity)
{

}