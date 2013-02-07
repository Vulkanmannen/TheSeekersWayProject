#include "TelekinesisBox.h"
#include "ImageManager.h"
#include "NormalBlock.h"


static const float WIDTH = 384;
static const float HEIGHT = 320;

TelekinesisBox::TelekinesisBox(sf::Vector2f &position):
	b(0)
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
	//stone.clear();
}

void TelekinesisBox::render()
{
	sf::RectangleShape rect(sf::Vector2f(mWidth, mHeight));
	rect.setPosition(mPosition);
	rect.setOrigin(mWidth/2, mHeight/2);

	ImageManager::render(&rect);
}

void TelekinesisBox::interact(Entity* e)
{
	if(e->getEntityKind() == STONE)
	{
		stone.push_back(static_cast<Stone*>(e)); 
	}
}

Stone* TelekinesisBox::getStone(int a)
{
	b += a;

	if(stone.size() <= b || b < 0)
	{
		b = 0;
	}

	if(stone.size() != 0)
	{
		return stone[b];
	}
}