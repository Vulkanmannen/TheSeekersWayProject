#include "Stone.h"
#include "ImageManager.h"

static const float WIDTH = 128;
static const float HEIGHT = 128;

Stone::Stone(sf::Vector2f Position):
	mMovementSpeed(0,0),
	mGravity(5),
	mDecrease(0.6),
	mFalling(false)
{
	mPosition = Position;
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = STONE;

	mTexture.loadFromImage(*ImageManager::getImage("crashstone.png"));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(Position);
	mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
	mSprite.scale(WIDTH/mSprite.getTexture()->getSize().x,HEIGHT/mSprite.getTexture()->getSize().y);
}

Stone::~Stone()
{

}

void Stone::update(EntityKind &currentEntity)
{
	move();
	falling();
}

void Stone::move()	   
{
	mPosition	+= mMovementSpeed;
	mPosition.y	+= mGravity;
}

void Stone::falling() 
{
	if(mFalling)
	{
		mMovementSpeed.y += mDecrease;
	}
}

void Stone::interact(Entity* e)
{
	if(e->getBaseKind() == BLOCK && getPosition().y - e->getPosition().y < (e->getHeight() / 2 + mHeight / 2) - 7) 
	{
		mFalling = true;
		mMovementSpeed.y = 0;
	}
}