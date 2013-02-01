#include "Lever.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 64;

Lever::Lever(sf::Vector2f &position, Block* target):
	mBlock(target),
	mAnimation("Lever.png", 60, 1, HEIGHT, WIDTH)
{
	mDrawn = false;
	mPosition = position;
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = LEVER;

	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
}

Lever::~Lever()
{

}

void Lever::Activate()
{
	if(mDrawn == false)
	{
		mBlock->Activate();
	}
	mDrawn = true;
}


void Lever::update(EntityKind &currentEntity)
{
}

void Lever::render()
{
	
	mAnimation.update(mDrawn);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - WIDTH/ 2, mPosition.y - HEIGHT/ 2));
	ImageManager::render(&getSprite());
}

sf::Sprite Lever::getSprite()
{
	return mAnimation.getSprite();
}

void Lever::interact(Entity* e)
{
	if(getPosition().y - e->getPosition().y > (e->getHeight() / 2 + mHeight / 2) - 7)
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
}