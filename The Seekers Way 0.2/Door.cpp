#include "Door.h"
#include "ImageManager.h"
#include "Sounds.h"
#include <cmath>

static const float WIDTH = 32;
static const float HEIGHT = 128;

static const float SPRITEWIDTH = 64;
static const float SPRITEHEIGHT = 128;

Door::Door(sf::Vector2f &position, std::string &texture):
	mAnimation(texture, 30, 11, SPRITEHEIGHT, SPRITEWIDTH),
	mStatus(CLOSED)
{
	mPosition = position + sf::Vector2f(0,32);
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = DOOR;	
	mAnimation.setPosition(sf::Vector2f(mPosition.x - SPRITEWIDTH/ 2, mPosition.y - SPRITEHEIGHT/ 2));
}

Door::~Door()
{

}

void Door::Activate()
{
	if(mBaseKind == BLOCK)
	{
		Sounds::getInstance()->Play("door.wav");
	}

	if(mStatus != OPEN)
	{
		if(mStatus != OPENING)
		{
			mAnimation.setAnimationToBegining();
		}
		mStatus = OPENING;
	}
	mBaseKind = OBJECT;
}

void Door::DisActivate()
{
	if(mStatus != CLOSED)
	{
		if(mStatus != CLOSING)
		{
			mAnimation.setAnimationToBegining();
		}
		mStatus = CLOSING;
	}
	mBaseKind = BLOCK;
}

void Door::update(EntityKind &currentEntity)
{
	if(mStatus == OPENING && mAnimation.getEndOfAnimation())
	{
		mStatus = OPEN;
	}

	if(mStatus == CLOSING && mAnimation.getEndOfAnimation())
	{
 		mStatus = CLOSED;
	}
}

void Door::render()
{
	mAnimation.update(mStatus);
	ImageManager::render(&mAnimation.getSprite());
}

void Door::interact(Entity* e)
{
	if((*e) == CHARACTER && mBaseKind == BLOCK)
	{
		// räknar ut objektens radier och lägger ihop dem
		float xRadius = mWidth / 2 + e->getWidth() / 2;

		// beräknar differansen mellan två objekt
		float xDif = e->getPosition().x - mPosition.x;

		if(std::abs(xDif) > xRadius - 10)
		{
			if(xDif > 0)
			{
				e->setPosition(sf::Vector2f(mPosition.x + xRadius - 0, e->getPosition().y));
			}
			else
			{
				e->setPosition(sf::Vector2f(mPosition.x - (xRadius - 0), e->getPosition().y));
			}
		}
		else
		{
			if(xDif > 0)
			{
				e->setPosition(e->getPosition() + sf::Vector2f(10, 0));
			}
			else
			{
				e->setPosition(e->getPosition() - sf::Vector2f(10, 0));
			}
		}
	}
}