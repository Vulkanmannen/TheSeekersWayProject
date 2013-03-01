#include "TelekinesisBox.h"
#include "ImageManager.h"
#include "NormalBlock.h"
#include "SFML\Graphics.hpp"


static const float WIDTH = 448;
static const float HEIGHT = 448;

TelekinesisBox::TelekinesisBox(sf::Vector2f &position, Stone* noStone):
	mSelectedStone(0),
	mNoStone(noStone),
	mCanPressChange(true)
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
	//sf::RectangleShape rect(sf::Vector2f(mWidth, mHeight));
	//rect.setPosition(mPosition);
	//rect.setOrigin(mWidth/2, mHeight/2);
	//sf::Color colo(255,255,255,128);
	//rect.setFillColor(colo);
	//ImageManager::render(&rect);
}

void TelekinesisBox::interact(Entity* e)
{
	if(e->getEntityKind() == STONE)
	{
		for(std::vector<Stone*>::size_type i = 0; i < stone.size(); ++i)
		{
			if(e == stone[i])
			{
				return;
			}
		}
		stone.push_back(static_cast<Stone*>(e)); 
	}
}

Stone* TelekinesisBox::getStone()
{
	if(mSelectedStone < static_cast<int>(stone.size()))
	{
		return stone[mSelectedStone];	
	}
	else
	{
		return NULL;
	}
}

void TelekinesisBox::clearStoneVector()
{
	stone.clear();
	mSelectedStone = 0;
}

TelekinesisBox::StoneVector TelekinesisBox::getStoneVector()const
{
	return stone;
}

void TelekinesisBox::changeStone()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mCanPressChange)
	{
		mSelectedStone++;
		mCanPressChange = false;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mCanPressChange)
	{
		mSelectedStone--;
		mCanPressChange = false;
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mCanPressChange = true;
	}

	if(mSelectedStone >= static_cast<int>(stone.size()))
	{
		mSelectedStone = 0;
	}
	else if(mSelectedStone < 0)
	{
		mSelectedStone = static_cast<int>(stone.size()) - 1;
	}

}