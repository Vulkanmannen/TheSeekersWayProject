#include "EntityManager.h"
#include "Entity.h"
#include "Character.h"
#include <cmath>
#include "Character.h"
#include "Door.h"
#include <algorithm>
#include "ImageManager.h"


EntityManager* EntityManager::sInstance = 0;

EntityManager::EntityManager():
	mPrimaryCharacter(Entity::SHEEKA),
	mPlayerLife(3),
	mMapHeight(1432),
	mMapWidth(3392),
	mNumberOfBackgroundsWidth(2),
	mNumberOfBackgroundsHeight(2)
	{
		mLifeTexture.loadFromImage(*ImageManager::getImage("heart.png"));
		mLifeSprite.setTexture(mLifeTexture);
		mMaskTexture.loadFromImage(*ImageManager::getImage("mask.png"));
		mMaskSprite.setTexture(mMaskTexture);
		mBackgroundTexture.loadFromImage(*ImageManager::getImage("background.png"));
		createBackground();
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
	lifeAndMaskPosition();
	updateLife();
}

// uppdaterar lifeposition
void EntityManager::lifeAndMaskPosition()
{
	mLifeSprite.setPosition(mView->getCenter() - sf::Vector2f(512, 360));
	mMaskSprite.setPosition(getCharacterPos() - sf::Vector2f(1024, 720));
}

// uppdaterar hur mycket liv spelaren har
void EntityManager::updateLife()
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

// ritarut alla objekt
void EntityManager::render()
{
	renderBackground();

	for(EntityVector::size_type i = 0; i < mEntities.size(); ++i)
	{
		mEntities[i]->render();
	}

	renderLifeAndMask();
}

// renderar livet
void EntityManager::renderLifeAndMask()
{
	ImageManager::render(&mMaskSprite);

	for(int i = 0; i < mPlayerLife; ++i)
	{
		ImageManager::render(&mLifeSprite);
		mLifeSprite.setPosition(mLifeSprite.getPosition() + sf::Vector2f(50, 0));
	}
}

// tilar bakgrunden
void EntityManager::createBackground()
{
	for(int i = 0; i < mNumberOfBackgroundsWidth; ++i)
	{
		for(int j = 0; j < mNumberOfBackgroundsHeight; ++j)
		{
			sf::Sprite background;
			background.setTexture(mBackgroundTexture);
			background.setPosition(i *1952, j * 896);
			mBackgroundSprites.push_back(background);
		}
	}
}

// renderar bakgrunden
void EntityManager::renderBackground()
{
	for(std::vector<sf::Sprite>::size_type i = 0; i < mBackgroundSprites.size(); ++i)
	{
		ImageManager::render(&mBackgroundSprites[i]);
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
	case Entity::WOODENWALL:
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
	for(EntityVector::size_type i = 0; i < mDynamicEntities.size(); ++i)
	{
		if(mDynamicEntities[i]->getAliveStatus() == false)
		{
			for(EntityVector::size_type j = 0; j < mEntities.size(); ++j)
			{
				if(mDynamicEntities[i] == mEntities[j])
				{
					mEntities[j] = mEntities.back();
					mEntities.pop_back();
				}
			}
			delete mDynamicEntities[i];
			mDynamicEntities[i] = mDynamicEntities.back();
			mDynamicEntities.pop_back();
		}	
	}
}

// uppdaterar vilken som är den primära karaktären
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
				if(mDynamicEntities[i]->getAliveStatus() && mEntities[j]->getAliveStatus())
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
}

// sätter viewn
void EntityManager::setView(sf::View* view)
{
	mView = view;
}

// updaterar view positionen
void EntityManager::updateView()
{
	sf::Vector2f playerPos = getCharacterPos();
	if(playerPos.x > 512 && playerPos.x < mMapWidth)
	{
		mView->setCenter(sf::Vector2f(playerPos.x, mView->getCenter().y));
	}
	else
	{
		if(playerPos.x > mMapWidth / 2)
		{
			mView->setCenter(sf::Vector2f(3392, mView->getCenter().y));
		}
		else
		{
			mView->setCenter(sf::Vector2f(512, mView->getCenter().y));
		}	
	}

	if(playerPos.y > 360 && playerPos.y < mMapHeight)
	{
		mView->setCenter(sf::Vector2f(mView->getCenter().x, playerPos.y));
	}
	else
	{
		if(playerPos.y > mMapHeight / 2)
		{
			mView->setCenter(sf::Vector2f(mView->getCenter().x, 1432));
		}
		else
		{
			mView->setCenter(sf::Vector2f(mView->getCenter().x, 360));
		}
	}
}

// sätter storleken på mappen tar emot fyra inter, läng o höjd räknat i block samt antalet bakgrunder i höjdled och längd;
void EntityManager::setMapSize(int numberOfBlocksWidth, int numberOfBlocksHeight, int numberOfBackgroundsWidth, int numberOfBackgroundsHeight)
{
	mMapWidth = numberOfBlocksWidth * 64;
	mMapHeight = numberOfBlocksHeight * 64;
	mNumberOfBackgroundsWidth = numberOfBackgroundsWidth;
	mNumberOfBackgroundsHeight = numberOfBackgroundsHeight;
}