#include "Entity.h"
#include "ImageManager.h"


Entity::Entity()
	{}


Entity::~Entity()
	{}

// renderar 
void Entity::render()
{
	ImageManager::render(&getSprite());
}

// funktion som returnerar positionen
sf::Vector2f Entity::getPosition()const
{
	return mPosition;
}

// fyra funktioner retunerar top bot right o left 
float Entity::getTop()const
{
	return mPosition.y - mHeight / 2;
}

float Entity::getBottom()const
{
	return mPosition.y + mHeight / 2;
}

float Entity::getRight()const
{
	return mPosition.x + mWidth / 2;
}

float Entity::getLeft()const
{
	return mPosition.x - mWidth / 2;
}

// två funktioner som retunerar höjd o brädd
float Entity::getHeight()const
{
	return mHeight;
}

float Entity::getWidth()const
{
	return mWidth;
}

// berättar om karaktären e död eller levande
bool Entity::getAliveStatus()const
{
	return mAlive;
}

// förstör karaktären
void Entity::destroy()
{
	mAlive = false;
}

// returnerar bas och entity kind
Entity::EntityKind Entity::getEntityKind()const
{
	return mEntityKind;
}

Entity::BaseKind Entity::getBaseKind()const
{
	return mBaseKind;
}
// bestämer karaktärens position
void Entity::setPosition(sf::Vector2f &v)
{
	mPosition = v;
}

