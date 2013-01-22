#include "NormalBlock.h"
#include "ImageManager.h"
#include "EntityManager.h"

//sf::Texture NormalBlock::sTexture;

static const float WIDTH = 64;
static const float HEIGHT = 64;

NormalBlock::NormalBlock(sf::Vector2f Position)
{
	mPosition = Position;
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = NORMALBLOCK;

	mTexture.loadFromFile("Block.png");
	mSprite.setTexture(mTexture);
	mSprite.setPosition(Position);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.scale(-1,1);
	mSprite.scale(1,1);
}

NormalBlock::~NormalBlock()
{

}

void NormalBlock::update()
{

}
