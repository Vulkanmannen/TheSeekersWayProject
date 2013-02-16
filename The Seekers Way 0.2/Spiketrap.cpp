#include "Spiketrap.h"
#include "ImageManager.h"

static const float HEIGHT = 128;
static const float WIDTH = 64;

Spiketrap::Spiketrap(sf::Vector2f &position):
	mAnimation("spiketrap.png", 60, 1, HEIGHT, WIDTH),
	mSpikeCount(0),
	mCountDirectionUpp(true),
	mWait(false),
	mStartYValue(position.y - 32),
	mHurting(false),
	mTimeToNextFrame(0.05),
	mTimeDown(3)
{
	mPosition = position - sf::Vector2f(0, 32);
	mWidth = WIDTH;
	mHeight = 0;
	mEntityKind = SPIKETRAP;
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - 128));
}


Spiketrap::~Spiketrap()
{
	
}

void Spiketrap::update(EntityKind &currentEntity)
{
	SpikeMove();
	spikeCount();
}

void Spiketrap::render()
{
	mAnimation.update(mSpikeCount);
	ImageManager::render(&mAnimation.getSprite());
}

void Spiketrap::spikeCount()
{


	if(mClockFrame.getElapsedTime().asSeconds() > mTimeToNextFrame && !mWait)
	{
		if(mCountDirectionUpp)
		{
			mSpikeCount++;
		}
		else if(!mCountDirectionUpp)
		{
			mSpikeCount--;
		}

		mClockFrame.restart();

		if(mSpikeCount == 0)
		{
			mWait = true;
			mClockWait.restart();
		}
	}
	
	if(mClockWait.getElapsedTime().asSeconds() > mTimeDown)
	{
		mWait = false;
	}


	if(mSpikeCount > 3)
	{
		mCountDirectionUpp = false;
	}
	else if(mSpikeCount < 1)
	{
		mCountDirectionUpp = true;		
	}
}

void Spiketrap::SpikeMove()
{
	mHeight =  mSpikeCount * 26;
	mPosition.y = mStartYValue - mSpikeCount * 13;

	if(mSpikeCount == 0)
	{
		mHurting = false;
	}
	else
	{
		mHurting = true;
	}
}

void Spiketrap::interact(Entity* e)
{

}

bool Spiketrap::getHurting()const
{
	return mHurting;
}