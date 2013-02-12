#include "Portal.h"

Portal::Portal(sf::Vector2f position1, sf::Vector2f position2)
{
	mEntityKind = PORTAL;
	mPosition = position1;
	Portal *iportal = new Portal(position2, this);
	mPortal = iportal;
	EntityManager::getInstance()->addEntity(this);
}

Portal::Portal(sf::Vector2f position, Portal *p)
{
	mEntityKind = PORTAL;
	mPosition = position;
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

}

void Portal::interact(Entity* e)
{

}