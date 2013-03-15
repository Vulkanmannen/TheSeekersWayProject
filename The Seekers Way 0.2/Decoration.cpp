#include "Decoration.h"
#include "ImageManager.h"
#include "EntityManager.h"


Decoration::Decoration(sf::Vector2f Position, unsigned char spriteNumber, bool bigDecoration, bool paralaxing)
	{
		mPosition = Position - sf::Vector2f(32, 32);
		mAlive = true;
		mEntityKind = DECORATION;
		mLayer = MIDDLE;

		if(bigDecoration)
		{
			mHeight = 128;
			mWidth = 128;
			
			if(spriteNumber == 4)
			{
				mLayer = FORGROUND;
			}
			if(paralaxing)
			{
				mTexture.loadFromImage(*ImageManager::getImage("decoration128.png"));
			}
		}
		else
		{
			mHeight = 64;
			mWidth = 64;
			if(paralaxing)
			{
				mTexture.loadFromImage(*ImageManager::getImage("decoration64.png"));
			}
		}

		mSprite.setTexture(mTexture);
		mSprite.setPosition(EntityManager::getInstance()->getBackgroundPos() + sf::Vector2f(1024, 1024) + mPosition);			
		
		sf::IntRect textureRect(spriteNumber * mWidth, 0, mWidth, mHeight);
		mSprite.setTextureRect(textureRect);
	}


Decoration::~Decoration()
	{}

void Decoration::update(EntityKind &currentEntity)
{
	mSprite.setPosition(EntityManager::getInstance()->getBackgroundPos() + sf::Vector2f(1024, 1024) + mPosition);
}
