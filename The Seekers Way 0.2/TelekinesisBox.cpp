#include "TelekinesisBox.h"
#include "ImageManager.h"
#include "NormalBlock.h"
#include "SFML\Graphics.hpp"


static const float WIDTH = 448;
static const float HEIGHT = 448;

TelekinesisBox::TelekinesisBox(sf::Vector2f &position):
	mCurrentStone(0),
	mCanPressChange(true),
	mCanPressClear(true)
{
	mPosition = position;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = TELEKINESISBOX;
}


TelekinesisBox::~TelekinesisBox()
{
}

void TelekinesisBox::update(EntityKind &currentEntity)
{

}

void TelekinesisBox::render()
{

}

// lägger till en sten i vektorn om den inte redan finns
void TelekinesisBox::interact(Entity* e)
{
	if(*e == STONE)
	{
		for(auto i = mStones.begin(); i < mStones.end(); ++i)
		{
			if(*i == e)
			{
				return;
			}
		}

		mStones.push_back(static_cast<Stone*>(e));
	}
}

// returnerar nuvarande sten, eller NULL om vektorn e tom
Stone* TelekinesisBox::getCurrentStone()
{
	if(mCurrentStone < mStones.size())
	{
		return mStones[mCurrentStone];
	}
	else
	{
		return NULL;
	}
}

// byter nuvarande sten
void TelekinesisBox::changeCurrenStone()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mCanPressChange) // tar in knapptryck och ändrar currentstone
	{
		mCurrentStone++;
		mCanPressChange = false;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mCanPressChange)// tar in knapptryck och ändrar currentstone
	{
		mCurrentStone--;
		mCanPressChange = false;
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mCanPressChange = true;
	}

	if(mCurrentStone >= static_cast<int>(mStones.size())) // ser till att mCurentStone inte blir för hög eller låg
	{
		mCurrentStone = 0;
	}
	else if(mCurrentStone < 0)
	{
		mCurrentStone = static_cast<int>(mStones.size() - 1);
	}
}

int TelekinesisBox::getNumberOfStones()const
{
	return static_cast<int>(mStones.size());
}

void TelekinesisBox::clear()
{
	mStones.clear();
	mCurrentStone = 0;
}
