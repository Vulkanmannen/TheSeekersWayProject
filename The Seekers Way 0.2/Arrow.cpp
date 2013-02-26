#include "Arrow.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 12;

Arrow::Arrow(sf::Vector2f &position, bool dirleft):
	mDirLeft(dirleft),
	mMovementSpeed(10*((0.5-dirleft)*2),0)
{
	mEntityKind = ARROW;
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = Entity::ARROW;
	mPosition = position;
	
	mTexture.loadFromImage(*ImageManager::getImage("arrow.png"));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(position);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.scale((-(0.5-dirleft)*2),1);
}

Arrow::~Arrow()
{

}

void Arrow::update(EntityKind &currentEntity)
{	
	mPosition	+= mMovementSpeed;
	mSprite.setPosition(mPosition);
}

void Arrow::interact(Entity* e)
{
	if(mShottingTime.getElapsedTime().asMilliseconds() > 150 || (*e) != Entity::BLOCK)
	{
		if((*e) == Entity::BLOCK || (*e) == Entity::CHARACTER || (*e) == Entity::SHIELD || (*e) == Entity::STONE)
		{
			if(e->getEntityKind() != FENRIR)
			{
				destroy();
			}
		}
	}
}