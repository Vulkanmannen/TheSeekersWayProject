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
	stone.clear();
}

void TelekinesisBox::render()
{

}

void TelekinesisBox::interact(Entity* e)
{
	e->getEntityKind() == STONE ? stone.push_back(static_cast<Stone*>(e)) : NULL;
}

Stone* TelekinesisBox::getStone(int a)
{
	b += a;
	stone.size() > b ? NULL : b = 0;
	return stone[b];
}