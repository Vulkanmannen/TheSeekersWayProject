#include "Portal.h"
#include "ImageManager.h"

static const float WIDTH = 100;
static const float HEIGHT = 5;

static const float SPRITEWIDTH = 128;
static const float SPRITEHEIGHT = 128;

Portal::Portal(sf::Vector2f position1, sf::Vector2f position2):
	mAnimation("portal.png", 80, 4, 128, 128)
{
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = PORTAL;
	mPosition = position1 + sf::Vector2f(0, 29);
	Portal *iportal = new Portal(position2, this);
	mPortal = iportal;

	mAnimation.setPosition(sf::Vector2f(position1.x - 32, position1.y - 96));
}

Portal::Portal(sf::Vector2f position, Portal *p):
	mAnimation("portal.png", 80, 4, 128, 128)
{
	mPosition = position + sf::Vector2f(0, 29);
	mAlive = true;
	mHeight = HEIGHT;
	mWidth = WIDTH;
	mEntityKind = PORTAL;
	EntityManager::getInstance()->addEntity(this);
	mPortal = p;

	mAnimation.setPosition(sf::Vector2f(position.x - 32, position.y - 96));
}

Portal::~Portal()
{
	
}

void Portal::update(EntityKind &currentEntity)
{
	mAnimation.update(0);
}

void Portal::render()
{
	ImageManager::render(&mAnimation.getSprite());
}

void Portal::interact(Entity* e)
{

}

sf::Vector2f Portal::getDestination()
{
	return mPortal->getPosition();
}