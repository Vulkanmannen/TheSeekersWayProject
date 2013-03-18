#include "Decoration.h"
#include "ImageManager.h"
#include "EntityManager.h"


Decoration::Decoration(sf::Vector2f Position, unsigned char spriteNumber, bool bigDecoration, bool paralaxing, bool biggerDecoration):
	mParalaxing(paralaxing)
	{
		mAlive = true;
		mEntityKind = DECORATION;
		mLayer = MIDDLE;

		if(bigDecoration)
		{
			mHeight = 128;
			mWidth = 128;
			
			if(paralaxing)
			{
				mTexture.loadFromImage(*ImageManager::getImage("decoration128parallaxing.png"));
				mLayer = BACKGROUND;
			}
			else
			{
				mTexture.loadFromImage(*ImageManager::getImage("decoration128.png"));
				mLayer = MIDDLE;
			}
		}
		else if(!biggerDecoration)
		{
			mHeight = 64;
			mWidth = 64;
			if(paralaxing)
			{
				mTexture.loadFromImage(*ImageManager::getImage("decoration64parallaxing.png"));
				mLayer = BACKGROUND;
			}
			else
			{
				mTexture.loadFromImage(*ImageManager::getImage("decoration64.png"));
				mLayer = MIDDLE;
			}
		}
		else if(biggerDecoration)
		{
			mHeight = 192;
			mWidth = 192;

			mTexture.loadFromImage(*ImageManager::getImage("FinishDoor.png"));
			mLayer = MIDDLE;
		}
		mPositionToBackground = Position - sf::Vector2f(32, 32);
		mPosition = EntityManager::getInstance()->getBackgroundPos() + sf::Vector2f(1024, 1024) + mPositionToBackground; 
		mSprite.setTexture(mTexture);
		mSprite.setPosition(mPosition);			
		
		sf::IntRect textureRect(spriteNumber * mWidth, 0, mWidth, mHeight);
		mSprite.setTextureRect(textureRect);
	}


Decoration::~Decoration()
	{}

void Decoration::update(EntityKind &currentEntity)
{
	if(mParalaxing)
	{
		mPosition = EntityManager::getInstance()->getBackgroundPos() + sf::Vector2f(1024, 1024) + mPositionToBackground;
		mSprite.setPosition(mPosition);
	}
}
