#include "EntityManager.h"
#include "Entity.h"
#include "Character.h"
#include <cmath>
#include "Character.h"
#include "Door.h"
#include <algorithm>
#include "ImageManager.h"
#include <iostream>
#include <SFML\Graphics.hpp>

EntityManager* EntityManager::sInstance = 0;

EntityManager::EntityManager():
	mPlayerLife(3),
	mMapTop(360),
	mMapLeft(512)
{
		mLifeTexture.loadFromImage(*ImageManager::getImage("heart.png"));
		mLifeSprite.setTexture(mLifeTexture);

		frameTexture.loadFromFile("frame.png");
		frame.setTexture(frameTexture);
		
		mPortraitSprite[0] = Animation("PortraitesKiba.png", 60, 1, 64, 64);
		mPortraitSprite[1] = Animation("PortraitesCharlotte.png", 60, 1, 64, 64);
		mPortraitSprite[2] = Animation("Fenrir Face sprite 1_1.png", 60, 1, 64, 64);
		mPortraitSprite[3] = Animation("Sheeka Face sprite 1_1.png", 60, 1, 64, 64);
		shadow.loadFromFile("greyscale.frag", sf::Shader::Fragment);
		shadow.setParameter("texture", sf::Shader::CurrentTexture);
		mLifeTexture.loadFromImage(*ImageManager::getImage("heart.png"));
		mLifeSprite.setTexture(mLifeTexture);
		mMaskTexture.loadFromImage(*ImageManager::getImage("mask.png"));
		mMaskSprite.setTexture(mMaskTexture);
		mBackgroundTexture.loadFromImage(*ImageManager::getImage("background.png"));
		createBackground();
		setMapSize(61, 28);
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

	updatePlayerLife();

	updatePlayerPortrait();
}

// uppdaterar lifeposition
void EntityManager::lifeAndMaskPosition()
{
	mLifeSprite.setPosition(mView->getCenter() - sf::Vector2f(512, 360));
	mMaskSprite.setPosition(getCharacterPos() - sf::Vector2f(1024, 720));
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
	renderBackground();

	
	for(int h = 0; h < 4; ++h)
	{
		for(EntityVector::size_type i = 0; i < mEntities.size(); ++i)
		{
			if(mEntities[i]->getLayer() == h)
			{
				mEntities[i]->render();
			}
		}
	}
	
	renderLifeAndMask();
	renderPortrait();
	lifeAndMaskPosition();
	//sf::RectangleShape rect(sf::Vector2f(mMapRight - 512, mMapBottom - 360));
	//rect.setPosition(mMapLeft, mMapTop);
	//sf::Color colo(255,255,255,128);
	//rect.setFillColor(colo);
	//ImageManager::render(&rect);
}

// renderar livet
void EntityManager::renderLifeAndMask()
{
	ImageManager::render(&mMaskSprite);
	mLifeSprite.setPosition(mLifeSprite.getPosition() + sf::Vector2f(20, frame.getLocalBounds().height + 10));
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
		frame.setPosition(	mPortraitSprite[i].getSprite().getPosition() - sf::Vector2f(9 , 9));
		for(CharacterVector::size_type j = 0; j < mCharacters.size(); j++)
		{
			sf::RenderStates states;
			states.shader = &shadow;
			if (mCharacters[j]->getEntityKind() == Entity::KIBA && i == 0)
			{
				ImageManager::render(&mPortraitSprite[0].getSprite(), mPrimaryCharacter != Entity::KIBA ? states : sf::RenderStates::Default);
				ImageManager::render(&frame, mPrimaryCharacter != Entity::KIBA ? states : sf::RenderStates::Default);
			}

			else if (mCharacters[j]->getEntityKind() == Entity::CHARLOTTE && i == 1)
			{
				ImageManager::render(&mPortraitSprite[1].getSprite(), mPrimaryCharacter != Entity::CHARLOTTE ? states : sf::RenderStates::Default);
				ImageManager::render(&frame, mPrimaryCharacter != Entity::CHARLOTTE ? states : sf::RenderStates::Default);
			}

			else if (mCharacters[j]->getEntityKind() == Entity::FENRIR && i == 2)
			{
				ImageManager::render(&mPortraitSprite[2].getSprite(), mPrimaryCharacter != Entity::FENRIR ? states : sf::RenderStates::Default);
				ImageManager::render(&frame, mPrimaryCharacter != Entity::FENRIR ? states : sf::RenderStates::Default);
			}

			else if (mCharacters[j]->getEntityKind() == Entity::SHEEKA && i == 3)
			{
				ImageManager::render(&mPortraitSprite[3].getSprite(), mPrimaryCharacter != Entity::SHEEKA ? states : sf::RenderStates::Default);
				ImageManager::render(&frame, mPrimaryCharacter != Entity::SHEEKA ? states : sf::RenderStates::Default);
			}
		}
		mPortraitSprite[i].setPosition(	mView->getCenter() - sf::Vector2f(503 - i * frameTexture.getSize().x, 351));
	}
	
}

