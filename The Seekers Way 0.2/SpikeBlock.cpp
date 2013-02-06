#include "SpikeBlock.h"
#include "ImageManager.h"
#include "EntityManager.h"
#include "Spiketrap.h"

static const float HEIGHT = 64;
static const float WIDTH = 64;

SpikeBlock::SpikeBlock(sf::Vector2f &position):
	mAnimation("Spikeblock.png", 60, 1, HEIGHT, WIDTH)
{
	mPosition = position;
	mWidth = WIDTH;
	mHeight = HEIGHT;
	mEntityKind = SPIKEBLOCK;
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	EntityManager::getInstance()->addEntity(new Spiketrap(mPosition));
}


SpikeBlock::~SpikeBlock()
{
}

void SpikeBlock::update(EntityKind &currentEntity)
{
	
}

void SpikeBlock::render()
{
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&mAnimation.getSprite());
}