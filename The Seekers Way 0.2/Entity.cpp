#include "Entity.h"
#include "ImageManager.h"


Entity::Entity():
	mAlive(true)
	{}


Entity::~Entity()
	{}

// renderar 
void Entity::render()
{
	ImageManager::render(&mSprite);
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

// tv� funktioner som retunerar h�jd o br�dd
float Entity::getHeight()const
{
	return mHeight;
}

float Entity::getWidth()const
{
	return mWidth;
}

// ber�ttar om karakt�ren e d�d eller levande
bool Entity::getAliveStatus()const
{
	return mAlive;
}

// f�rst�r karakt�ren
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
// best�mer karakt�rens position
void Entity::setPosition(sf::Vector2f &v)
{
	mPosition = v;
}

// g�mf�r en entity med en entitykind, e de lika
bool Entity::operator==(EntityKind entityKind)
{
	return mEntityKind == entityKind;
}

// g�mf�r en entity med en entitykind, e de olika
bool Entity::operator!=(EntityKind entityKind)
{
	return mEntityKind != entityKind;
}
// g�mf�r en entity med en baseKind, e de lika
bool Entity::operator==(BaseKind baseKind)
{
	return mBaseKind == baseKind;
}

// g�mf�r en entity med en baseKind, e de olika
bool Entity::operator!=(BaseKind baseKind)
{
	return mBaseKind != baseKind;
}

// returnerar lagret
Entity::Layer Entity::getLayer()const
{
	return mLayer;
}