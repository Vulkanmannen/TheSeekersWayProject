#include "NormalBlock.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 64;

NormalBlock::NormalBlock(sf::Vector2f Position, unsigned char spriteNumber)
{
	mPosition = Position;
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = NORMALBLOCK;

	mTexture.loadFromImage(*ImageManager::getImage("Block.png"));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(Position);
	mSprite.setOrigin(32/* + spriteNumber * 64*/, mSprite.getLocalBounds().height / 2);

	sf::IntRect textureRect(spriteNumber * 64, 0, mWidth, mHeight);
	mSprite.setTextureRect(textureRect);
}

NormalBlock::~NormalBlock()
{

}

void NormalBlock::update(EntityKind &currentEntity)
{

}
