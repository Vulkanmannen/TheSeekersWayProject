#include "EntityManager.h"
#include "Entity.h"
#include "Character.h"
#include <cmath>
#include "Character.h"
#include "Door.h"
#include <algorithm>


EntityManager* EntityManager::sInstance = 0;

EntityManager::EntityManager():
	mPrimaryCharacter(Entity::SHEEKA)
	{}


EntityManager::~EntityManager()
	{}

// returnerar den enda instancen av managern
EntityManager* EntityManager::getInstance()
{
	if(sInstance == 0)
	{
		sInstance = new EntityManager;
	}
	return sInstance;
}


// uppdaterar alla objekt
void EntityManager::update()
{
	for(EntityVector::size_type i = 0; i < mEntities.size(); ++i)
	{
		mEntities[i]->update(mPrimaryCharacter);
	}

	killEntity();
	interact();
}

// ritarut alla objekt
void EntityManager::render()
{
	for(EntityVector::size_type i = 0; i < mEntities.size(); ++i)
	{
		mEntities[i]->render();
	}
}

// lägger till en entiteter i de vectorer de ska va i.
void EntityManager::addEntity(Entity *e)
{
	mEntities.push_back(e);

	switch(e->getEntityKind())
	{
	case Entity::ARROW:
		mDynamicEntities.push_back(e);
		break;
	}

	if(e->getBaseKind() == Entity::CHARACTER)
	{
		mDynamicEntities.push_back(e);
		mCharacters[e->getEntityKind()] = e;
	}
}

// kollar om en karaktär kolliderar
bool EntityManager::isColliding(Entity *c, Entity *e)
{
	if(c->getTop() > e->getBottom())
	{
		return false;
	}
	else if(c->getBottom() < e->getTop())
	{
		return false;
	}
	else if(c->getRight() < e->getLeft())
	{
		return false;
	}
	else if(c->getLeft() > e->getRight())
	{
		return false;
	}
	else
	{
		return true;
	}
}


void EntityManager::killEntity()
{
	for(EntityVector::size_type j = 0; j < mEntities.size(); ++j)
	{
		if(mEntities[j]->getAliveStatus() == false)
		{
			for(EntityVector::size_type i = 0; i < mDynamicEntities.size(); ++i)
			{
				if(mDynamicEntities[i] == mEntities[j])
				{
					mDynamicEntities[i] = mDynamicEntities.back();
					mDynamicEntities.pop_back();
				}
			}
			delete mEntities[j];
			mEntities[j] = mEntities.back();
			mEntities.pop_back();
		}
	}
}

void EntityManager::updatePrimaryCharacter()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		mPrimaryCharacter = Entity::SHEEKA;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		mPrimaryCharacter = Entity::FENRIR;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		mPrimaryCharacter = Entity::CHARLOTTE;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		mPrimaryCharacter = Entity::KIBA;
	}
}

sf::Vector2f EntityManager::getCharacterPos()const
{
	return mCharacters[mPrimaryCharacter]->getPosition();
}

void EntityManager::interact()
{
	//samlar alla saker i en lista
	EntityVector temp;
	for(int i = 0; i < sizeof(mCharacters) / sizeof(mCharacters[0]); i++)
	{
		temp.push_back(mCharacters[i]);
	}
	temp.insert(temp.end(), mEntities.begin(), mEntities.end());
	
	//kör interact mot alla som krockar
	for(EntityVector::size_type i = 0; i < mDynamicEntities.size(); ++i)
	{
		for(EntityVector::size_type j = 0; j < mEntities.size(); ++j)
		{
			if(mDynamicEntities[i] != mEntities[j])
			{
				if(isColliding(mDynamicEntities[i], mEntities[j]))
				{
					mDynamicEntities[i]->interact(mEntities[j]);

					mEntities[j]->interact(mDynamicEntities[i]);
				}
			}
		}
	}
}