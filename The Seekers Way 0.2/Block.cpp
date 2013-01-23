#include "Block.h"

Block::Block()
{
	mBaseKind = BLOCK;
}

Block::~Block()
{

}

sf::Sprite Block::getSprite()
{
	return mSprite;
}