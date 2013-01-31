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

	for(int i = 0; i < sizeof(mCharacters) / sizeof(mCharacters[0]); ++i)
	{
		mCharacters[i]->update(mPrimaryCharacter);
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

	for(int i = 0; i < sizeof(mCharacters) / sizeof(mCharacters[0]); ++i)
	{
		mCharacters[i]->render();
	}
}

// l�gger till en entitet i vecktorn
void EntityManager::addEntity(Entity *e)
{
	mEntities.push_back(e);
}

// l�gger till character i charactervectorn
void EntityManager::addCharacter(Character *character, int placeInVector)
{
	mCharacters[placeInVector] = character;
}

// g�r igenom alla karakt�rer och krocktestar dem mot alla entiteter
void EntityManager::checkCollisions()
{
	for(int i = 0; i < sizeof(mCharacters) / sizeof(mCharacters[0]); ++i)
	{
		for(EntityVector::size_type j = 0; j < mEntities.size(); ++j)
		{
			if(mEntities[j]->getBaseKind() == Entity::BLOCK)
			{
				if(isColliding(static_cast<Entity*>(mCharacters[i]), mEntities[j]))
				{
					stopEntity(static_cast<Entity*>(mCharacters[i]), mEntities[j]);
				}
			}
		}
	}
	for(EntityVector::size_type i = 0; i < mEntities.size(); ++i)
	{
		for(EntityVector::size_type j = 0; j < mEntities.size(); ++j)
		{
			if(mEntities[i]->getEntityKind() == Entity::ARROW && mEntities[j]->getBaseKind() == Entity::BLOCK)
			{
				if(isColliding(mEntities[i], mEntities[j]))
				{
					stopEntity(mEntities[i], mEntities[j]);
				}
			}
		}
	}
	
}

// kollar om en karakt�r kolliderar
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


// flyttar ut objekt som kolliderat med block
void EntityManager::stopEntity(Entity *c, Entity *e)
{
	
	
	// r�knar ut objektens radier och l�gger ihop dem
	float xRadius = c->getWidth() / 2 + e->getWidth() / 2;
	float yRadius = c->getHeight() / 2 + e->getHeight() / 2;

	// ber�knar differansen mellan tv� objekt
	float xDif = c->getPosition().x - e->getPosition().x;
	float yDif = c->getPosition().y - e->getPosition().y;

	// fr�ga vilken sida carakt�ren finns p�.
	if(std::abs(xDif / xRadius) > std::abs(yDif / yRadius)) // �r karakt�ren h�ger/v�nster eller �ver/under om blocket
	{
		if(xDif > 0) // kollar om karakt�ren �r h�ger eller v�nster
		{
			if(std::abs(yDif) < yRadius - 10) // kollar s� blocket inte ligger snett under
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
		if(yDif > 0) // kollar om karakt�ren �r under eller �ver
		{
			if(std::abs(xDif) < xRadius - 10) // kollar om blocket ligger snett �ver
			{
				c->setPosition(sf::Vector2f(c->getPosition().x, e->getPosition().y + yRadius));
			}
		}
		else
		{
			if(std::abs(xDif) < xRadius - 10)
			{
				c->setPosition(sf::Vector2f(c->getPosition().x, e->getPosition().y - (yRadius)));
				if(c->getBaseKind() == Entity::CHARACTER)
				{
					dynamic_cast<Character*> (c)->onblock();
				}
				if(c->getBaseKind() == Entity::CHARACTER && (e->getEntityKind() == Entity::BUTTON || e->getEntityKind()==Entity::LEVER))
				{
					dynamic_cast<Block*> (e)->Activate();
				}

			}
		}
	}
	
}

void EntityManager::killEntity()
{
	for(int i = 0; i < sizeof(mCharacters) / sizeof(mCharacters[0]); ++i)
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
}

sf::Vector2f EntityManager::getCharacterPos()const
{
	return mCharacters[mPrimaryCharacter]->getPosition();
}

void EntityManager::interact()
{
	//samlar alla saker i en lista
	EntityVector temp;
	for(CharacterVector::size_type i = 0; i < sizeof(mCharacters) / sizeof(mCharacters[0]); i++)
	{
		temp.push_back(static_cast<Entity*>(mCharacters[i]));
	}
	temp.insert(temp.end(), mEntities.begin(), mEntities.end());
	
	for(EntityVector::size_type i = 0; i < mEntities.size(); ++i)
	{
		for(EntityVector::size_type j = i+1; j < mEntities.size(); ++j)
		{
			
			temp[i]->interact(temp[j]);
			temp[j]->interact(temp[i]);

		}
	}
}