#include "EntityManager.h"
#include "Entity.h"
#include "Character.h"
#include <cmath>
#include "Character.h"
#include "Door.h"
#include <algorithm>
#include "ImageManager.h"
#include <iostream>

EntityManager* EntityManager::sInstance = 0;

EntityManager::EntityManager():
	mPrimaryCharacter(Entity::SHEEKA),
	mPlayerLife(3)	
	{
		mLifeTexture.loadFromImage(*ImageManager::getImage("heart.png"));
		mLifeSprite.setTexture(mLifeTexture);

		frameTexture.loadFromFile("frame.png");
		frame.setTexture(frameTexture);
		
		mPortraitSprite[0] = Animation("Fenrir Face sprite 1_1.png", 60, 1, 64, 64);
		mPortraitSprite[1] = Animation("Fenrir Face sprite 1_1.png", 60, 1, 64, 64);
		mPortraitSprite[2] = Animation("Fenrir Face sprite 1_1.png", 60, 1, 64, 64);
		mPortraitSprite[3] = Animation("Fenrir Face sprite 1_1.png", 60, 1, 64, 64);
	}


EntityManager::~EntityManager()
{
	for(EntityVector::size_type j = 0; j < mEntities.size(); ++j)
	{
		delete mEntities[j];
	}
}

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
	interact();
	killEntity();
	lifePosition();
	updatePlayerLife();
	updatePlayerPortrait();
}

// uppdaterar lifeposition
void EntityManager::lifePosition()
{
	mLifeSprite.setPosition(mView->getCenter() - sf::Vector2f(512, 360));
}

// uppdaterar hur mycket liv spelaren har
void EntityManager::updatePlayerLife()
{
	for(CharacterVector::size_type i = 0; i < mCharacters.size(); ++i)
	{
		if(mCharacters[i]->getIsHit())
		{
			mCharacters[i]->setIsHitToFalse();
			mPlayerLife--;
		}
	}
}

// uppdaterar Portraiten spelaren har
void EntityManager::updatePlayerPortrait()
{
	mPortraitSprite[0].update(0);
	mPortraitSprite[1].update(0);
	mPortraitSprite[2].update(0);
	mPortraitSprite[3].update(0);
}

// ritarut alla objekt
void EntityManager::render()
{
	for(EntityVector::size_type i = 0; i < mEntities.size(); ++i)
	{
		mEntities[i]->render();
	}
	renderLife();
	renderPortrait();
}

// renderar livet
void EntityManager::renderLife()
{
	for(int i = 0; i < mPlayerLife; ++i)
	{
		ImageManager::render(&mLifeSprite);
		mLifeSprite.setPosition(mLifeSprite.getPosition() + sf::Vector2f(50, 0));
	}
}

// renderar portraitet
void EntityManager::renderPortrait()
{

	for(int i = 0; i < 4; i++)
	{
		frame.setPosition(				mView->getCenter() - sf::Vector2f(512 - i * frameTexture.getSize().x, 360));
		mPortraitSprite[i].setPosition(	mView->getCenter() - sf::Vector2f(503 - i * frameTexture.getSize().x, 351));
		
		for(CharacterVector::size_type j = 0; j < mCharacters.size(); j++)
		{
			if (mCharacters[j]->getEntityKind() == Entity::KIBA && i == 0)
			{
				ImageManager::render(&mPortraitSprite[0].getSprite());
				ImageManager::render(&frame);
			}

			else if (mCharacters[j]->getEntityKind() == Entity::CHARLOTTE && i == 1)
			{
				ImageManager::render(&mPortraitSprite[1].getSprite());
				ImageManager::render(&frame);
			}

			else if (mCharacters[j]->getEntityKind() == Entity::FENRIR && i == 2)
			{
				ImageManager::render(&mPortraitSprite[2].getSprite());
				ImageManager::render(&frame);
			}

			else if (mCharacters[j]->getEntityKind() == Entity::SHEEKA && i == 3)
			{
				ImageManager::render(&mPortraitSprite[3].getSprite());
				ImageManager::render(&frame);
			}
		}
	}
	
}

// lägger till en entiteter i de vectorer de ska va i.
void EntityManager::addEntity(Entity *e)
{
	mEntities.push_back(e);

	switch(e->getEntityKind())
	{
	case Entity::ARROW:
	case Entity::SHIELD:
	case Entity::DARKBINDING:
	case Entity::STONE:
	case Entity::SPIKETRAP:
	case Entity::SLASH:
		mDynamicEntities.push_back(e);
		break;
	}

	if(e->getBaseKind() == Entity::CHARACTER)
	{
		mDynamicEntities.push_back(e);
		mCharacters.push_back(static_cast<Character*>(e));
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

// tar bort entiterter som är döda i både entityvectorn och dynamicentityvektorn
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

// uppdaterar vilken som är den primära karaktären
void EntityManager::updatePrimaryCharacter()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		mPrimaryCharacter = Entity::KIBA;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		mPrimaryCharacter = Entity::CHARLOTTE;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		mPrimaryCharacter = Entity::FENRIR;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		mPrimaryCharacter = Entity::SHEEKA;
	}
}

// returnerar possitione till den primära karaktären
sf::Vector2f EntityManager::getCharacterPos()const
{
	for(CharacterVector::size_type i = 0; i < mCharacters.size(); ++i)
	{
		if(mCharacters[i]->getEntityKind() == mPrimaryCharacter)
		{
			return mCharacters[i]->getPosition();
		}
	}
}

void EntityManager::interact()
{
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

// sätter viewn
void EntityManager::setView(sf::View* view)
{
	mView = view;
}

sf::View* EntityManager::getView()
{
	return mView;
}