// tilar bakgrunden
void EntityManager::createBackground()
{
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
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

// l�gger till en entiteter i de vectorer de ska va i.
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

// tar bort entiterter som �r d�da i b�de entityvectorn och dynamicentityvektorn
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

// uppdaterar vilken som �r den prim�ra karakt�ren
void EntityManager::updatePrimaryCharacter()
{
	Entity::EntityKind tempEntityKind = mPrimaryCharacter;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		tempEntityKind = Entity::KIBA;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		tempEntityKind = Entity::CHARLOTTE;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		tempEntityKind = Entity::FENRIR;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		tempEntityKind = Entity::SHEEKA;
	}

	for(CharacterVector::size_type i = 0; i < mCharacters.size(); ++i) // kollar om den valda karakt�ren finns i vektorn
	{
		if(mCharacters[i]->getEntityKind() == tempEntityKind)
		{
			mPrimaryCharacter = tempEntityKind;
		}
	}
}

// returnerar possitione till den prim�ra karakt�ren
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

// setter primarycharacter
void EntityManager::setPrimaryCharacter(Entity::EntityKind entityKind)
{
	mPrimaryCharacter = entityKind;
}

void EntityManager::interact()
{
	//k�r interact mot alla som krockar
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

// s�tter viewn
void EntityManager::setView(sf::View* view)
{
	mView = view;
}

sf::View* EntityManager::getView()
{
	return mView;
}

// updaterar view positionen
void EntityManager::updateView()
{
	sf::Vector2f playerPos = getCharacterPos();
	
	if(playerPos.x > mMapLeft && playerPos.x < mMapRight)
	{
		mView->setCenter(sf::Vector2f(playerPos.x, mView->getCenter().y));
	}
	else
	{
		if(playerPos.x > mMapRight / 2)
		{
			mView->setCenter(sf::Vector2f(mMapRight, mView->getCenter().y));
		}
		else
		{
			mView->setCenter(sf::Vector2f(mMapLeft, mView->getCenter().y));
		}	
	}
	// det st�r fan totte �verallt
	if(playerPos.y > mMapTop && playerPos.y < mMapBottom)
	{
		mView->setCenter(sf::Vector2f(mView->getCenter().x, playerPos.y));
	}
	else
	{
		if(playerPos.y > mMapBottom / 2)
		{
			mView->setCenter(sf::Vector2f(mView->getCenter().x, mMapBottom));
		}
		else
		{
			mView->setCenter(sf::Vector2f(mView->getCenter().x, mMapTop));
		}
	}
}

// s�tter storleken p� mappen tar emot fyra inter, l�ng o h�jd r�knat i block samt antalet bakgrunder i h�jdled och l�ngd;
void EntityManager::setMapSize(int numberOfBlocksRight, int numberOfBlocksBottom)
{
	mMapRight = numberOfBlocksRight * 64 - 576;
	mMapBottom = numberOfBlocksBottom * 64 - 424;
}

// returnerar storleken p� mCharacters
int EntityManager::getSizeOfCharacterVector()const
{
	return static_cast<int>(mCharacters.size());
}

void EntityManager::ClearAll()
{
	while(!mEntities.empty())
	{
		delete mEntities.back();
		mEntities.pop_back();
	}
	mDynamicEntities.clear();
	mCharacters.clear();
}