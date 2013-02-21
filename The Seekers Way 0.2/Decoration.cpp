#include "Decoration.h"
#include "ImageManager.h"


Decoration::Decoration(sf::Vector2f Position, unsigned char spriteNumber, bool bigDecoration)
	{
		mPosition = Position;
		mAlive = true;
		mEntityKind = DECORATION;
		mLayer = MIDDLE;

		if(bigDecoration)
		{
			mHeight = 128;
			mWidth = 128;
			mTexture.loadFromImage(*ImageManager::getImage("decoration128.png"));
			if(spriteNumber == 4)
			{
				mLayer = FORGROUND;
			}
		}
		else
		{
			mHeight = 64;
			mWidth = 64;
			mTexture.loadFromImage(*ImageManager::getImage("decoration64.png"));
		}

		mSprite.setTexture(mTexture);
		mSprite.setPosition(Position - sf::Vector2f(32, 32));			
		
		sf::IntRect textureRect(spriteNumber * mWidth, 0, mWidth, mHeight);
		mSprite.setTextureRect(textureRect);
	}


Decoration::~Decoration()
	{}

void Decoration::update(EntityKind &currentEntity)
{

}
