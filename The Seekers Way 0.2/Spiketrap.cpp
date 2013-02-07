#include "Spiketrap.h"
#include "ImageManager.h"

static const float HEIGHT = 128;
static const float WIDTH = 64;

Spiketrap::Spiketrap(sf::Vector2f &position):
	mAnimation("Door1.png", 60, 1, HEIGHT, WIDTH),
	mSpikeAcc(2),
	mSpikeStatus(START)
{
	mPosition = position;
	mMaxSpikeHeight = position.y - 96;
	mMinSpikeHeight = position.y - 32;
	mWidth = WIDTH;
	mHeight = HEIGHT;
	mEntityKind = SPIKETRAP;
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
}


Spiketrap::~Spiketrap()
{
	
}

void Spiketrap::update(EntityKind &currentEntity)
{
	SpikeMove();
}

void Spiketrap::render()
{
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&mAnimation.getSprite());
}

void Spiketrap::SpikeMove()
{
	if(mSpikeStatus == START && mClock.getElapsedTime().asSeconds() > 2 && mPosition.y != mMaxSpikeHeight)
	{
		mPosition.y -= mSpikeAcc;
		if(mPosition.y == mMaxSpikeHeight)
		{
			mSpikeStatus = DOWN;
			mClock.restart();
		}
	}
	if(mSpikeStatus == DOWN && mClock.getElapsedTime().asSeconds() > 2)
	{
		mPosition.y += mSpikeAcc;
		if(mPosition.y == mMinSpikeHeight)
		{
			mSpikeStatus = START;
			mClock.restart();
		}
	}
}