#include "Lever.h"
#include "ImageManager.h"
#include "Sounds.h"

static const float WIDTH = 40;
static const float HEIGHT = 15;

static const float SPRITEWIDTH = 64;
static const float SPRITEHEIGHT = 64;

Lever::Lever(sf::Vector2f &position, Block* target):
	mBlock(target),
	mAnimation("Lever.png", 120, 4, SPRITEHEIGHT, SPRITEWIDTH)
{
	mDrawn = false;
	mPosition = position + sf::Vector2f(0, 25);
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = LEVER;

	mAnimation.setPosition(sf::Vector2f(position.x - SPRITEWIDTH/ 2, position.y - SPRITEHEIGHT/ 2));
}

Lever::~Lever()
{

}

void Lever::Activate()
{
	if(mDrawn == false)
	{
		mBlock->Activate();
		Sounds::getInstance()->Play("lever.wav",30);
	}
	mDrawn = true;
}


void Lever::update(EntityKind &currentEntity)
{
}

void Lever::render()
{	
	mAnimation.update(mDrawn);
	ImageManager::render(&getSprite());
}

sf::Sprite Lever::getSprite()
{
	return mAnimation.getSprite();
}

void Lever::interact(Entity* e)
{
	switch(e->getEntityKind())
	{
	case CHARLOTTE:
	case KIBA:
	case FENRIR:
	case SHEEKA:
	case STONE:
		 Activate();
		break;
	}
}