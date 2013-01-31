#include "EntityManager.h"
#include "Entity.h"
#include "Character.h"
#include <cmath>
#include "Character.h"
#include "Door.h"


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
		mEntities[i]->update();
	}

	mCharacters[mPrimaryCharacter]->update();

	for(CharacterVector::size_type i = 0; i < mCharacters.size(); ++i)
	{
		Character::characterUpdate(mCharacters[i], mPrimaryCharacter);
	}

	killEntity();
	checkCollisions();
}

// ritarut alla objekt
void EntityManager::render()
{
	for(EntityVector::size_type i = 0; i < mEntities.size(); ++i)
	{
		mEntities[i]->render();
	}

	for(CharacterVector::size_type i = 0; i < mCharacters.size(); ++i)
	{
		mCharacters[i]->render();
	}
}

// lägger till en entitet i vecktorn
void EntityManager::addEntity(Entity *e)
{
	mEntities.push_back(e);
}

// lägger till character i charactervectorn
void EntityManager::addCharacter(Character *c)
{
	mCharacters.push_back(c);
}

// går igenom alla karaktärer och krocktestar dem mot alla entiteter
void EntityManager::checkCollisions()
{
	for(CharacterVector::size_type i = 0; i < mCharacters.size(); ++i)
	{
		for(EntityVector::size_type j = 0; j < mEntities.size(); ++j)
		{
			if(mEntities[j]->getBaseKind() == Entity::BLOCK)
			{
				if(isColliding(mCharacters[i], mEntities[j]))
				{
					stopEntity(mCharacters[i], mEntities[j]);
				}
			}
		}
	}
}

// kollar om en karaktär kolliderar
bool EntityManager::isColliding(Character *c, Entity *e)
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


// flyttar ut objekt som kolliderat med block
void EntityManager::stopEntity(Character *c, Entity *e)
{
	// räknar ut objektens radier och lägger ihop dem
	float xRadius = c->getWidth() / 2 + e->getWidth() / 2;
	float yRadius = c->getHeight() / 2 + e->getHeight() / 2;

	// beräknar differansen mellan två objekt
	float xDif = c->getPosition().x - e->getPosition().x;
	float yDif = c->getPosition().y - e->getPosition().y;

	// fråga vilken sida caraktären finns på.
	if(std::abs(xDif / xRadius) > std::abs(yDif / yRadius)) // är karaktären höger/vänster eller över/under om blocket
	{
		if(xDif > 0) // kollar om karaktären är höger eller vänster
		{
			if(std::abs(yDif) < yRadius - 10) // kollar så blocket inte ligger snett under
			{
				c->setPosition(sf::Vector2f(e->getPosition().x + xRadius - 3, c->getPosition().y));
			}
		}
		else
		{
			if(std::abs(yDif) < yRadius - 10)
			{
				c->setPosition(sf::Vector2f(e->getPosition().x - (xRadius - 3), c->getPosition().y));
			}
		}
	}
	else
	{
		if(yDif > 0) // kollar om karaktären är under eller över
		{
			if(std::abs(xDif) < xRadius - 10) // kollar om blocket ligger snett över
			{
				c->setPosition(sf::Vector2f(c->getPosition().x, e->getPosition().y + yRadius));
			}
		}
		else
		{
			if(std::abs(xDif) < xRadius - 10)
			{
				c->setPosition(sf::Vector2f(c->getPosition().x, e->getPosition().y - (yRadius)));
				c->onblock();
				if(e->getEntityKind()==Entity::BUTTON || e->getEntityKind()==Entity::LEVER)
				{
					Block * tempblock;
					tempblock = dynamic_cast<Block*> (e);
					tempblock->Activate();
				}
			}

		}
	}
}

void EntityManager::killEntity()
{
	for(CharacterVector::size_type i = 0; i < mCharacters.size(); ++i)
	{
		if(mCharacters[i]->getAliveStatus() == false)
		{
			
		}
	}
	for(EntityVector::size_type j = 0; j < mEntities.size(); ++j)
	{
		if(mEntities[j]->getAliveStatus() == false)
		{
			delete mEntities[j];
			mEntities[j] = mEntities.back();
			mEntities.pop_back();
		}
	}
}

void EntityManager::primaryCharacter()
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
}

sf::Vector2f EntityManager::getCharacterPos()const
{
	for(CharacterVector::size_type i = 0; i < mCharacters.size(); ++i)
	{
		return mCharacters[mPrimaryCharacter]->getPosition();
	}
}