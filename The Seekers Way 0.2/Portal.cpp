#include "Portal.h"
#include "ImageManager.h"

static const float WIDTH = 64;
static const float HEIGHT = 128;

Portal::Portal(sf::Vector2f position1, sf::Vector2f position2):
	mAnimation("Door1.png", 60, 1, 128, 64)
{
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = PORTAL;
	mPosition = position1 + sf::Vector2f(WIDTH/2 - 32, HEIGHT/2 - 32);
	Portal *iportal = new Portal(position2, this);
	mPortal = iportal;
	EntityManager::getInstance()->addEntity(this);
}

Portal::Portal(sf::Vector2f position, Portal *p):
	mAnimation("Door1.png", 60, 1, 128, 64)
{
	mPosition = position + sf::Vector2f(WIDTH/2 - 32, HEIGHT/2 - 32);
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = PORTAL;
	EntityManager::getInstance()->addEntity(this);
	mPortal = p;
}

Portal::~Portal()
{
	
}

void Portal::update(EntityKind &currentEntity)
{

}

void Portal::render()
{
	mAnimation.update(0);
	mAnimation.setPosition(sf::Vector2f(mPosition.x - mWidth / 2, mPosition.y - mHeight / 2));
	ImageManager::render(&mAnimation.getSprite());
}

void Portal::interact(Entity* e)
{

}

sf::Vector2f Portal::getDestination()
{
	return mPortal->getPosition();
}