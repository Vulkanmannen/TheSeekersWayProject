#include "NormalBlock.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 64;

NormalBlock::NormalBlock(sf::Vector2f Position)
{
	mPosition = Position;
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = NORMALBLOCK;

	mTexture.loadFromImage(*ImageManager::getImage("Block.png"));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(Position);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
}

NormalBlock::~NormalBlock()
{

}

void NormalBlock::update()
{

}
