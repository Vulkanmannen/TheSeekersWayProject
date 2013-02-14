#include "Vine.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 64;

Vine::Vine(sf::Vector2f &position)
	
	{

	mPosition = position;
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = VINE;

	mTexture.loadFromImage(*ImageManager::getImage("ShottingTrap.png"));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(position);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);

	}


Vine::~Vine()
	{}

void Vine::update(EntityKind &currentEntity)
{

}